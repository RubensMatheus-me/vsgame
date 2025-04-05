#include <SDL2/SDL.h>
#include "iostream"

class Game {
	public:
		Game();
		~Game();

		void init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);

		void handleEvents();
		void update();
		void render();
		void clean();

		bool running() {return isRunning;}
		
	private:
        bool isRunning;
        int updateCounter = 0;
        SDL_Window *window;
        SDL_Renderer *renderer;
};