#include "Game.h"
#include "iostream"
#include "TextureManager.h"
#include "Keyboard.h"
#include "TickRate.h"
#include "CollisionManager.h"
#include "Enemy.h"
#include "SDL_ttf.h"

const char* pathFont = "assets/fonts/dogica.ttf";
int windowWidth, windowHeight;

bool Game::debugMode = false;

std::unique_ptr<Player> player;
std::unique_ptr<Enemy> enemy;
std::vector<std::unique_ptr<Enemy>> enemies;
std::vector<GraphicalElement*> allElements;
std::unique_ptr<CollisionManager> collision;
std::unique_ptr<Keyboard> keyboard;
std::unique_ptr<TickRate> tickRate;
std::unique_ptr<CameraManager> camera;

std::string lastFpsText;
std::string lastTimeText;
SDL_Texture* fpsTexture = nullptr;
SDL_Texture* timeTexture = nullptr;


Game::Game() : timer(1.0f){};
Game::~Game() {};

void Game::init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen) {

	keyboard = std::make_unique<Keyboard>();
	tickRate = std::make_unique<TickRate>();
	collision = std::make_unique<CollisionManager>();
	tileManager = std::make_unique<TileManager>();

	int flags = 0;
	
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		if(TTF_Init() == -1) {
			setIsRunning(false);
			return;
		}
		window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
		SDL_GetWindowSize(window, &windowWidth, &windowHeight);

		renderer = SDL_CreateRenderer(window, -1, 0);
		camera = std::make_unique<CameraManager>(windowWidth, windowHeight);
		TextureManager::init(renderer);

		loadResources();
		tileManager->loadMap("assets/map/tileset.json", "assets/data/tiles.json", renderer);
		initializeEntities();

		spawnEnemy();


		setIsRunning(true);

	} else {
		setIsRunning(false);
	}
	
}

void Game::events() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			setIsRunning(false);
		}
	}

}

void Game::clean() {

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	TextureManager::cleanTexture();

	SDL_DestroyTexture(fpsTexture);
    SDL_DestroyTexture(timeTexture);


	TTF_Quit();
	SDL_Quit();

	std::cout << "Jogo limpo" << std::endl;
}

void Game::render() {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	SDL_RenderClear(renderer);
	Vector camOffset = camera->getOffSet();

	tileManager->renderMap(renderer, camOffset, player->getCollider());
	
	SDL_GetWindowSize(window, &windowWidth, &windowHeight);

	if (player != nullptr) {
        player->render(renderer, camOffset);
    }else {
        std::cout << "Player não está inicializado!" << std::endl;
    }

	for (auto& e : enemies) {
		e->render(renderer, camOffset);
	}

	if (fpsTexture == nullptr) {
		std::cerr << "Falha ao criar textura de FPS!" << std::endl;
	}

	if(fpsTexture != nullptr) {
		int textW = 0, textH = 0;
        SDL_QueryTexture(fpsTexture, nullptr, nullptr, &textW, &textH);
        SDL_Rect fpsRect = {10, 10, textW, textH};
        SDL_RenderCopy(renderer, fpsTexture, nullptr, &fpsRect);
	}

	if (timeTexture != nullptr) {
        int textW = 0, textH = 0;
        SDL_QueryTexture(timeTexture, nullptr, nullptr, &textW, &textH);
        SDL_Rect timeRect = {(windowWidth - textW) / 2, 10, textW, textH};
        SDL_RenderCopy(renderer, timeTexture, nullptr, &timeRect);
    }

	if(!getDebugMode() == false){
		collision->debugDrawColliders(renderer, allElements, camera->getOffSet());
	}

	SDL_RenderPresent(renderer);
}

void Game::update() {
	SDL_GetWindowSize(window, &windowWidth, &windowHeight);
	tickRate->update();
	camera->follow(player->getPosition());

	float dt = tickRate->getDeltaTime();
	
	player->update(dt);
	keyboard->update(*player, dt);

	timer.update(dt);

	if(!allElements.empty()) {
		CollisionManager::handleCollisions(allElements);
	}else {
		std::cerr << "allElements vazio para gerenciar a colisão" << std::endl;
	}

	for (auto& e : enemies) {
		Vector toPlayer = player->getPosition() - e->getPosition();
		toPlayer.normalize();
		e->setSpeed(toPlayer * e->getMovSpeed());
		e->update(dt);
	}

	updateFpsDisplay();
	updateClockDisplay();
}

void Game::loadResources() {

	//enemies, player
	TextureManager::loadTexture("assets/sprites/classes/Stickman.png", "stickman");
	TextureManager::loadTexture("assets/sprites/enemies/slime.png", "slime");

	//tiles
	TextureManager::loadTexture("assets/sprites/tiles/grassTile.png", "grassTile");
	TextureManager::loadTexture("assets/sprites/tiles/grassTile2.png", "grassTile2");
	TextureManager::loadTexture("assets/sprites/tiles/mudTile.png", "mudTile");
	TextureManager::loadTexture("assets/sprites/tiles/sandTile.png", "sandTile");
}

