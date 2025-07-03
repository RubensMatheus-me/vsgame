#pragma once
#include "Weapon.h"
#include "SpriteAnimation.h"
#include "Projectile.h"
#include "Entity.h"

class Axe : public Weapon {
public:
    Axe(const Vector& size, SpriteAnimation* spriteAnimation, const std::string& description,
        float flatDamage, float flatAtkSpeed, float damageMultiplier,
        float atkSpeedMultiplier, int level,
        SpriteAnimation* axeProjectileAnimation, float projectileSpeed, float projectileLifetime);

    void attack(const Vector& position, const Vector& direction,  std::vector<std::unique_ptr<Projectile>>& projectiles, Entity* owner) override;
	void render(SDL_Renderer* renderer) override;
	void update(float deltaTime) override;
	
private:
    SpriteAnimation* axeProjectileAnimation;
    float projectileSpeed;
    float projectileLifetime;
};
