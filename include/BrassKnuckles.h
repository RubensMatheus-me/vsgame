#pragma once

#include "Weapon.h"
#include "SpriteAnimation.h"
#include "MeleeAttack.h"
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
        SpriteAnimation* punchAnimation,
        float attackDuration
    );

    void render(SDL_Renderer* renderer) override;
    void update(float deltaTime) override;
	void attack(const Vector& position, const Vector& direction, std::vector<std::unique_ptr<MeleeAttack>>& meleeAttack, Entity* owner) override;

private:
    SpriteAnimation* punchAnimation;
    float attackDuration;
};
