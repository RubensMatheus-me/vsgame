#include "Upgrade.h"

Upgrade::Upgrade(float width, float height, SpriteAnimation* spriteAnimation, const std::string& description,
                 float hpMultiplier, float damageMultiplier, float movSpeedMultiplier)
    : Item(width, height, spriteAnimation, description), 
      hpMultiplier(hpMultiplier), damageMultiplier(damageMultiplier), movSpeedMultiplier(movSpeedMultiplier) {}
