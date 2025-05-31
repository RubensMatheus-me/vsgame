#include "Projectile.h"

Projectile::Projectile(const Vector& size, const Vector& position, const Vector& direction, float speed, float lifetime, std::unique_ptr<SpriteAnimation> animation, Entity* owner)
    : Entity(size, position, direction * speed, animation.get()), direction(direction), speed(speed), lifeRemaining(lifetime), animation(std::move(animation)), owner(owner)
{}


void Projectile::update(float dt) {
    Vector newPos = getPosition() + getSpeed() * dt;
    setPosition(newPos);

    lifeRemaining -= dt;
}

void Projectile::render(SDL_Renderer* renderer) {
    animation->render(renderer, getPosition().x , getPosition().y, SDL_FLIP_NONE);
}

bool Projectile::isAlive() const {
    return lifeRemaining > 0;
}

void Projectile::setAlive(bool alive) {
    lifeRemaining = alive ? lifeRemaining : 0;
}

void Projectile::expire() {
    lifeRemaining = 0;
}

Rect Projectile::getCollider() const {
    return Rect({getPosition().x, getPosition().y}, {getSize().x, getSize().y});
}
