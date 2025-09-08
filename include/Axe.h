#pragma once
#include "Weapon.h"
#include "SpriteAnimation.h"
#include "Projectile.h"
#include "Entity.h"

class Axe : public Weapon {
public:
    Axe(const Vector& size,
        SpriteAnimation* spriteAnimation,
        const std::string& description);

    Axe(const Vector& size,
        SpriteAnimation* spriteAnimation,
        const std::string& description,
        float flatDamage,
        float flatAtkSpeed,
        float damageMultiplier,
        float atkSpeedMultiplier,
        int level,
        float projectileSpeed,
        float projectileLifetime,
        float cooldown,
		int id,
        float knockback);

    void attack(const Vector &position, const std::vector<std::unique_ptr<Enemy>> &enemies, Player *player) override;
	void levelUp(int levelUp) override;
    void render(SDL_Renderer* renderer) override;
    Vector resolveClosestTarget(const std::vector<std::unique_ptr<Enemy>> &enemies, Vector playerPosition);

private:
    float projectileSpeed;
    float projectileLifetime;
};