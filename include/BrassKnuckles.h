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
        float cooldown
    );

    void render(SDL_Renderer* renderer) override;
	void attack(const Vector& position, const Vector& direction, Player* owner) override;

};
