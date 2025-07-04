#include "Game.h"
#include "TickRate.h"
#include <SDL2/SDL.h>

Game *game = nullptr;

int main(int argc, const char *argv[])
{

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL não pode ser inicializado! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    SDL_DisplayMode displayMode;
    if (SDL_GetCurrentDisplayMode(0, &displayMode) != 0)
    {
        printf("Não foi possível obter o tamanho da tela! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    int screenWidth = 800;
    int screenHeight = 600;

    game = new Game();
    game->init("VsGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, false);

    while (game->getIsRunning())
    {
        game->events();
        game->update();
        game->render();
        game->limitFPS(60.0f);
    }

    game->clean();
    delete game;
    game = nullptr;

    SDL_Quit();

    return 0;
}
