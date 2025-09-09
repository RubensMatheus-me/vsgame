#include "BrassKnuckles.h"
#include "AnimationLifeTime.h"
#include "Attack.h"
#include "StraightLineMotion.h"
#include "Player.h"
#include "Weapon.h"

BrassKnuckles::BrassKnuckles(
    const Vector &size,
    SpriteAnimation *spriteAnimation,
    const std::string &description,
    float flatDamage,
    float flatAtkSpeed,
    float damageMultiplier,
    float atkSpeedMultiplier,
    int level,
    float cooldown,
    int id,
    float knockback)
    : Weapon(size, spriteAnimation, description, flatDamage, flatAtkSpeed, damageMultiplier, atkSpeedMultiplier, level, cooldown, id, knockback) {}
BrassKnuckles::BrassKnuckles(const Vector &size,
                 SpriteAnimation *spriteAnimation,
                 const std::string &description)
    : BrassKnuckles(size, spriteAnimation, description, 15.0f, 10.0f, 10.0f, 10.0f, 5, 8.0f, 3, 600.0f){}
void BrassKnuckles::attack(const Vector &position, const std::vector<std::unique_ptr<Enemy>> &enemies, Player *player)
{
    auto animation = std::make_unique<SpriteAnimation>();
    animation->addAnimation("attack-right", "brassKnuckles-attack", 0, 0, 64, 64, 4, false);
    animation->addAnimation("attack-left", "brassKnuckles-attack", 256, 0, 64, 64, 4, false);

    Vector newPosition;
    Vector direction;

    if (player->getPlayerFacingDirection()[0] == 1)
    {
        animation->play("attack-right");
        newPosition = position + Vector(15.0f, 0.0f);
        direction = {1.0f, 0.0f};
    }
    else
    {
        animation->play("attack-left");
        newPosition = position - Vector(48.0f, 0.0f);
        direction = {-1.0f, 0.0f};
    }
    
    direction.normalize();
    float playerHeight = player->getSize()[1]/2;

    auto p = std::make_unique<Attack>(
        Vector(64.0f, 64.0f),
        newPosition - Vector(0.0f, playerHeight),
        5.0f,
        std::move(animation),
        std::make_unique<StraightLineMotion>(direction, 300.0f),
        std::make_unique<AnimationLifeTime>(),
        false,
        false);

    getAttacks().push_back(std::move(p));
    currentCooldown = cooldown / player->getAtkRate();
}

void BrassKnuckles::render(SDL_Renderer *renderer)
{
    if (getSprite())
    {
        getSprite()->render(renderer, 1, 1);
    }
}

void BrassKnuckles::levelUp(int levelUp)
{
    level++;
    if(cooldown > 1) {
        cooldown = cooldown - level;
    }
}
