	#include "SceneManager.h"
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_ttf.h>
	#include "GameStateManager.h"
	#include "iostream"

	SceneManager::~SceneManager() {
		cleanUp();
	}

	void SceneManager::pushScene(Scene* scene) {
		if (!sceneStack.empty()) {
			sceneStack.top()->cleanUp();
		}
		sceneStack.push(scene);
		scene->init(renderer);
	}

	void SceneManager::popScene() {
		if (!sceneStack.empty()) {
			sceneStack.top()->cleanUp();
			sceneStack.pop();
		}
	}

	void SceneManager::changeScene(Scene* scene) {
		cleanUp();
		pushScene(scene);
	}

	void SceneManager::handleInput(SDL_Event& event) {
		if (!sceneStack.empty()) {
			sceneStack.top()->handleInput(event);
		}
	}

	void SceneManager::update() {
		getTickRate()->update();
		float dt = getTickRate()->getDeltaTime();
		if (!sceneStack.empty()) {
			sceneStack.top()->update(dt);
		}
	}

	void SceneManager::cleanUp() {
		while (!sceneStack.empty()) {
			sceneStack.top()->cleanUp();
			delete sceneStack.top();
			sceneStack.pop();
		}
	}

	Scene* SceneManager::getCurrentScene() {
		if (!sceneStack.empty()) {
			return sceneStack.top();
		}
		return nullptr;
	}

	void SceneManager::createWindow(const char *title, int xPos, int yPos, int width, int height, bool fullscreen) {
		Uint32 flags = SDL_WINDOW_SHOWN;
		if (fullscreen)
		{
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}
		if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
		{

			if (TTF_Init() == -1)
			{
				setIsRunning(false);
				return;
			}

			//window = SDL_CreateWindow(title, xPos, yPos, 800, 600, flags);
			//SDL_GetWindowSize(window, 800, 600);
			window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
			if (!window) {
				printf("Erro ao criar a janela: %s\n", SDL_GetError());
				return;
			}
			
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			SDL_RenderSetLogicalSize(renderer, 800, 600);
			if (!renderer) {
				printf("Erro ao criar o renderizador: %s\n", SDL_GetError());
				return;
			}
			this->width = width;
    		this->height = height;

			setIsRunning(true);
			GameStateManager::getInstance().setState(GameState::InMenu);
		}
		else
		{
			setIsRunning(false);
			GameStateManager::getInstance().setState(GameState::InLose);
		}
	}

	void SceneManager::render() {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);

		SDL_GetWindowSize(window, &width, &height);
		if (!sceneStack.empty()) {
			sceneStack.top()->render();
		}
		SDL_RenderPresent(renderer);
	}

	void SceneManager::destroyWindow() {
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);

		TTF_Quit();
		SDL_Quit();
		setIsRunning(false);
		std::cout << "Jogo limpo" << std::endl;
	}

void SceneManager::toggleFullscreen() {
	Uint32 fullscreenFlag = SDL_WINDOW_FULLSCREEN_DESKTOP;
    bool isFullscreen = SDL_GetWindowFlags(window) & fullscreenFlag;

    if (isFullscreen)
        SDL_SetWindowFullscreen(window, 0);
    else
        SDL_SetWindowFullscreen(window, fullscreenFlag);
}