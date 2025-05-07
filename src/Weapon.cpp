#include "Weapon.h"

Weapon::Weapon(float width, float height, SpriteAnimation* spriteAnimation, const std::string& description,
               float flatDamage, float flatAtkSpeed, float damageMultiplier,
               float atkSpeedMultiplier, int level) : Item(width, height, spriteAnimation, description),
      flatDamage(flatDamage), flatAtkSpeed(flatAtkSpeed),
      damageMultiplier(damageMultiplier), atkSpeedMultiplier(atkSpeedMultiplier),
      level(level) {}