#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <map>
#include <vector>

class SpriteAnimation
{
public:
    SpriteAnimation();
    SpriteAnimation(const SpriteAnimation &other);

    void addAnimation(const std::string &name, const std::string &texture, int startX, int startY, int frameWidth, int frameHeight, int numFrames, bool loop, float frametime = 100.0f);
    void play(const std::string &animationName);
    void update(float deltaTime);
    void render(SDL_Renderer *renderer, int x, int y, bool flip = false);

    void setFrameTime(float newFrameTime) { this->frameTime = newFrameTime; }
    void setTextureName(std::string &newTextureName) { this->textureName = newTextureName; }
    int getCurrentFrame() { return this->currentFrame; }

    void setFlipX(bool flip);
    bool getFlipX() const;

    bool animationEnded();

    SDL_Rect getCurrentFrameRect() const
    {
        if (currentAnimation.empty() || animations.find(currentAnimation) == animations.end())
        {
            return {0, 0, 0, 0};
        }
        return animations.at(currentAnimation).frames[currentFrame];
    }

    std::string getCurrentTextureName() const
    {
        if (currentAnimation.empty() || animations.find(currentAnimation) == animations.end())
        {
            return "";
        }
        return animations.at(currentAnimation).textureName;
    }

    struct AnimationData
    {
        std::string textureName;
        std::vector<SDL_Rect> frames;
        bool loop;
        float frameTime;
    };

private:
    std::string textureName;
    std::map<std::string, AnimationData> animations;
    std::string currentAnimation;
    int currentFrame;
    float frameTime;
    float elapsedTime;
    bool flipX = false;
};