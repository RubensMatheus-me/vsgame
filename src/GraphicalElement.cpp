#include <SDL2/SDL.h>
#include "GraphicalElement.h"
#include "SpriteAnimation.h"

GraphicalElement::GraphicalElement(float width, float height, SpriteAnimation* spriteAnimation) 
    : width(width), height(height), spriteAnimation(spriteAnimation) {}
