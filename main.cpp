#include "Game.h"
#include "TickRate.h"


Game *game = nullptr;
int main(int argc, const char* argv[]) {
    
    game = new Game();
    game->init("VsGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

    while(game->getIsRunning() == true) {
        game->events();
        game->update();
        game->render();
        game->limitFPS(60.0f);
        
    }
    game->clean();

    return 0;
}