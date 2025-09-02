#pragma once
#include "Entity.h"
#include "IMotion.h"
#include "ILifetime.h"
#include <memory>

class Attack : public Entity {
public:
    Attack(const Vector& size,
           const Vector& position,
           float damage,
           std::unique_ptr<SpriteAnimation> animation,
           std::unique_ptr<IMotion> motion,
           std::unique_ptr<ILifetime> lifetime,
           bool destroyOnHit);

    void update(float dt) override;
    void render(SDL_Renderer* renderer) override;
    Rect getCollider() const override;
    bool getDestroyOnHit() const { return destroyOnHit; }
    float getDamage() const { return damage; }
    
private:
    float damage;
    std::unique_ptr<SpriteAnimation> animation;
    std::unique_ptr<IMotion> motion;
    std::unique_ptr<ILifetime> lifetime;
    bool destroyOnHit;
};
