#pragma once
#include "Entity.h"
#include "SpriteAnimation.h"
#include <memory>

class Projectile : public Entity {
public:
    Projectile(const Vector& size, const Vector& position, const Vector& direction, float speed, float lifetime, std::unique_ptr<SpriteAnimation> animation, float damage, Entity* owner = nullptr);
    virtual ~Projectile() = default;

	virtual void update(float dt);
    virtual void render(SDL_Renderer* renderer);
    bool isAlive() const;
    void setAlive(bool alive);
    void expire();
    Entity* getOwner() const { return owner; }

    virtual Rect getCollider() const override;
	float getDamage() const {return damage;}

protected:
    Entity* owner;
    Vector direction;
    float speed;
	float damage;
    float lifeRemaining;
    std::unique_ptr<SpriteAnimation> animation;
};
