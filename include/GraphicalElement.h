#pragma once
#include <SDL2/SDL.h>		
#include "Vector.h"
#include "SpriteAnimation.h"

class GraphicalElement {
	public:
		GraphicalElement(float width, float height, SpriteAnimation* spriteAnimation);

		float getWidth() const { return this->width; }
		float getHeight() const { return this->height; }
		
		void setWidth(float width) { this->width = width; }
		void setHeight(float height) { this->height = height; }

		const SpriteAnimation* getSprite() const { return this->spriteAnimation; }

		virtual void render(SDL_Renderer *renderer, const Vector& cameraOffSet) = 0;
		virtual void update(float deltaTime) = 0;
		virtual SDL_Rect getCollider() const = 0;

	private:
		float width;
		float height;
		SpriteAnimation* spriteAnimation;
};
