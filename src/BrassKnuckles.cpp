#include "BrassKnuckles.h"
#include "MeleeAttack.h"

BrassKnuckles::BrassKnuckles(
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
)
    : Weapon(size, spriteAnimation, description, flatDamage, flatAtkSpeed, damageMultiplier, atkSpeedMultiplier, level),
      punchAnimation(punchAnimation),
      attackDuration(attackDuration)
{}

void BrassKnuckles::attack(const Vector& position, const Vector& direction, Entity* owner)
{

}

void BrassKnuckles::render(SDL_Renderer* renderer) {
    if (getSprite()) {
        getSprite()->render(renderer, 1, 1);
    }
}

void BrassKnuckles::update(float deltaTime) {
    if (getSprite()) {
        getSprite()->update(deltaTime);
    }
}
