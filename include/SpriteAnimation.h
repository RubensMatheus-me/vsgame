#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <map>
#include <vector>


class SpriteAnimation {
    public:
        SpriteAnimation();
        SpriteAnimation(const SpriteAnimation& other);

        void addAnimation(const std::string& name, const std::string& texture, int startX, int startY, int frameWidth, int frameHeight, int numFrames);
        void play(const std::string& animationName);
        void update(float deltaTime);
        void render(SDL_Renderer* renderer, int x, int y, bool flip = false);
        
        void setFrameTime(float newFrameTime) {this->frameTime = newFrameTime;}
        void setTextureName(std::string& newTextureName) {this->textureName = newTextureName;}

        struct AnimationData {
            std::string textureName;
            std::vector<SDL_Rect> frames;
        };

    private:
        std::string textureName;
        std::map<std::string, AnimationData> animations;
        std::string currentAnimation;
        int currentFrame;
        float frameTime;
        float elapsedTime;
};