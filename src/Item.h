#pragma once
#include "GraphicElement.h"
#include <string>

class Item : public GraphicElement {
	std::string description;

	public:
		Item(float x, float y, SDL_Surface *image);
		void render(SDL_Renderer *image) override;
};