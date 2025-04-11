#include "Keyboard.h"
#include "SDL2/SDL.h"

Keyboard::Keyboard() {};
Keyboard::Keyboard(DIRECTION state, bool isMoviment) : state(NONE), isMoviment(false){};


void Keyboard::update(Player& player) {
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    
    if(currentKeyStates[SDL_SCANCODE_W]) {
        state = UP;
        isMoviment = true;

    } else if(currentKeyStates[SDL_SCANCODE_S]) {
        state = DOWN;
        isMoviment = true;

    } else if(currentKeyStates[SDL_SCANCODE_A]) {
        state = LEFT;
        isMoviment = true;

    }else if(currentKeyStates[SDL_SCANCODE_D]) {
        state = RIGHT;
        isMoviment = true;

    } else {
        state = NONE;
        isMoviment = false;
    }
    
    if(isMoviment) {
        Vector currentPosition = player.getPosition();
        Vector currentSpeed = player.getSpeed();

        switch (state) {
            case UP:
            currentPosition.y -= currentSpeed.y;
            break;

            case DOWN:
            currentPosition.y += currentSpeed.y;
            break;

            break;
            case LEFT:
            currentPosition.x -= currentSpeed.x;
            break;

            case RIGHT:
            currentPosition.x += currentSpeed.x;
            break;

            default:
            break;
        }
        player.setPosition(currentPosition);
    }
};