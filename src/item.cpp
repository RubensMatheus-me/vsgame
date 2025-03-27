#pragma once
#include "GraphicElement.cpp"
class Item : public GraphicElement {
	public:
		Item(float x, float y, SDL_Surface *image) : GraphicElement(x, y, image){}
		void render(SDL_Renderer *image) override {};
};