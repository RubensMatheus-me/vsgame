#pragma once
#include <SDL2/SDL.h>

class Scene {
    public:
        virtual ~Scene() = default; 
        virtual void init() = 0;
        virtual void handleInput(SDL_Event& event) = 0;
        virtual void update(float dt) = 0;
        virtual void render() = 0;
        virtual void cleanUp() = 0;
        
};
