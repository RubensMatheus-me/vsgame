#pragma once

#include "MeleeAttack.h"

class BrassKnucklesMeleeAttack : public MeleeAttack {
public:
    BrassKnucklesMeleeAttack(
        const Vector& size,
        const Vector& position,
        float damage,
        float duration,
        std::unique_ptr<SpriteAnimation> animation,
        Entity* owner = nullptr
    );

    void update(float dt) override;
    void render(SDL_Renderer* renderer) override;
};
