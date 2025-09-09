#include "Attack.h"
#include "SpriteAnimation.h"
#include "Rect.h"
#include <SDL.h>
#include "Enemy.h"
#include "DamagePopup.h"

Attack::Attack(const Vector &size,
               const Vector &position,
               float damage,
               std::unique_ptr<SpriteAnimation> animation,
               std::unique_ptr<IMotion> motion,
               std::unique_ptr<ILifetime> lifetime,
               bool stopHitboxOnHit,
               bool stopAnimationOnHit)
    : Entity(size, position, {}, animation.get()),
      damage(damage),
      animation(std::move(animation)),
      motion(std::move(motion)),
      lifetime(std::move(lifetime)),
      stopHitboxOnHit(stopHitboxOnHit),
      stopAnimationOnHit(stopAnimationOnHit)
{
}

void Attack::update(float dt)
{
    if (motion)
    {
        setPosition(getPosition() + motion->computeDelta(*this, dt));
    }

    if (lifetime)
    {
        lifetime->advance(dt);
        if (!lifetime->alive(*this))
        {
            setAlive(false);
            return;
        }
    }

    if (animation)
    {
        animation->update(dt);
    }
}

void Attack::checkCollisions(std::vector<std::unique_ptr<Enemy>> &enemies,
                             std::vector<std::unique_ptr<DamagePopup>> &popups,
                             SDL_Renderer *renderer,
                             TTF_Font *font)
{
    if (!isHitboxActive || !isAlive())
        return;

    for (auto &enemy : enemies)
    {
        if (!enemy->isAlive())
            continue;

        if (getCollider().intersects(enemy->getCollider()))
        {
            enemy->takeDamage(damage, popups, renderer, font);
            onHit();
            break;
        }
    }
}

void Attack::render(SDL_Renderer *renderer)
{
    if (animation)
    {
        animation->render(renderer, getPosition().x, getPosition().y);
    }
}

Rect Attack::getCollider() const
{
    return Rect(getPosition(), getSize());
}

void Attack::resetLifetime()
{
    lifetime->reset();
}

void Attack::onHit()
{
    if (stopAnimationOnHit)
    {
        setAlive(false);
    }
    if (stopHitboxOnHit)
    {
        isHitboxActive = false;
    }
}
