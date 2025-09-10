#include "Lightning.h"
#include "TimedLifeTime.h"
#include "WaveMotion.h"
#include "Attack.h"
#include "OrbitMotion.h"
#include "Player.h"
#include <random>
#include "StraightLineMotion.h"
#include "Enemy.h"
#include "AnimationLifeTime.h"

Lightning::Lightning(const Vector &size, SpriteAnimation *spriteAnim, const std::string &description,
                     float flatDamage, float flatAtkSpeed, float damageMultiplier,
                     float atkSpeedMultiplier, int level, float cooldown, int id, float knockback)
    : Weapon(size, spriteAnim, description, flatDamage, flatAtkSpeed, damageMultiplier, atkSpeedMultiplier, level, cooldown, id, knockback)
{
}
Lightning::Lightning(const Vector &size,
                     SpriteAnimation *spriteAnimation,
                     const std::string &description)
    : Lightning(size, spriteAnimation, description, 15.0f, 10.0f, 10.0f, 10.0f, 1, 2.0f, 4, 100.0f)
{
}

void Lightning::attack(const Vector &position, const std::vector<std::unique_ptr<Enemy>> &enemies, Player *player)
{
    std::vector<Enemy *> candidates;

    float maxRange = 200.0f;
    float maxRangeSq = maxRange * maxRange;

    for (const auto &e : enemies)
    {
        float distSq = (e->getPosition() - position).length_squared();
        if (distSq <= maxRangeSq && e->getExpectedHp() > 0)
        {
            candidates.push_back(e.get());
        }
    }

    if (candidates.empty())
        return;

    static std::random_device rd;
    static std::mt19937 rng(rd());
    std::uniform_int_distribution<size_t> dist(0, candidates.size() - 1);

    Enemy *target = candidates[dist(rng)];
    Vector direction = {1.0f, 1.0f};
    // Vector direction = target->getPosition() - player->getPosition();
    direction.normalize();
    auto anim = std::make_unique<SpriteAnimation>();
    anim->addAnimation("lightning", "lightning", 0, 0, 64, 64, 6, false);
    anim->play("lightning");
    // anim->setFrameTime(25.0f);

    auto p = std::make_unique<Attack>(
        Vector(32.0f, 64.0f),
        target->getPosition() - Vector(0.0f, 60.0f),
        resolveDamage(player),
        std::move(anim),
        std::make_unique<StraightLineMotion>(
            direction,
            0.0f),
        std::make_unique<TimedLifetime>(0.5f),
        true,
        false);

    // auto anim = std::make_unique<SpriteAnimation>();
    // anim->addAnimation("lightning", "lightning", 0, 0, 32, 64, 6, false);
    // anim->play("lightning");
    // anim->setFrameTime(1000.0f);

    // auto p = std::make_unique<Attack>(
    //     Vector(32.0f, 64.0f),
    //     target->getPosition() - Vector(0.0f, 10.0f),
    //     8.0f,
    //     std::move(anim),
    //     std::make_unique<StraightLineMotion>(direction, 0.0f),
    //     std::make_unique<TimedLifetime>(1.0f),
    //     false);

    getAttacks().push_back(std::move(p));
    currentCooldown = cooldown / player->getAtkRate();
}

void Lightning::render(SDL_Renderer *renderer)
{
    if (getSprite())
    {
        getSprite()->render(renderer, 1, 1);
    }
}

void Lightning::levelUp(int levelUp)
{
    cooldown = cooldown - 0.25f;
    level++;
}