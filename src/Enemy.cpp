#include "Enemy.h"
#include "TextureManager.h"
#include "SpriteAnimation.h"

Enemy::Enemy(float width, float height, SpriteAnimation* spriteAnimation, std::unique_ptr<SpriteAnimation> anim, const Vector& pos, const Vector& speed,
     float hp, float atkRate, float movSpeed, float xpDrop, int spawnWeight)
     : Character(width, height, pos, speed, hp, atkRate, movSpeed, spriteAnimation), animation(std::move(anim)),
     xpDrop(xpDrop), spawnWeight(spawnWeight) {}

void Enemy::render(SDL_Renderer* renderer, const Vector& cameraOffSet) {
     
     float drawX = getPosition().x - cameraOffSet.x;
     float drawY = getPosition().y - cameraOffSet.y;

     animation->render(renderer, drawX, drawY);

}

SDL_Rect Enemy::getCollider() const {
     SDL_Rect rect;
     rect.x = getPosition().x;
     rect.y = getPosition().y;
     rect.h = getHeight();
     rect.w = getWidth();

     return rect;
}

void Enemy::update(float deltaTime){
     if(target) {
          Vector direction = target->getPosition() - getPosition();
          direction.normalize();

          Vector velocity = direction * getMovSpeed() * deltaTime;
          setPosition(getPosition() + velocity);
     } 
     if(animation) {
          animation->update(deltaTime);
     }
}