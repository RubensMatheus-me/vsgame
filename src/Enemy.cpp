#include "Enemy.h"
#include "TextureManager.h"

Enemy::Enemy(float width, float height, SDL_Texture *image, const Vector& pos, const Vector& speed,
             float hp, float atkRate, float movSpeed, float xpDrop, int spawnWeight)
    : Character(width, height, image, pos, speed, hp, atkRate, movSpeed),
      xpDrop(xpDrop), spawnWeight(spawnWeight) {}

void Enemy::render(SDL_Renderer* renderer) {
	SDL_Rect srcRect;
     srcRect.h = getHeight();
     srcRect.w = getWidth();
     srcRect.x = 0;
     srcRect.y = 0;

     SDL_Rect destRect;
     destRect.x = getPosition().x;
     destRect.y = getPosition().y;
     destRect.h = getHeight();
     destRect.w = getWidth();

	 SDL_Texture* tex = TextureManager::getTexture("slime");

     TextureManager::draw(tex, srcRect, destRect);

}

void Enemy::update(){}