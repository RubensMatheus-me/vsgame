#pragma once

#include "GraphicalElement.h"
#include "Rect.h"
#include "Entity.h"
#include "SpriteAnimation.h"
#include "Vector.h"
#include <memory>

class MeleeAttack : public GraphicalElement {
	public:
		MeleeAttack(const Vector& size, const Vector& position,float damage, float duration, std::unique_ptr<SpriteAnimation> animation, Entity* owner = nullptr);

		bool isAlive() const;
		Entity* getOwner() const;
	
		float getDamage() const;
		Rect getCollider() const;
	
	private:
		float damage;
		float duration;
		float timeElapsed;
		Entity* owner;
		std::unique_ptr<SpriteAnimation> animation;
	};
	