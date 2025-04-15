#include "Keyboard.h"
#include "SDL2/SDL.h"

Keyboard::Keyboard() {};
Keyboard::Keyboard(DIRECTION state, bool isMoviment) : state(NONE), isMoviment(false){};


void Keyboard::update(Player& player, float deltaTime) {
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
        float moveSpeed = player.getMovSpeed();

        switch (state) {
            case UP:
            currentPosition.y -= currentSpeed.y * moveSpeed * deltaTime;
            break;

            case DOWN:
            currentPosition.y += currentSpeed.y * moveSpeed * deltaTime;
            break;

            break;
            case LEFT:
            currentPosition.x -= currentSpeed.x * moveSpeed * deltaTime;
            break;

            case RIGHT:
            currentPosition.x += currentSpeed.x * moveSpeed * deltaTime;
            break;

            default:
            break;
        }
        player.setPosition(currentPosition);

        //std::cout << "dt: " << deltaTime << ", pos: " << currentPosition.x << ", " << currentPosition.y << std::endl;
    }
};