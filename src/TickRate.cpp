#include "TickRate.h"

TickRate::TickRate() : lastTime(SDL_GetTicks()), currentTime(0), deltaTime(0.0), frameCount(0), fpsTimer(SDL_GetTicks()), fps(0) {}

void TickRate::update() {
    currentTime = SDL_GetTicks();
    deltaTime = (currentTime - lastTime) / 1000.0;
    lastTime = currentTime;

    frameCount++;

    if(currentTime - fpsTimer >= 1000) {
        fps = frameCount;
        frameCount = 0;
        fpsTimer = currentTime;
    }
}
