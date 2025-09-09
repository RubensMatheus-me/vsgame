#include "Enemy.h"
#include "TextureManager.h"
#include "SpriteAnimation.h"

Enemy::Enemy(const Vector &size, SpriteAnimation *spriteAnimation, std::unique_ptr<SpriteAnimation> anim, const Vector &pos, const Vector &speed,
             float hp, float atkRate, float currentHp, float movSpeed, float xpDrop, int spawnWeight, float baseAtk, float expectedHp)
    : Character(size, pos, speed, hp, currentHp, atkRate, movSpeed, spriteAnimation), animation(std::move(anim)),
      xpDrop(xpDrop), spawnWeight(spawnWeight), baseAtk(baseAtk), expectedHp(expectedHp) {}

void Enemy::render(SDL_Renderer *renderer)
{
    animation->render(renderer, getPosition().x, getPosition().y, flipX);
}

Rect Enemy::getCollider() const
{
    return Rect({getPosition().x, getPosition().y}, {getSize().x, getSize().y});
}

void Enemy::update(float deltaTime)
{
    Vector moveVelocity(0, 0);
    if (target)
    {
        Vector direction = target->getPosition() - getPosition();
        direction.normalize();
        moveVelocity = direction * getMovSpeed();

        if (animation)
        {
            if (direction.x > 0)
            {
                animation->setFlipX(true);
            }
            else
            {
                animation->setFlipX(false);
            }
        }
    }

    Vector totalVelocity = moveVelocity + knockbackVelocity;
    setPosition(getPosition() + totalVelocity * deltaTime);

    float friction = 5.0f;
    knockbackVelocity = knockbackVelocity * (1.0f - friction * deltaTime);

    if (animation)
        animation->update(deltaTime);
}

void Enemy::takeDamage(float dmg, std::vector<std::unique_ptr<DamagePopup>> &popups, SDL_Renderer *renderer, TTF_Font *font)
{

    setCurrentHp(getCurrentHp() - dmg);

    Vector popupPos = getPosition();
    popupPos.x += getSize().x / 2.0f;
    popupPos.y -= getSize().y / 4.0f;

    popups.push_back(std::make_unique<DamagePopup>(renderer, font, popupPos, static_cast<int>(dmg)));

    if (getCurrentHp() <= 0)
    {
        setAlive(false);
        if (animation)
            animation->play("deathSprite");
    }
}

void Enemy::applyKnockback(const Vector &direction, float force)
{
    Vector dir = direction;
    dir.normalize();
    knockbackVelocity = dir * force;
}