#include "Item.h"

Item::Item(float x, float y, SDL_Surface *image)
	: GraphicElement(x, y, image){}

void Item::render(SDL_Renderer *image){}