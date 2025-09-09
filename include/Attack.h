#pragma once
#include "Entity.h"
#include "IMotion.h"
#include "ILifeTime.h"
#include <memory>
#include <SDL_ttf.h>

class Enemy;
class DamagePopup;

class Attack : public Entity
{
public:
    Attack(const Vector &size,
           const Vector &position,
           float damage,
           std::unique_ptr<SpriteAnimation> animation,
           std::unique_ptr<IMotion> motion,
           std::unique_ptr<ILifetime> lifetime,
           bool stopHitboxOnHit,
           bool stopAnimationOnHit);

    void update(float dt) override;
    void render(SDL_Renderer *renderer) override;
    Rect getCollider() const override;
    bool getStopHitboxOnHit() const { return stopHitboxOnHit; }
    bool getStopAnimationOnHit() const { return stopAnimationOnHit; }
    bool getIsHitboxActive() const { return isHitboxActive; }

    void checkCollisions(std::vector<std::unique_ptr<Enemy>> &enemies,
                         std::vector<std::unique_ptr<DamagePopup>> &popups,
                         SDL_Renderer *renderer,
                         TTF_Font *font);

    float getDamage() const { return damage; }
    void resetLifetime();
    void onHit();

private:
    float damage;
    std::unique_ptr<SpriteAnimation> animation;
    std::unique_ptr<IMotion> motion;
    std::unique_ptr<ILifetime> lifetime;
    bool isHitboxActive = true;
    bool stopHitboxOnHit;
    bool stopAnimationOnHit;
};
