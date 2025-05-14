#include <SDL2/SDL.h>
#include "GraphicalElement.h"
#include "SpriteAnimation.h"

GraphicalElement::GraphicalElement(const Vector& size, SpriteAnimation* spriteAnimation) 
    : size(size), spriteAnimation(spriteAnimation) {}
