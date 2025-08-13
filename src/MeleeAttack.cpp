#include "MeleeAttack.h"

MeleeAttack::MeleeAttack(const Vector& size, const Vector& position, const Vector& direction, float damage, std::unique_ptr<SpriteAnimation> animation, Entity* owner)
	: GraphicalElement(size, animation.get()), 
	  direction(direction), damage(damage), owner(owner), animation(std::move(animation)), pos(position) {}


void MeleeAttack::update(float dt) {
	animation->update(dt);
}

bool MeleeAttack::hasEnded() {
	return animation->animationEnded();
}

void MeleeAttack::render(SDL_Renderer* renderer) {
    if (animation) {
        Vector drawPos = getPosition();
        if (direction[0] == 0) { 
            drawPos.x -= animation->currentFrame();
        }
        animation->render(renderer, drawPos.x, drawPos.y, SDL_FLIP_HORIZONTAL, false);
    }
}

Rect MeleeAttack::getCollider() const {
	return Rect({getPosition().x, getPosition().y}, {getSize().x, getSize().y});
}
