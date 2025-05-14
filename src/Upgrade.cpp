#include "Upgrade.h"

Upgrade::Upgrade(const Vector& size, SpriteAnimation* spriteAnimation, const std::string& description,
                 float hpMultiplier, float damageMultiplier, float movSpeedMultiplier)
    : Item(size, spriteAnimation, description), 
      hpMultiplier(hpMultiplier), damageMultiplier(damageMultiplier), movSpeedMultiplier(movSpeedMultiplier) {}
