#pragma once

#include "SpriteAnimation.h"
#include "Weapon.h"
#include <vector>

class BrassKnuckles : public Weapon {
public:
    BrassKnuckles(const Vector& size,
        SpriteAnimation* spriteAnimation,
        const std::string& description);
    BrassKnuckles(
        const Vector& size,
        SpriteAnimation* spriteAnimation,
        const std::string& description,
        float flatDamage,
        float flatAtkSpeed,
        float damageMultiplier,
        float atkSpeedMultiplier,
        int level,
        float cooldown,
		int id,
        float knockback
    );

    void render(SDL_Renderer* renderer) override;
    void attack(const Vector &position, const std::vector<std::unique_ptr<Enemy>> &enemies, Player *player) override;
	void levelUp(int levelUp) override;

};
