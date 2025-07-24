#pragma once
#include "RangedWeapon.h"
#include "SpriteAnimation.h"
#include "Projectile.h"
#include "Entity.h"

class Axe : public RangedWeapon {
public:
    Axe(const Vector& size, SpriteAnimation* spriteAnimation, const std::string& description,
        float flatDamage, float flatAtkSpeed, float damageMultiplier,
        float atkSpeedMultiplier, int level,
        SpriteAnimation* axeProjectileAnimation, float projectileSpeed, float projectileLifetime);

    void attack(const Vector& position, const Vector& direction, Entity* owner) override;
    void render(SDL_Renderer* renderer) override;
    void update(float deltaTime) override;

private:
    SpriteAnimation* axeProjectileAnimation;
    float projectileSpeed;
    float projectileLifetime;
};