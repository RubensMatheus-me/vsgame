#include "Game.h"
#include "TickRate.h"


Game *game = nullptr;
int main(int argc, const char* argv[]) {
    
    game = new Game();
    game->init("VsGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
    game->loadResources();
    

    while(game->running()) {
        game->handleEvents();
        game->update();
        game->render();
        game->limitFPS(60.0f);
        
    }
    game->clean();

    return 0;
}