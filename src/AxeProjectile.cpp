#include "AxeProjectile.h"

AxeProjectile::AxeProjectile(const Vector& position, const Vector& direction,
                             float speed, float lifetime, std::unique_ptr<SpriteAnimation> animation, Entity* owner)
    : Projectile({getSize().x, getSize().y}, position, direction, speed, lifetime, std::move(animation), owner), currentState(AxeProjectileState::RotateRight),
      animationInitialized(false)
{}

void AxeProjectile::update(float dt) {
    Projectile::update(dt);

	if (!animationInitialized) {
        animationInitialized = true;

        if (direction.x > 0.0f) {
        setAnimationState(AxeProjectileState::RotateRight);
		} else {
            setAnimationState(AxeProjectileState::RotateLeft);
		}
    }

	if (animation) {
        animation->update(dt);
    }
}

Rect AxeProjectile::getCollider() const {
    return Projectile::getCollider();
}

void AxeProjectile::render(SDL_Renderer* renderer) {
    if (animation) {
        animation->render(renderer, getPosition().x, getPosition().y, SDL_FLIP_NONE);
    }
}

void AxeProjectile::setAnimationState(AxeProjectileState newState) {
	if (currentState == newState) return;
    currentState = newState;

    switch (newState) {
        case AxeProjectileState::RotateRight:
            if (animation) animation->play("axe-right");
            break;
        case AxeProjectileState::RotateLeft:
            if (animation) animation->play("axe-left");
            break;
    }
}
