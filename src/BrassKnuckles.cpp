#include "BrassKnuckles.h"
#include "MeleeAttack.h"
#include "BrassKnucklesMeleeAttack.h"

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

void BrassKnuckles::attack(const Vector& position, const Vector& direction, std::vector<std::unique_ptr<MeleeAttack>>& meleeAttack, Entity* owner)
{
    Vector normalizedDir = direction;
	normalizedDir.normalize();
    Vector offset = normalizedDir * 30.0f;
    Vector attackPos = position + offset;

    auto anim = punchAnimation ? std::make_unique<SpriteAnimation>(*punchAnimation) : nullptr;

    float totalDamage = getTotalDamage();

    auto melee = std::make_unique<BrassKnucklesMeleeAttack>(
		Vector(32, 32),
		attackPos,
		totalDamage,
		attackDuration,
		std::move(anim),
		owner
	);
	

    meleeAttack.push_back(std::move(melee));
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
