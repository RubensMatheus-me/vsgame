#include "Entity.h"
#include "SpriteAnimation.h"

Entity::Entity(float width, float height, const Vector& pos, const Vector& speed, SpriteAnimation* spriteAnimation)
    : GraphicalElement(width, height, spriteAnimation), pos(pos), speed(speed) {}