void Game::limitFPS(float targetFPS) {
	static Uint64 previousTicks = SDL_GetPerformanceCounter();
	Uint64 currentTicks = SDL_GetPerformanceCounter();

	float frameDelay = 1000.0f / targetFPS;

	float elapsedTime = (currentTicks - previousTicks) / (float)SDL_GetPerformanceFrequency() * 1000.0f;

	if(elapsedTime < frameDelay) {
		SDL_Delay(static_cast<Uint32>(frameDelay - elapsedTime));
	}

	previousTicks = SDL_GetPerformanceCounter();
}

void Game::initializeEntities() {

	float centerX = (windowWidth - 32) / 2;
	float centerY = (windowHeight - 32) / 2;


	SDL_Texture* tex = TextureManager::getTexture("stickman");
    if (tex == nullptr) {
        std::cerr << "Erro: textura 'stickman' não carregada corretamente!" << std::endl;
        return;
    }

    player = std::make_unique<Player>(
        32, 32,
        tex,
        Vector(centerX, centerY),
        Vector(0.5f, 0.5f),
        100, 1.0f, 100.0f,
        0, 1, 1.5f
    );

	allElements.push_back(player.get());

}

void Game::updateFpsDisplay() {
	int textW, textH;
	std::string currentFpsText = std::to_string(tickRate->getFPS());

	std::string fullText = "FPS: " + currentFpsText;


	SDL_Color black = {0, 0, 0, 255};

	if(currentFpsText != lastFpsText) {
		lastFpsText = currentFpsText;
		
		if(fpsTexture != nullptr) SDL_DestroyTexture(fpsTexture);
		
		TTF_Font* font = TTF_OpenFont(pathFont, 10);
		if(!font) {
			std::cerr << TTF_GetError() << std::endl;
			return;
		}
		
		textW = 0, textH = 0;
		if(TTF_SizeText(font, fullText.c_str(), &textW, &textH) != 0) {
			std::cerr << TTF_GetError() << std::endl;
			TTF_CloseFont(font);
			return;
		}

		fpsTexture = TextureManager::renderText(fullText, pathFont, black, 10);
		TTF_CloseFont(font);
	}
	
}

void Game::updateClockDisplay() {
	std::string timeText = timer.clock();

	SDL_Color black = {0, 0, 0, 255};

	if(timeText != lastTimeText) {
		lastTimeText = timeText;
	
		if(timeTexture != nullptr) {
			SDL_DestroyTexture(timeTexture);
			timeTexture = nullptr;
		}

		TTF_Font* font = TTF_OpenFont(pathFont, 12);
		if(!font) {
			std::cerr << "erro: " << TTF_GetError() << std::endl;
			return;
		}

		int textW = 0, textH = 0;

		if(TTF_SizeText(font, timeText.c_str(), &textW, &textH) != 0) {
			std::cerr << TTF_GetError() << std::endl;
			TTF_CloseFont(font);
			return;
		}
		timeTexture = TextureManager::renderText(timeText, pathFont, black, 12);
		if (timeTexture == nullptr) {
			std::cerr << "Erro ao criar a textura de tempo: " << TTF_GetError() << std::endl;
		}
		TTF_CloseFont(font);
	}
}

void Game::spawnEnemy() {
	int spawnMargin = 100;
	int side = rand() % 4;
	float x = 0, y = 0;

	switch(side) {
		case 0:
			x = rand() %(windowWidth + 200) - 100;
			y = - spawnMargin;
			break;
		case 1:
			x = rand() % (windowWidth + 200) - 100;
			y = windowHeight + spawnMargin;
			break;
		case 2:
			x = -spawnMargin;
			y = rand() % (windowHeight + 200) - 100;
			break;
		case 3:
			x = windowWidth + spawnMargin;
			y = rand() % (windowHeight + 200) - 100;
			break;
	}

	SDL_Texture* enemyTexture = TextureManager::getTexture("slime");

	if (TextureManager::getTexture("slime") == nullptr) {
		std::cerr << "Erro ao carregar textura slime!" << std::endl;
	}

	auto newEnemy = std::make_unique<Enemy>(
        32, 32,
        enemyTexture,
        Vector(x, y),
        Vector(0.5f, 0.5f),
        100, 1.0f, 50.0f,
        10.0f, 1
    );
	newEnemy->setTarget(player.get());

	Enemy* rawEnemyPtr = newEnemy.get();
	enemies.emplace_back(std::move(newEnemy));

	allElements.push_back(rawEnemyPtr);
}