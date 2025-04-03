#include "Upgrade.h"

Upgrade::Upgrade(float width, float height, SDL_Texture *image, const std::string& description,
                 float hpMultiplier, float damageMultiplier, float movSpeedMultiplier)
    : Item(width, height, image, description), 
      hpMultiplier(hpMultiplier), damageMultiplier(damageMultiplier), movSpeedMultiplier(movSpeedMultiplier) {}
