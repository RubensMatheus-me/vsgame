#include "Attack.h"
#include "SpriteAnimation.h"
#include "Rect.h"
#include <SDL.h>  

Attack::Attack(const Vector& size,
               const Vector& position,
               float damage,
               std::unique_ptr<SpriteAnimation> animation,
               std::unique_ptr<IMotion> motion,
               std::unique_ptr<ILifetime> lifetime,
               bool destroyOnHit)
    : Entity(size, position, {}, animation.get()), 
      damage(damage),
      animation(std::move(animation)),
      motion(std::move(motion)),
      lifetime(std::move(lifetime)),
      destroyOnHit(destroyOnHit)
{
}

void Attack::update(float dt) {
    if (motion) {
        setPosition(getPosition() + motion->computeDelta(*this, dt));
    }

    if (lifetime) {
        lifetime->advance(dt);
        if (!lifetime->alive(*this)) {
            setAlive(false);
            return;
        }
    }

    if (animation) {
        animation->update(dt);
    }
}

void Attack::render(SDL_Renderer* renderer) {
    if (animation) {
        animation->render(renderer, getPosition().x, getPosition().y);
    }
}

Rect Attack::getCollider() const {
    return Rect(getPosition(), getSize());
}
