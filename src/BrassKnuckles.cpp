#include "BrassKnuckles.h"
#include "MeleeAttack.h"
#include "AxeProjectile.h"
#include "TimedLifetime.h"
#include "WaveMotion.h"
#include "Attack.h"
#include "OrbitMotion.h"
#include "StraightLineMotion.h"
#include "Player.h"

BrassKnuckles::BrassKnuckles(
    const Vector& size,
    SpriteAnimation* spriteAnimation,
    const std::string& description,
    float flatDamage,
    float flatAtkSpeed,
    float damageMultiplier,
    float atkSpeedMultiplier,
    int level,
    float cooldown
)
    : Weapon(size, spriteAnimation, description, flatDamage, flatAtkSpeed, damageMultiplier, atkSpeedMultiplier, level, cooldown){}

void BrassKnuckles::attack(const Vector& position, const Vector& direction, Player* owner) {
    auto animation = std::make_unique<SpriteAnimation>(); 
	animation->addAnimation("attack", "brassKnuckles", 0, 0, 64, 32, 4, false);
    animation->play("attack");
    Vector newPosition;

    if(owner->getPlayerFacingDirection()[0] == 1) {   
        newPosition = position + Vector(30.0f, 0.0f);
    } else {
        newPosition = position - Vector(64.0f, 0.0f);
    }

    auto p = std::make_unique<Attack>(
        Vector(144.0f, 32.0f),
        newPosition,
        50.0f,
        std::move(animation),
        std::make_unique<StraightLineMotion>(direction, 0.0f),
        std::make_unique<TimedLifetime>(1.0f),
        false
    );

    getAttacks().push_back(std::move(p));
    currentCooldown = cooldown / owner->getAtkRate();
}

void BrassKnuckles::render(SDL_Renderer* renderer) {
    if (getSprite()) {
        getSprite()->render(renderer, 1, 1);
    }
}
