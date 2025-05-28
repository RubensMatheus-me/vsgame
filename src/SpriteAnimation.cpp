#include "SpriteAnimation.h"
#include "TextureManager.h"

SpriteAnimation::SpriteAnimation() : currentFrame(0), frameTime(100.0f), elapsedTime(0.1f){}

SpriteAnimation::SpriteAnimation(const SpriteAnimation& other)
    : textureName(other.textureName),
      animations(other.animations),
      currentAnimation(other.currentAnimation),
      currentFrame(other.currentFrame),
      frameTime(other.frameTime),
      elapsedTime(other.elapsedTime)
{}

void SpriteAnimation::addAnimation(const std::string& name, const std::string& texture, int startX, int startY, int frameWidth, int frameHeight, int numFrames) {
    std::vector<SDL_Rect> frames;
    
    for(int i = 0; i < numFrames; i++) {
        SDL_Rect frame = {startX + i * frameWidth, startY, frameWidth, frameHeight};
        frames.push_back(frame);
    }
    animations[name] = {texture, frames};
}

void SpriteAnimation::play(const std::string& animationName) {
    if(animationName != currentAnimation) {
        currentAnimation = animationName;
        currentFrame = 0;
        elapsedTime = 0.0f;
    }
    
}

void SpriteAnimation::update(float deltaTime) {
    if (currentAnimation.empty() || animations.find(currentAnimation) == animations.end()) return;

    elapsedTime += deltaTime * 1000.0f;

    if(elapsedTime >= frameTime) {
        currentFrame = (currentFrame + 1) % animations[currentAnimation].frames.size();
        elapsedTime = 0.0f;
    }
}

void SpriteAnimation::render(SDL_Renderer* renderer, int x, int y, bool flip) {
    if (currentAnimation.empty() || animations.find(currentAnimation) == animations.end()) return;

    const AnimationData& anim = animations[currentAnimation];
    SDL_Texture* texture = TextureManager::getTexture(anim.textureName);
    if(!texture) return;

    SDL_Rect srcRect = anim.frames[currentFrame];
    SDL_Rect destRect = {x, y, srcRect.w, srcRect.h};
    SDL_RendererFlip flipFlag = flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

    SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, 0, nullptr, flipFlag);
}