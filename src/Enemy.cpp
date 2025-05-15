#include "Enemy.h"
#include "TextureManager.h"
#include "SpriteAnimation.h"

Enemy::Enemy(const Vector& size, SpriteAnimation* spriteAnimation, std::unique_ptr<SpriteAnimation> anim, const Vector& pos, const Vector& speed,
     float hp, float atkRate, float movSpeed, float xpDrop, int spawnWeight)
     : Character(size, pos, speed, hp, atkRate, movSpeed, spriteAnimation), animation(std::move(anim)),
     xpDrop(xpDrop), spawnWeight(spawnWeight) {}

void Enemy::render(SDL_Renderer* renderer, const Vector& cameraOffSet) {
     
     float drawX = getPosition().x - cameraOffSet.x;
     float drawY = getPosition().y - cameraOffSet.y;

     animation->render(renderer, drawX, drawY);

}

Rect Enemy::getCollider() const {
     return Rect(getPosition().x, getPosition().y, getSize().x, getSize().y);
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