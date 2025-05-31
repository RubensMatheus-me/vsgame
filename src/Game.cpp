#include "Game.h"
#include "iostream"
#include "TextureManager.h"
#include "Keyboard.h"
#include "TickRate.h"
#include "CollisionManager.h"
#include "Enemy.h"
#include "Upgrade.h"
#include "SDL_ttf.h"
#include "SpriteAnimation.h"
#include "Config.h"
#include "LevelUpMenu.h"
#include "AxeProjectile.h"
#include "Timer.h"
#include <time.h>

using namespace Config;

const char* pathFont = "assets/fonts/dogica.ttf";
int windowWidth, windowHeight;

bool Game::debugMode = true;

std::unique_ptr<Player> player;
std::unique_ptr<Enemy> enemy;
std::vector<std::unique_ptr<Enemy>> enemies;
std::vector<GraphicalElement*> allElements;
std::unique_ptr<CollisionManager> collision;
std::unique_ptr<Keyboard> keyboard;
std::unique_ptr<TickRate> tickRate;
std::unique_ptr<SpriteAnimation> playerAnimation;
std::unique_ptr<LevelUpMenu> levelUpMenu;
std::vector<std::unique_ptr<Projectile>> projectiles;
std::vector<std::unique_ptr<SpriteAnimation>> ownedAnimations;

std::string lastFpsText;
std::string lastTimeText;
std::string lastXpText;
SDL_Texture* fpsTexture = nullptr;
SDL_Texture* timeTexture = nullptr;
SDL_Texture* xpTexture = nullptr;

Game::Game() : timerEvents(2.0f), gameTime(1.0f){}; 
Game::~Game() {};

void Game::init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen) {

	keyboard = std::make_unique<Keyboard>();
	tickRate = std::make_unique<TickRate>();
	collision = std::make_unique<CollisionManager>();
	tileManager = std::make_unique<TileManager>();
	playerAnimation = std::make_unique<SpriteAnimation>();
	levelUpMenu = std::make_unique<LevelUpMenu>();

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
		CameraManager::getCameraManager()->init(windowWidth, windowHeight);

		renderer = SDL_CreateRenderer(window, -1, 0);
		TextureManager::init(renderer);
		levelUpMenu->init("assets/data/upgrades.json");
		loadResources();
		tileManager->loadMap("assets/map/tileset.json", "assets/data/tiles.json", renderer);
		
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

	SDL_DestroyTexture(fpsTexture);
    SDL_DestroyTexture(timeTexture);
    SDL_DestroyTexture(xpTexture);

	TTF_Quit();
	SDL_Quit();

	std::cout << "Jogo limpo" << std::endl;
}

