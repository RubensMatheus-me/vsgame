#pragma once
#include <SDL2/SDL.h>		
#include "Vector.h"
#include "SpriteAnimation.h"

class GraphicalElement {
	public:
		GraphicalElement(const Vector& size, SpriteAnimation* spriteAnimation);
		virtual ~GraphicalElement() = default;

		Vector getSize() const { return this->size; }
		void setSize(Vector size) { this->size = size; }

		SpriteAnimation* getSprite() { return this->spriteAnimation; }

		virtual void render(SDL_Renderer *renderer) = 0;
		virtual void update(float deltaTime) = 0;

	private:
		Vector size;
		SpriteAnimation* spriteAnimation;
};
