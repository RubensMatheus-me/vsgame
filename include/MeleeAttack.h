#pragma once

#include "GraphicalElement.h"
#include "Rect.h"
#include "Entity.h"
#include "SpriteAnimation.h"
#include "Vector.h"
#include <memory>

class MeleeAttack : public GraphicalElement {
	public:
		MeleeAttack(const Vector& size, const Vector& position, const Vector& direction, float damage, std::unique_ptr<SpriteAnimation> animation, Entity* owner = nullptr);

		bool isAlive() const;
		Entity* getOwner() const;
	
		float getDamage() const {return damage;}

		void update(float dt) override;
		Rect getCollider() const;
		void render(SDL_Renderer* renderer) override;
		bool hasEnded();

		Vector getPosition() const { return this->pos; }

	private:
		float damage;
		Vector pos;
		Entity* owner;
		Vector direction;
		std::unique_ptr<SpriteAnimation> animation;
	};
	