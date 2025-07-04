#include "Player.h"
#include "TextureManager.h"
#include "Keyboard.h"
#include "TickRate.h"
#include "Timer.h"
#include "SpriteAnimation.h"
#include "Rect.h"
#include "Config.h"
#include "AudioManager.h"

Player::Player(const Vector &size, SpriteAnimation *spriteAnimation, const Vector &pos, const Vector &speed,
               float hp, float currentHp, float atkRate, float movSpeed, float xp, int level, float xpNextLevel, float atkSpeed,
               bool isMoving, const Vector &direction, float damageCooldown, float invulnerabilityTime)
    : Character(size, pos, speed, hp, currentHp, atkRate, movSpeed, spriteAnimation),
      xp(xp),
      level(level),
      xpNextLevel(xpNextLevel),
      atkSpeed(atkSpeed),
      isMoving(isMoving),
      direction(direction),
      facingRight(true),
      damageCooldown(damageCooldown),
      invulnerabilityTime(invulnerabilityTime),
      lastHp(hp) {}

void Player::render(SDL_Renderer *renderer)
{
    spriteAnimation->render(renderer, getPosition().x, getPosition().y);
}

void Player::setAnimationState(PlayerAnimationState newState)
{
    if (currentAnimationState == newState)
        return;
    currentAnimationState = newState;

    switch (newState)
    {
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
    case PlayerAnimationState::TakenDamage:
        spriteAnimation->play("player-taken-damage");
        break;
    case PlayerAnimationState::Death:
        AudioManager::getInstance().playSound("gameOver");
        spriteAnimation->play("death-player");
        break;
    }
}

Rect Player::getCollider() const
{
    return Rect({getPosition().x, getPosition().y}, {getSize().x, getSize().y});
}

void Player::update(float deltaTime)
{

    if (!dead && getCurrentHp() <= 0.0f)
    {
        dead = true;
        setAnimationState(PlayerAnimationState::Death);
        setSpeed({0.0f, 0.0f});
        setMovSpeed(0);
    }
    if (dead)
    {
        spriteAnimation->update(deltaTime);
        return;
    }
    else if (getCurrentHp() < lastHp)
    {
        hitAnimTimer = Config::HIT_ANIM_DURATION;
        setAnimationState(PlayerAnimationState::TakenDamage);
    }

    if (hitAnimTimer > 0.f)
    {
        hitAnimTimer -= deltaTime;
        if (hitAnimTimer < 0.f)
            hitAnimTimer = 0.f;
    }
    else
    {
        if (isMoving)
        {
            if (direction.x > 0)
            {
                setAnimationState(PlayerAnimationState::WalkRight);
                facingRight = true;
            }
            else if (direction.x < 0)
            {
                setAnimationState(PlayerAnimationState::WalkLeft);
                facingRight = false;
            }
            else
            {
                setAnimationState(facingRight ? PlayerAnimationState::WalkRight : PlayerAnimationState::WalkLeft);
            }
        }
        else
        {
            setAnimationState(facingRight ? PlayerAnimationState::IdleRight : PlayerAnimationState::IdleLeft);
        }
    }

    if (attackCooldown > 0.0f)
        attackCooldown -= deltaTime;

    if (damageCooldown > 0.0f)
    {
        damageCooldown -= deltaTime;
        if (damageCooldown < 0.0f)
            damageCooldown = 0.0f;
    }

    if (xp > xpNextLevel)
    {
        level++;
        xpNextLevel *= Config::NEXT_LEVEL_EXPERIENCE_RATE;
        xp = 0.0f;
    }

    lastHp = getCurrentHp();
    spriteAnimation->update(deltaTime);
}
