#include "Chakram.h"
#include "TimedLifeTime.h"
#include "WaveMotion.h"
#include "Attack.h"
#include "OrbitMotion.h"
#include "Player.h"

Chakram::Chakram(const Vector &size, SpriteAnimation *spriteAnim, const std::string &description,
                 float flatDamage, float flatAtkSpeed, float damageMultiplier,
                 float atkSpeedMultiplier, int level, float cooldown, int id, float knockback)
    : Weapon(size, spriteAnim, description, flatDamage, flatAtkSpeed, damageMultiplier, atkSpeedMultiplier, level, cooldown, id, knockback)
{
}
Chakram::Chakram(const Vector &size,
                 SpriteAnimation *spriteAnimation,
                 const std::string &description)
    : Chakram(size, spriteAnimation, description, 0.5f, 10.0f, 10.0f, 10.0f, 3, 10.0f, 3, 400.0f)
{
}

void Chakram::attack(const Vector &position, const std::vector<std::unique_ptr<Enemy>> &enemies, Player *player)
{

    int lifeTime = 6.0f + level;
    float angle = 360.0f / (level + 1);

    for (int i = 0; i <= level; i++)
    {

        auto anim = std::make_unique<SpriteAnimation>();
        anim->addAnimation("chakram-spin", "chakram", 0, 0, 32, 32, 4, true);
        anim->play("chakram-spin");

        auto attack = std::make_unique<Attack>(
            Vector(32.0f, 32.0f),
            position + Vector(10.0f, 0.0f),
            resolveDamage(player),
            std::move(anim),
            std::make_unique<OrbitMotion>(
                player,
                100.0f,
                60.0f + (10.0f + level),
                angle * i),
            std::make_unique<TimedLifetime>(lifeTime),
            false,
            false);

        getAttacks().push_back(std::move(attack));
    }
    currentCooldown = cooldown / player->getAtkRate();
}

void Chakram::render(SDL_Renderer *renderer)
{
    if (getSprite())
    {
        getSprite()->render(renderer, 1, 1);
    }
}

void Chakram::levelUp(int levelUp)
{
    level++;
}