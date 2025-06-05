#include "Player.h"
#include "TextureManager.h"
#include "Keyboard.h"
#include "TickRate.h"
#include "Timer.h"
#include "SpriteAnimation.h"
#include "Rect.h"
#include "Config.h"

Player::Player(const Vector& size, SpriteAnimation* spriteAnimation, const Vector& pos, const Vector& speed,
     float hp,  float currentHp, float atkRate, float movSpeed, float xp, int level, float xpNextLevel, float atkSpeed, bool isMoving, const Vector& direction, float damageCooldown, float invulnerabilityTime)
    : Character(size, pos, speed, hp, currentHp, atkRate, movSpeed, spriteAnimation),
    xp(xp),
    level(level),
    xpNextLevel(xpNextLevel),
    atkSpeed(atkSpeed),
    isMoving(isMoving),
    direction(direction),
    facingRight(true),
    damageCooldown(damageCooldown),
    invulnerabilityTime(invulnerabilityTime){}

void Player::render(SDL_Renderer* renderer) {
  spriteAnimation->render(renderer,  getPosition().x, getPosition().y);
}

void Player::setAnimationState(PlayerAnimationState newState) {
    if (currentAnimationState == newState) return;
    currentAnimationState = newState;

    switch (newState) {
        case PlayerAnimationState::IdleRight:
            spriteAnimation->play("idle-right");
            break;
        case PlayerAnimationState::IdleLeft:
            spriteAnimation->play("idle-left");
            break;
        case PlayerAnimationState::WalkRight:
            spriteAnimation->play("walk-right");
            break;
        case PlayerAnimationState::WalkLeft:
            spriteAnimation->play("walk-left");
            break;
        case PlayerAnimationState::Death:
            spriteAnimation->play("death-player");
            break;
    }
}

Rect Player::getCollider() const {
  return Rect({getPosition().x, getPosition().y}, {getSize().x, getSize().y});
}

void Player::update(float deltaTime) {
    if (getCurrentHp() <= 0.0f) {
        setAnimationState(PlayerAnimationState::Death);
        setSpeed({0.0f, 0.0f});
        setMovSpeed(0);
    } else if (isMoving) {
        if (direction.x > 0) {
            setAnimationState(PlayerAnimationState::WalkRight);
            facingRight = true;
        } else if (direction.x < 0) {
            setAnimationState(PlayerAnimationState::WalkLeft);
            facingRight = false;
        } else {
            setAnimationState(facingRight ? PlayerAnimationState::WalkRight : PlayerAnimationState::WalkLeft);
        }
    } else {
        setAnimationState(facingRight ? PlayerAnimationState::IdleRight : PlayerAnimationState::IdleLeft);
    }

    if (attackCooldown > 0.0f)
        attackCooldown -= deltaTime;

    if (damageCooldown > 0.0f) {
        damageCooldown -= deltaTime;
        if (damageCooldown < 0.0f) damageCooldown = 0.0f;
    }

    spriteAnimation->update(deltaTime);

    if (xp > xpNextLevel) {
        level++;
        xpNextLevel *= Config::NEXT_LEVEL_EXPERIENCE_RATE;
        xp = 0.0f;
    }
}

