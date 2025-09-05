#pragma once

#include "SpriteAnimation.h"
#include "Weapon.h"
#include <vector>

class BrassKnuckles : public Weapon {
public:
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
		int id
    );

    void render(SDL_Renderer* renderer) override;
	void attack(const Vector& position, const Vector& direction, Player* owner) override;
	void levelUp(int levelUp) override;

};
