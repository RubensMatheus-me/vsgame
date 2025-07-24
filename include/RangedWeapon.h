#pragma once
#include "Weapon.h"
#include "Projectile.h"

class RangedWeapon : public Weapon {
public:
    RangedWeapon(const Vector& size, SpriteAnimation* spriteAnimation, const std::string& description,
                 float flatDamage, float flatAtkSpeed, float damageMultiplier,
                 float atkSpeedMultiplier, int level);

	virtual ~RangedWeapon() = default;

    std::vector<std::unique_ptr<Projectile>>& getProjectiles() { return projectiles; }

private:
    std::vector<std::unique_ptr<Projectile>> projectiles;
};