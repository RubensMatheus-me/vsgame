#include "Player.h"
#include "TextureManager.h"
#include "Keyboard.h"
#include "TickRate.h"
#include "Timer.h"
#include "SpriteAnimation.h"
#include "Rect.h"

Player::Player(const Vector& size, SpriteAnimation* spriteAnimation, const Vector& pos, const Vector& speed,
     float hp, float atkRate, float movSpeed, float xp, int level, float atkSpeed, bool isMoving, const Vector& direction, float damageCooldown, float invulnerabilityTime)
    : Character(size, pos, speed, hp, atkRate, movSpeed, spriteAnimation),
    xp(xp),
    level(level),
    atkSpeed(atkSpeed),
    isMoving(isMoving),
    direction(direction),
    facingRight(true),
    damageCooldown(damageCooldown),
    invulnerabilityTime(invulnerabilityTime){}

void Player::render(SDL_Renderer* renderer, const Vector& cameraOffSet) {
  float drawX = getPosition().x - cameraOffSet.x;
  float drawY = getPosition().y - cameraOffSet.y;

  spriteAnimation->render(renderer, drawX, drawY);

}

Rect Player::getCollider() const {
  return Rect({getPosition().x, getPosition().y}, {getSize().x, getSize().y});
}

void Player::update(float deltaTime) {
  if (attackCooldown > 0) {
            attackCooldown -= deltaTime;
  }
  if (damageCooldown > 0.0f) {
    damageCooldown -= deltaTime;
    
    if(damageCooldown < 0.0f) damageCooldown = 0.0f;
  } 
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

