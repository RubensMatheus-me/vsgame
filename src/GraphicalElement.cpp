#include <SDL2/SDL.h>
#include "GraphicalElement.h"

GraphicalElement::GraphicalElement(float width, float height, SDL_Texture *sprite) 
: width(this->width), height(this->height), sprite(this->sprite){}

float GraphicalElement::getHeight() {
	return height;
}

float GraphicalElement::getWidth() {
	return width;
}

SDL_Texture* GraphicalElement::getSprite() {
	return sprite;
}

