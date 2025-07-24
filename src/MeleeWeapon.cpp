#include "MeleeWeapon.h"

MeleeWeapon::MeleeWeapon(const Vector& size, SpriteAnimation* spriteAnimation, const std::string& description,
                         float flatDamage, float flatAtkSpeed, float damageMultiplier,
                         float atkSpeedMultiplier, int level)
    : Weapon(size, spriteAnimation, description, flatDamage, flatAtkSpeed, damageMultiplier, atkSpeedMultiplier, level)
{
}
