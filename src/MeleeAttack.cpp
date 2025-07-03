#include "MeleeAttack.h"

MeleeAttack::MeleeAttack(const Vector& size, const Vector& position, float damage, float duration, std::unique_ptr<SpriteAnimation> animation, Entity* owner)
	: GraphicalElement(size, animation.get()), 
	  damage(damage), duration(duration), timeElapsed(0.f), owner(owner), animation(std::move(animation)) {}