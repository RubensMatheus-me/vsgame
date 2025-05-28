#include "Entity.h"
#include "SpriteAnimation.h"

Entity::Entity(const Vector& size, const Vector& pos, const Vector& speed, SpriteAnimation* spriteAnimation)
    : GraphicalElement(size, spriteAnimation), pos(pos), speed(speed), alive(true) {}