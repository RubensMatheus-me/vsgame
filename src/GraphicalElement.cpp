#include <SDL2/SDL.h>
#include "GraphicalElement.h"

GraphicalElement::GraphicalElement(float width, float height, SDL_Texture *sprite) 
    : width(width), height(height), sprite(sprite) {}
