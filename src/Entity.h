#include <SDL2/SDL.h>
#include "template.h"
#include "GraphicalElement.h"

class Entity : public GraphicalElement {

	public:
		Entity(Vector pos, Vector speed, float width, float height, SDL_Texture *texture);	
		Vector getPos();
		Vector getSpeed();
	private:
		Vector pos;
		Vector speed;
};