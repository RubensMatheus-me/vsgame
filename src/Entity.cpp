#include "Entity.h"

Entity::Entity(float width, float height, SDL_Texture *image, const Vector& pos, const Vector& speed)
    : GraphicalElement(width, height, image), pos(pos), speed(speed) {}