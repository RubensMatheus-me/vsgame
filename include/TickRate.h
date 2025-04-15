#pragma once
#include <SDL2/SDL.h>

class TickRate{
    public:
        TickRate();

        void update();
        float getDeltaTime() const {return this->deltaTime;};
        int getFPS() const {return this->fps;};
        Uint32 getCurrentTime() const {return this->currentTime;}


    private:
        Uint32 lastTime;
        Uint32 currentTime;
        float deltaTime;

        int frameCount;
        Uint32 fpsTimer;
        int fps;

};