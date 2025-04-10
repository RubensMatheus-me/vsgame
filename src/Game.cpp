#include "Game.h"
#include "iostream"
#include "TextureManager.h"

Game::Game() {};
Game::~Game() {};

void Game::init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen) {
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_INIT_EVERYTHING) {
		window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
		if (window) {
			std::cout << "Janela criada" << std::endl;
		}
		
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer criado" << std::endl;
		}

		TextureManager::init(renderer);
		isRunning = true;

	} else {
		isRunning = false;
	}
	
}

void Game::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	
	default:
		break;
	}

}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	TextureManager::cleanTexture();
	SDL_Quit();

	std::cout << "Jogo fechado" << std::endl;
}

void Game::render() {
	SDL_RenderClear(renderer);

	player->render(renderer);

	SDL_RenderPresent(renderer);
}

void Game::update() {
	updateCounter++;

	//std::cout << "update: " << updateCounter << std::endl;
}

void Game::loadResources() {
	TextureManager::loadTexture("assets/sprites/classes/Stickman.png", "stickman");

	SDL_Texture* tex = TextureManager::getTexture("stickman");

	this->player = new Player(
		64, 64,                     
		tex,                        
		Vector(100, 100),          
		Vector(0, 0),               
		100, 1.0f, 2.0f,        
		0, 1, 1.5f 
	);

}