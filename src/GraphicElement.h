#pragma once
#include <SDL2/SDL.h>

class GraphicElement {
	float width;
	float height;
	
	SDL_Surface *image;

	public:
		GraphicElement(float width, float height, SDL_Surface *image);
        virtual ~GraphicElement() = default;

		virtual void render(SDL_Renderer *renderer) = 0;

		float getWidth() const;
		float getHeight() const;
		SDL_Surface *getImage() const;
};