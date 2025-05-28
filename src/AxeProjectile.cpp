#include "AxeProjectile.h"

AxeProjectile::AxeProjectile(const Vector& position, const Vector& direction,
                             float speed, float lifetime, std::unique_ptr<SpriteAnimation> animation, Entity* owner)
    : Projectile({getSize().x, getSize().y}, position, direction, speed, lifetime, std::move(animation), owner)
{}

void AxeProjectile::update(float dt) {
    Projectile::update(dt);
}

Rect AxeProjectile::getCollider() const {
    return Projectile::getCollider();
}

void AxeProjectile::render(SDL_Renderer* renderer, const Vector& camOffset) {
    if (animation) {
        animation->render(renderer, getPosition().x - camOffset.x, getPosition().y - camOffset.y, SDL_FLIP_NONE);
    }
}
