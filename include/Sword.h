#pragma once
#include "Weapon.h"
#include "SpriteAnimation.h"
#include "Projectile.h"
#include "Entity.h"

class Sword : public Weapon {
public:
    Sword(const Vector& size, SpriteAnimation* spriteAnimation, const std::string& description,
        float flatDamage, float flatAtkSpeed, float damageMultiplier,
        float atkSpeedMultiplier, int level,
        SpriteAnimation* swordProjectileAnimation, float projectileSpeed, float projectileLifetime);

    void attack(const Vector& position, const Vector& direction, std::vector<Projectile*>& projectiles, Entity* owner) override;

private:
    SpriteAnimation* swordProjectileAnimation;
    float projectileSpeed;
    float projectileLifetime;
};
