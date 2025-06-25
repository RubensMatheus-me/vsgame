#include "Enemy.h"
#include "TextureManager.h"
#include "SpriteAnimation.h"

Enemy::Enemy(const Vector& size, SpriteAnimation* spriteAnimation, std::unique_ptr<SpriteAnimation> anim, const Vector& pos, const Vector& speed,
     float hp, float atkRate, float currentHp, float movSpeed, float xpDrop, int spawnWeight, float baseAtk)
     : Character(size, pos, speed, hp, currentHp, atkRate, movSpeed, spriteAnimation), animation(std::move(anim)),
     xpDrop(xpDrop), spawnWeight(spawnWeight), baseAtk(baseAtk) {}

void Enemy::render(SDL_Renderer* renderer) {
     animation->render(renderer, getPosition().x, getPosition().y);

}

Rect Enemy::getCollider() const {
    return Rect({getPosition().x, getPosition().y}, {getSize().x, getSize().y});
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

void Enemy::applyKnockback(const Vector& direction, float force) {
	Vector dir = direction;
	dir.normalize();
	Vector knockback = dir * force;
	setPosition(getPosition() + knockback);
}