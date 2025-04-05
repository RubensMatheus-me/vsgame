#include "Weapon.h"

Weapon::Weapon(float width, float height, SDL_Texture *image, const std::string& description,
               float flatDamage, float flatAtkSpeed, float damageMultiplier,
               float atkSpeedMultiplier, int level) : Item(width, height, image, description),
      flatDamage(flatDamage), flatAtkSpeed(flatAtkSpeed),
      damageMultiplier(damageMultiplier), atkSpeedMultiplier(atkSpeedMultiplier),
      level(level) {}