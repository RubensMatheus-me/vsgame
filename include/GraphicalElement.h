#pragma once
#include <SDL2/SDL.h>		
#include "Vector.h"
#include "SpriteAnimation.h"

class GraphicalElement {
	public:
		GraphicalElement(const Vector& size, SpriteAnimation* spriteAnimation);

		Vector getSize() const { return this->size; }

		SpriteAnimation* getSprite() { return this->spriteAnimation; }

		virtual void render(SDL_Renderer *renderer, const Vector& cameraOffSet) = 0;
		virtual void update(float deltaTime) = 0;

	private:
		Vector size;
		SpriteAnimation* spriteAnimation;
};
