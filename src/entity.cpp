#include "Template.h"
#include "GraphicElement.cpp"
#include <SDL2/SDL.h>

class Entity : public GraphicElement{
	Vector pos;
	Vector speed;
	public:

		Entity(Vector pos, Vector speed, float width, float height, SDL_Surface *image) 
		: GraphicElement(width, height, image), pos(pos), speed(speed){}

		void virtual render(SDL_Renderer *renderer) override {}

		Vector getPosition() const { return pos; }
    	Vector getSpeed() const { return speed; }
};