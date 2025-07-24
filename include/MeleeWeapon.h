#pragma once

#include "Weapon.h"
#include "MeleeAttack.h"

class MeleeWeapon : public Weapon {
public:
    MeleeWeapon(const Vector& size, SpriteAnimation* spriteAnimation, const std::string& description,
                float flatDamage, float flatAtkSpeed, float damageMultiplier,
                float atkSpeedMultiplier, int level);

    virtual ~MeleeWeapon() = default;

    std::vector<std::unique_ptr<MeleeAttack>>& getMeleeAttacks() { return meleeAttacks; }

private:
    std::vector<std::unique_ptr<MeleeAttack>> meleeAttacks;
};