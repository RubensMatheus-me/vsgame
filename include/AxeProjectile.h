#pragma once
#include "Projectile.h"
#include "enums/AxeProjectileState.h"

class AxeProjectile : public Projectile {
	public:
		AxeProjectile(const Vector& position, const Vector& direction, float speed, float lifetime, std::unique_ptr<SpriteAnimation> animation, float damage, Entity* owner);

		void update(float dt) override;
		Rect getCollider() const override;
		void render(SDL_Renderer* renderer) override;

		void setAnimationState(AxeProjectileState newState);

	private:
		AxeProjectileState currentState;
		bool animationInitialized;
};
