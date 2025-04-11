#pragma once
#include <SDL2/SDL.h>
#include "Vector.h"
#include "GraphicalElement.h"

class Entity : public GraphicalElement {
	public:
		Entity(float width, float height, SDL_Texture *image, const Vector& pos, const Vector& speed);

		Vector getPosition() const { return this->pos; }
		Vector getSpeed() const { return this->speed; }

		void setPosition(const Vector& newPos) { this->pos = newPos; }
		void setSpeed(const Vector& newSpeed) { this->speed = newSpeed; }

	private:
		Vector pos;
		Vector speed;
};