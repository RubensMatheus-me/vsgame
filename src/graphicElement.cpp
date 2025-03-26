#include <SDL2/SDL.h>

class GraphicElement {
	float width;
	float height;
	SDL_Surface *image;

	public:
		GraphicElement(float width, float height, SDL_Surface *image) : width(width), height(height), image(image){}

		virtual void render(SDL_Renderer *renderer) = 0;

		float getWidth() {return width;}
		float getHeight() {return height;}
		SDL_Surface *getImage() {return image;}
};