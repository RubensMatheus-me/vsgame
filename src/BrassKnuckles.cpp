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
    : MeleeWeapon(size, spriteAnimation, description, flatDamage, flatAtkSpeed, damageMultiplier, atkSpeedMultiplier, level),
      punchAnimation(punchAnimation),
      attackDuration(attackDuration)
{}

void BrassKnuckles::attack(const Vector& position, const Vector& direction, Entity* owner) {
    auto animation = std::make_unique<SpriteAnimation>(); 
	animation->addAnimation("attack", "brassKnuckles", 0, 0, 64, 32, 4, false);
    animation->play("attack");
    Vector newPosition;
    if(direction[0] == 1) {
        newPosition = position + Vector(30.0f, 0.0f);
    } else {
        newPosition = position - Vector(64.0f, 0.0f);
    }

    auto p = std::make_unique<MeleeAttack>(
        Vector(144.0f, 32.0f),
        newPosition,
        direction,
        50.0f,
        std::move(animation),  
        owner
    );

    getMeleeAttacks().push_back(std::move(p));
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
