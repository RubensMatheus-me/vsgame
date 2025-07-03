#include "BrassKnucklesMeleeAttack.h"

BrassKnucklesMeleeAttack::BrassKnucklesMeleeAttack(
    const Vector& size,
    const Vector& position,
    float damage,
    float duration,
    std::unique_ptr<SpriteAnimation> animation,
    Entity* owner
)
    : MeleeAttack(size, position, damage, duration, std::move(animation), owner)
{}

void BrassKnucklesMeleeAttack::update(float dt) {

    MeleeAttack::update(dt);
}

void BrassKnucklesMeleeAttack::render(SDL_Renderer* renderer) {
    MeleeAttack::render(renderer);
}
