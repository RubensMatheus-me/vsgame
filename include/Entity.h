#pragma once
#include <SDL2/SDL.h>
#include "Vector.h"
#include "Rect.h"
#include "GraphicalElement.h"

class Entity : public GraphicalElement {
	public:
		Entity(const Vector& size, const Vector& pos, const Vector& speed, SpriteAnimation* spriteAnimation);

		Vector getPosition() const { return this->pos; }
		Vector getSpeed() const { return this->speed; }

		Vector getSize() const { return this->size; }

		void setPosition(const Vector& newPos) { this->pos = newPos; }
		void setSpeed(const Vector& newSpeed) { this->speed = newSpeed; }
		void setSize(const Vector& newSize) { this->size = newSize; }

		virtual Rect getCollider() const = 0;


	private:
		Vector size;
		Vector pos;
		Vector speed;
};