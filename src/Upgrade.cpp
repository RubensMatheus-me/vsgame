#include "Upgrade.h"

Upgrade::Upgrade(const Vector& size, SpriteAnimation* spriteAnimation, const std::string& name, const std::string& description,
                 float hpMultiplier, float damageMultiplier, float movSpeedMultiplier)
    : Item(size, spriteAnimation, description), 
      hpMultiplier(hpMultiplier), damageMultiplier(damageMultiplier), movSpeedMultiplier(movSpeedMultiplier) {}

void Upgrade::render(SDL_Renderer* renderer, const Vector& menuoffset) {

    if (getSprite()) {
        getSprite()->render(renderer,  menuoffset.x,  menuoffset.y);
    }
    
}

void Upgrade::render(SDL_Renderer* renderer) {

    if (getSprite()) {
        getSprite()->render(renderer,  1,  1);
    }
    
}

void Upgrade::update(float deltaTime) {
    if (getSprite()) {
        getSprite()->update(deltaTime); 
    }  
}