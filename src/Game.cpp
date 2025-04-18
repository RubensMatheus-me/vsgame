#include "Game.h"
#include "iostream"
#include "TextureManager.h"
#include "Keyboard.h"
#include "TickRate.h"
#include "Enemy.h"
#include "SDL_ttf.h"

std::unique_ptr<Player> player;
std::unique_ptr<Enemy> enemy;
std::unique_ptr<Keyboard> keyboard;
std::unique_ptr<TickRate> tickRate;

std::string lastFpsText;
std::string lastTimeText;
std::string lastMillisText;
SDL_Texture* fpsTexture = nullptr;
SDL_Texture* timeTexture = nullptr;
SDL_Texture* millisTexture = nullptr;

Game::Game() : timer(1.0f){};
Game::~Game() {};

void Game::init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen) {
	keyboard = std::make_unique<Keyboard>();
	tickRate = std::make_unique<TickRate>();
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
		renderer = SDL_CreateRenderer(window, -1, 0);
		
		TextureManager::init(renderer);
		
		loadResources();
		initializeEntities();

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
	TTF_Quit();
	SDL_Quit();

	std::cout << "Jogo limpo" << std::endl;
}

void Game::render() {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	SDL_RenderClear(renderer);
	int windowWidth = 0, windowHeight = 0;
	SDL_GetWindowSize(window, &windowWidth, &windowHeight);

	if (player != nullptr) {
        player->render(renderer);
    }else {
        std::cout << "Player não está inicializado!" << std::endl;
    }

	enemy->render(renderer);

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


	SDL_RenderPresent(renderer);
}

void Game::update() {
	tickRate->update();

	float dt = tickRate->getDeltaTime();
	
	player->update();
	keyboard->update(*player, dt);

	timer.update(dt);

	updateFpsDisplay();
	updateClockDisplay();
}

void Game::loadResources() {

	TextureManager::loadTexture("assets/sprites/classes/Stickman.png", "stickman");
	TextureManager::loadTexture("assets/sprites/enemies/slime.png", "slime");
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
	SDL_Texture* tex = TextureManager::getTexture("stickman");
    if (tex == nullptr) {
        std::cerr << "Erro: textura 'stickman' não carregada corretamente!" << std::endl;
        return;
    }

    player = std::make_unique<Player>(
        64, 64,
        tex,
        Vector(100.0f, 100.0f),
        Vector(0.5f, 0.5f),
        100, 1.0f, 300.0f,
        0, 1, 1.5f
    );

	SDL_Texture* enemySlime = TextureManager::getTexture("slime");

	enemy = std::make_unique<Enemy>(
        64, 64,
        enemySlime,
        Vector(500.0f, 500.0f),   
        Vector(0.0f, 0.0f),       
        100, 1.0f, 10.0f,                     
		10.0f, 1                         
    );
}

void Game::updateFpsDisplay() {
	int textW, textH;
	std::string currentFpsText = std::to_string(tickRate->getFPS());

	std::string fullText = "FPS: " + currentFpsText;
	const char* path = "assets/fonts/dogica.ttf";

	SDL_Color black = {0, 0, 0, 255};

	if(currentFpsText != lastFpsText) {
		lastFpsText = currentFpsText;
		
		if(fpsTexture != nullptr) SDL_DestroyTexture(fpsTexture);
		
		TTF_Font* font = TTF_OpenFont(path, 10);
		if(!font) {
			std::cerr << TTF_GetError() << std::endl;\
			return;
		}
		
		textW = 0, textH = 0;
		if(TTF_SizeText(font, fullText.c_str(), &textW, &textH) != 0) {
			std::cerr << TTF_GetError() << std::endl;
			TTF_CloseFont(font);
			return;
		}

		fpsTexture = TextureManager::renderText(fullText, path, black, 10);
		TTF_CloseFont(font);
	}
	
}

void Game::updateClockDisplay() {
	auto[timeText, millisText] = timer.clock();

    const char* path = "assets/fonts/dogica.ttf";
	SDL_Color black = {0, 0, 0, 255};

	if(timeText != lastTimeText) {
		lastTimeText = timeText;
	}
	if(timeTexture != nullptr) SDL_DestroyTexture(timeTexture);

	TTF_Font* font = TTF_OpenFont(path, 12);
	if(!font) {
		std::cerr << TTF_GetError() << std::endl;
		return;
	}

	int textW = 0, textH = 0;

	if(TTF_SizeText(font, timeText.c_str(), &textW, &textH) != 0) {
		std::cerr << TTF_GetError() << std::endl;
		TTF_CloseFont(font);
		return;
	}
	timeTexture = TextureManager::renderText(timeText, path, black, 12);
	TTF_CloseFont(font);
}