#include "Weapon.h"

Weapon::Weapon(const Vector& size, SpriteAnimation* spriteAnimation, const std::string& description,
               float flatDamage, float flatAtkSpeed, float damageMultiplier,
               float atkSpeedMultiplier, int level) : Item(size, spriteAnimation, description),
      flatDamage(flatDamage), flatAtkSpeed(flatAtkSpeed),
      damageMultiplier(damageMultiplier), atkSpeedMultiplier(atkSpeedMultiplier),
      level(level) {}