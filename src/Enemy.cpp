#include "Enemy.h"
#include "TextureManager.h"

Enemy::Enemy(float width, float height, SDL_Texture *image, const Vector& pos, const Vector& speed,
             float hp, float atkRate, float movSpeed, float xpDrop, int spawnWeight)
    : Character(width, height, image, pos, speed, hp, atkRate, movSpeed),
      xpDrop(xpDrop), spawnWeight(spawnWeight) {}

void Enemy::render(SDL_Renderer* renderer, const Vector& cameraOffSet) {
	SDL_Rect srcRect;
     srcRect.h = getHeight();
     srcRect.w = getWidth();
     srcRect.x = 0;
     srcRect.y = 0;

     SDL_Rect destRect;
     destRect.x = getPosition().x - cameraOffSet.x;
     destRect.y = getPosition().y - cameraOffSet.y;
     destRect.h = getHeight();
     destRect.w = getWidth();

	 SDL_Texture* tex = TextureManager::getTexture("slime");

     TextureManager::draw(tex, srcRect, destRect);

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
}