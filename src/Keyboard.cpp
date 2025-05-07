#include "Keyboard.h"
#include "SDL2/SDL.h"
#include "SpriteAnimation.h"
#include <iostream>
#include <iomanip>
#include <cmath>

Keyboard::Keyboard() : state(NONE), isMoviment(false) {}

void Keyboard::update(Player& player, float deltaTime) {
    SpriteAnimation spriteAnim;
    const Uint8* keys = SDL_GetKeyboardState(NULL);
    
    isMoviment = false;
    Vector direction = {0, 0};

    if (keys[SDL_SCANCODE_W]) {
        direction.y -= 1;
        isMoviment = true;
    }
    if (keys[SDL_SCANCODE_S]) {
        direction.y += 1;
        isMoviment = true;
    }
    if (keys[SDL_SCANCODE_A]) {
        direction.x -= 1;
        isMoviment = true;
    }
    if (keys[SDL_SCANCODE_D]) {
        direction.x += 1;
        isMoviment = true;
    }

    if (isMoviment) {
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length != 0) {
            direction.x /= length;
            direction.y /= length;
        }

        Vector position = player.getPosition();
        float speed = player.getMovSpeed();

        position.x += direction.x * speed * deltaTime;
        position.y += direction.y * speed * deltaTime;

        player.setPosition(position);
        player.setIsMoving(true);
        player.setDirection(direction);
        //std::cout << std::fixed << std::setprecision(2);
        //std::cout << "pos: " << position.x << ", " << position.y << std::endl;
    }else {
        player.setIsMoving(false);
        player.setDirection(Vector(0, 0));
    }
}