void Game::render() {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	SDL_RenderClear(renderer);

	tileManager->renderMap(renderer, player->getCollider());
	
	SDL_GetWindowSize(window, &windowWidth, &windowHeight);

	if (player != nullptr) {
        player->render(renderer);
    }else {
        std::cout << "Player não está inicializado!" << std::endl;
    }

	for (auto& e : enemies) {
		e->render(renderer);
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

	if (xpTexture != nullptr) {
		int textW = 0, textH = 0;
        SDL_QueryTexture(xpTexture, nullptr, nullptr, &textW, &textH);
        SDL_Rect xpRect = {10, 25, textW, textH};
        SDL_RenderCopy(renderer, xpTexture, nullptr, &xpRect);
	}

	for (auto& proj : projectiles) {
		proj->render(renderer);
	}

	/*
	if(getDebugMode()){
		collision->debugDrawColliders(renderer, allElements, camera->getOffSet());
	}
	*/
	SDL_RenderPresent(renderer);
}

void Game::update() {
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    tickRate->update();
    float dt = tickRate->getDeltaTime();

    timerEvents.update(dt);
	gameTime.update(dt);

	if (player->getLevel() > levelUpMenu->lastUpgradedLevel) {
		TTF_Font* font = TTF_OpenFont(pathFont, 10);
		levelUpMenu->show(renderer, font, *player, windowWidth, windowHeight);
		TTF_CloseFont(font);
		levelUpMenu->lastUpgradedLevel = levelUpMenu->lastUpgradedLevel +1;
	}

    if (timerEvents.hasElapsed()) {
        shootProjectile();
        timerEvents.reset();
    }
    if (player) {
        CameraManager::getCameraManager()->follow(player->getPosition());
        keyboard->update(*player, dt);
        player->update(dt);
    }

    // if (!allElements.empty()) {
    //     CollisionManager::handleCollisions(allElements);
    // } else {
    //     std::cerr << "allElements vazio para gerenciar a colisão" << std::endl;
    // }
	if(!enemies.empty()) {
		CollisionManager::handlePlayerCollisions(player.get(), enemies);
	}
	if(!enemies.empty() && !projectiles.empty()) {
		CollisionManager::handleProjectileCollisions(player.get(), enemies, projectiles);
	}

    for (auto& e : enemies) {
        Vector toPlayer = player->getPosition() - e->getPosition();
        toPlayer.normalize();
        e->setSpeed(toPlayer * e->getMovSpeed());
        e->update(dt);
    }

    for (auto& proj : projectiles) {
        proj->update(dt);
    }

	
	removeDeadEntities();

    updateFpsDisplay();
    updateClockDisplay();
	updateXp();
}


void Game::loadResources() {

	//player
	TextureManager::loadTexture("assets/sprites/classes/spriteSheets/warrior/idle/idle-left.png", "warrior-idle-left");
	TextureManager::loadTexture("assets/sprites/classes/spriteSheets/warrior/idle/idle-right.png", "warrior-idle-right");
	TextureManager::loadTexture("assets/sprites/classes/spriteSheets/warrior/walk/walk-left.png", "warrior-walk-left");
	TextureManager::loadTexture("assets/sprites/classes/spriteSheets/warrior/walk/walk-right.png", "warrior-walk-right");

	//enemies
	TextureManager::loadTexture("assets/sprites/enemies/slime.png", "slime");

	//tiles
	TextureManager::loadTexture("assets/sprites/tiles/grassTile.png", "grassTile");
	TextureManager::loadTexture("assets/sprites/tiles/grassTile2.png", "grassTile2");
	TextureManager::loadTexture("assets/sprites/tiles/mudTile.png", "mudTile");
	TextureManager::loadTexture("assets/sprites/tiles/sandTile.png", "sandTile");

	//GUI
	TextureManager::loadTexture("assets/sprites/gui/upgradeMenu.png", "upgradeMenu");


	//projectiles
	TextureManager::loadTexture("assets/sprites/effects/axe.png", "axe");
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

	playerAnimation->addAnimation("walk-right", "warrior-walk-right", 0, 0, 32, 32, 4);
	playerAnimation->addAnimation("walk-left", "warrior-walk-left", 0, 0, 32, 32, 4);
	playerAnimation->addAnimation("idle-right", "warrior-idle-right", 0, 0, 34, 32, 6);
	playerAnimation->addAnimation("idle-left", "warrior-idle-left", 0, 0, 34, 32, 6);
	playerAnimation->play("idle-right");

	int mapCenterX = tileManager->getMapWidthInPixels() / 2;
	int mapCenterY = tileManager->getMapHeightInPixels() / 2;
	Vector centerPos(mapCenterX, mapCenterY);
	Vector zero(0, 0);

	player = std::make_unique<Player>(
		Config::PLAYER_SIZE,
		playerAnimation.get(),
		centerPos,
		Config::PLAYER_SPEED,
		Config::PLAYER_HP,
		Config::PLAYER_ATTACK_RATE,
		Config::PLAYER_MOV_SPEED,
		Config::PLAYER_INITIAL_XP,
		Config::PLAYER_INITIAL_LEVEL,
		Config::INITIAL_NEXT_LEVEL_EXPERIENCE,
		Config::PLAYER_ATTACK_SPEED,
		Config::PLAYER_IS_MOVING,
		Config::PLAYER_INITIAL_DIRECTION,
		Config::PLAYER_DAMAGE_COOLDOWN,
		Config::PLAYER_INVULNERABILITY_TIME                   
    );
	

	player->setAnimations(playerAnimation.get());
	allElements.push_back(player.get());
	int count = 10;
	for (size_t i = 0; i < count; i++)
	{
		spawnEnemy();
	}
	
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
	std::string timeText = gameTime.clock();

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

void Game::updateXp() {
	std::string xpText = "LEVEL: " + std::to_string(player->getLevel()) + " XP:" + std::to_string(static_cast<int>(player->getXp())) + " / " + std::to_string(static_cast<int>(player->getXpNextLevel()));
	if(xpText != lastXpText) {
		SDL_Color black = {0, 0, 0, 255};
		lastXpText = xpText;
	
		if(xpTexture != nullptr) {
			SDL_DestroyTexture(xpTexture);
			xpTexture = nullptr;
		}

		TTF_Font* font = TTF_OpenFont(pathFont, 12);
		if(!font) {
			std::cerr << "erro: " << TTF_GetError() << std::endl;
			return;
		}

		int textW = 0, textH = 0;

		if(TTF_SizeText(font, xpText.c_str(), &textW, &textH) != 0) {
			std::cerr << TTF_GetError() << std::endl;
			TTF_CloseFont(font);
			return;
		}
		xpTexture = TextureManager::renderText(xpText, pathFont, black, 12);
		if (xpTexture == nullptr) {
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
		case 0: x = rand() %(windowWidth + 200) - 100; y = -spawnMargin; break;
        case 1: x = rand() % (windowWidth + 200) - 100; y = windowHeight + spawnMargin; break;
        case 2: x = -spawnMargin; y = rand() % (windowHeight + 200) - 100; break;
        case 3: x = windowWidth + spawnMargin; y = rand() % (windowHeight + 200) - 100; break;
	}

	auto slimeAnim = std::make_unique<SpriteAnimation>();
	slimeAnim->addAnimation("idle", "slime", 0, 0, 32, 32, 1);
	slimeAnim->play("idle");

	auto slime = std::make_unique<Enemy>(
		Config::ENEMY_SIZE,
		nullptr,
		std::move(slimeAnim),
		Vector(x, y),
		Config::ENEMY_SPEED,
		Config::ENEMY_HP,
		Config::ENEMY_ATTACK_RATE,
		Config::ENEMY_MOV_SPEED,
		Config::ENEMY_XP_DROP,
		Config::ENEMY_SPAWN_WEIGHT  
	);
	slime->setTarget(player.get());

	Enemy* rawEnemyPtr = slime.get();
	enemies.emplace_back(std::move(slime));

	allElements.push_back(rawEnemyPtr);
}

void Game::shootProjectile() {
	if (enemies.empty()) return;
	Vector playerPos = player->getPosition();

		
	Enemy* target = enemies.front().get();
	Vector enemyPos = target->getPosition();

		
	Vector direction = enemyPos - playerPos;
	direction.normalize();

	auto anim = std::make_unique<SpriteAnimation>();
	anim->addAnimation("default", "axe", 0, 0, 32, 32, 1);
	anim->play("default");

	auto p = std::make_unique<AxeProjectile>(
		playerPos + 10.0f,
		direction,
		150.0f,
		10.0f,
		std::move(anim),
		player.get()
	);

	projectiles.push_back(std::move(p));
	allElements.push_back(projectiles.back().get());

}

void Game::removeDeadEntities() {
	projectiles.erase(
        std::remove_if(projectiles.begin(), projectiles.end(),
            [](const std::unique_ptr<Projectile>& p) {
                return !p->isAlive();
            }),
        projectiles.end()
    );

    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
            [](const std::unique_ptr<Enemy>& e) {
                return !e->isAlive();
            }),
        enemies.end()
    );

    allElements.clear();
    allElements.push_back(player.get());
    for (auto& e : enemies) allElements.push_back(e.get());
    for (auto& p : projectiles) allElements.push_back(p.get());
}