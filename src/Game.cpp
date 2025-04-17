#include "Game.h"
#include "iostream"
#include "TextureManager.h"
#include "Keyboard.h"
#include "TickRate.h"
#include "Enemy.h"

std::unique_ptr<Player> player;
std::unique_ptr<Enemy> enemy;
std::unique_ptr<Keyboard> keyboard;
std::unique_ptr<TickRate> tickRate;

Game::Game() : attackTimer(1.0f){};
Game::~Game() {};

void Game::init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen) {
	keyboard = std::make_unique<Keyboard>();
	tickRate = std::make_unique<TickRate>();
	int flags = 0;
	
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
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
	std::cout << "aaa" << std::endl;
	SDL_Quit();

	std::cout << "Jogo fechado" << std::endl;
}

void Game::render() {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	SDL_RenderClear(renderer);
	if (player != nullptr) {
        player->render(renderer);
    }else {
        std::cout << "Player não está inicializado!" << std::endl;
    }

	enemy->render(renderer);

	SDL_RenderPresent(renderer);
}

void Game::update() {
	tickRate->update();
	float dt = tickRate->getDeltaTime();
	
	//std::cout << "FPS: " << tickRate->getFPS() << std::endl;
	
	player->update();
	keyboard->update(*player, dt);

	attackTimer.update(dt);

	if(attackTimer.hasElapsed()) {

		std::cout << "timer" << std::endl << std::flush;

		attackTimer.reset();
	}

}

void Game::loadResources() {

	TextureManager::loadTexture("assets/sprites/classes/Stickman.png", "stickman");
	TextureManager::loadTexture("assets/sprites/enemies/slime.png", "slime");
}

void Game::limitFPS(float targetFPS) {
	Uint64 startTicks = SDL_GetPerformanceCounter();

	float frameDelay = 1000.0f / targetFPS;

	Uint64 endTicks = SDL_GetPerformanceCounter();

	float elapsedTime = (endTicks - startTicks) / (float)SDL_GetPerformanceFrequency() * 1000.0f;

	if(elapsedTime < frameDelay) {
		SDL_Delay(static_cast<Uint32>(frameDelay - elapsedTime));
	}
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