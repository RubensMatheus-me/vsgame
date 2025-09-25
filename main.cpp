#include "Game.h"
#include "TickRate.h"
#include <SDL2/SDL.h>
#include "scenes/MenuScene.h"
#include "SceneManager.h"

Game *game = nullptr;


int main(int argc, const char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL não pode ser inicializado! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    SDL_DisplayMode displayMode;
    if (SDL_GetCurrentDisplayMode(0, &displayMode) != 0) {
        printf("Não foi possível obter o tamanho da tela! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    int screenWidth = 800;
    int screenHeight = 600;
    game = new Game();

    SceneManager& sceneManager = SceneManager::getInstance();
    sceneManager.createWindow("Vsgame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, false);
    sceneManager.pushScene(new MenuScene(game));

    SDL_Event event;
    while (sceneManager.getIsRunning()) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                sceneManager.setIsRunning(false); 
            }
            
            sceneManager.handleInput(event);
        }

        sceneManager.render();
		sceneManager.update();
        SDL_Delay(16);  
    }

    SDL_Quit();
    return 0;
}