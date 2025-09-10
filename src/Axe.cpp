#include "Axe.h"
#include "AxeProjectile.h"
#include "TimedLifeTime.h"
#include "Attack.h"
#include "Player.h"
#include "StraightLineMotion.h"
#include "Enemy.h"

Axe::Axe(const Vector &size, SpriteAnimation *spriteAnim, const std::string &description,
         float flatDamage, float flatAtkSpeed, float damageMultiplier,
         float atkSpeedMultiplier, int level, float projSpeed, float projLifetime, float cooldown, int id, float knockback)
    : Weapon(size, spriteAnim, description, flatDamage, flatAtkSpeed, damageMultiplier, atkSpeedMultiplier, level, cooldown, id, knockback),
      projectileSpeed(projSpeed),
      projectileLifetime(projLifetime)
{
}
Axe::Axe(const Vector &size,
         SpriteAnimation *spriteAnimation,
         const std::string &description)
    : Axe(size, spriteAnimation, description, 10.0f, 10.0f, 10.0f, 10.0f, 1, 150.0f, 1, 3, 1, 100.0f)
{
}

void Axe::attack(const Vector &position, const std::vector<std::unique_ptr<Enemy>> &enemies, Player *player)
{
    Vector enemyPos = resolveClosestTarget(enemies, player->getPosition());
    Vector direction = enemyPos - player->getPosition();
    direction.normalize();
    
    for(int i = 0; i <=level/2; i++) {
        auto anim = std::make_unique<SpriteAnimation>();
        anim->addAnimation("axe-idle", "axe", 0, 0, 32, 32, 1, false);
        anim->addAnimation("axe-right", "axe", 0, 0, 32, 32, 5, true);
        anim->addAnimation("axe-left", "axe", 160, 0, 32, 32, 5, true);
        anim->play("axe-right");

        auto p = std::make_unique<Attack>(
            Vector(50.0f, 50.0f),
            position + Vector(10.0f*(i+1), 0.0f),
            resolveDamage(player),
            std::move(anim),
            std::make_unique<StraightLineMotion>(
                direction,
                200.0f),
            std::make_unique<TimedLifetime>(5.0f),
            true,
            true);

        getAttacks().push_back(std::move(p));
    }

    currentCooldown = cooldown / player->getAtkRate();
}

void Axe::render(SDL_Renderer *renderer)
{
    if (getSprite())
    {
        getSprite()->render(renderer, 1, 1);
    }
}

void Axe::levelUp(int levelUp)
{
    level++;
}

Vector Axe::resolveClosestTarget(const std::vector<std::unique_ptr<Enemy>> &enemies, Vector playerPosition) {
    Enemy *target = nullptr;
    float closestDistanceSq = std::numeric_limits<float>::max();

    for (const auto &e : enemies)
    {
        float distSq = (e->getPosition() - playerPosition).length_squared();
        if (distSq < closestDistanceSq && e->getExpectedHp() > 0)
        {
            closestDistanceSq = distSq;
            target = e.get();
        }
    }

    return target->getPosition();
}
