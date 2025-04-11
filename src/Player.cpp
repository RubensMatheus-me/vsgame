#include "Player.h"
#include "TextureManager.h"
#include "Keyboard.h"

Player::Player(float width, float height, SDL_Texture *image, const Vector& pos, const Vector& speed,
     float hp, float atkRate, float movSpeed, float xp, int level, float atkSpeed)
    : Character(width, height, image, pos, speed, hp, atkRate, movSpeed), xp(xp), level(level), atkSpeed(atkSpeed) {}

void Player::render(SDL_Renderer* renderer) {
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

     SDL_Texture* tex = TextureManager::getTexture("stickman");

     TextureManager::draw(tex, srcRect, destRect);
}

void Player::update() {

}