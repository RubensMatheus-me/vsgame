#include "Player.h"
#include "TextureManager.h"
#include "Keyboard.h"
#include "TickRate.h"
#include "Timer.h"
#include "SpriteAnimation.h"

Player::Player(float width, float height, SpriteAnimation* spriteAnimation, const Vector& pos, const Vector& speed,
     float hp, float atkRate, float movSpeed, float xp, int level, float atkSpeed, bool isMoving, Vector& direction)
    : Character(width, height, pos, speed, hp, atkRate, movSpeed, spriteAnimation), xp(xp), level(level), atkSpeed(atkSpeed), isMoving(isMoving), direction(direction),
    facingRight(true) {}

void Player::render(SDL_Renderer* renderer, const Vector& cameraOffSet) {
     float drawX = getPosition().x - cameraOffSet.x;
     float drawY = getPosition().y - cameraOffSet.y;

     spriteAnimation->render(renderer, drawX, drawY);
}

SDL_Rect Player::getCollider() const {
     SDL_Rect rect;
     rect.x = getPosition().x;
     rect.y = getPosition().y;
     rect.h = getHeight();
     rect.w = getWidth();

     return rect;
}

void Player::update(float deltaTime) {
     if (isMoving) {
          if (direction.x > 0) {
            spriteAnimation->play("walk-right");
              facingRight = true;
          } else if (direction.x < 0) {
            spriteAnimation->play("walk-left");
              facingRight = false;
          } else {
            spriteAnimation->play(facingRight ? "walk-right" : "walk-left");
          }
      } else {
        spriteAnimation->play(facingRight ? "idle-right" : "idle-left");
      }
      
      spriteAnimation->update(deltaTime);
}

