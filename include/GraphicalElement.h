#include <SDL2/SDL.h>

class GraphicalElement {
	public:
		GraphicalElement(float width, float height, SDL_Texture *image);

		float getWidth() const { return this->width; }
		float getHeight() const { return this->height; }
		
		void setWidth(float width) { this->width = width; }
		void setHeight(float height) { this->height = height; }

		SDL_Texture* getSprite() const { return this->sprite; }

		virtual void render(SDL_Renderer *renderer) = 0;
		virtual void update() = 0;

	private:
		float width;
		float height;
		SDL_Texture* sprite;
};
