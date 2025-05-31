#include "Axe.h"
#include "AxeProjectile.h" 

Axe::Axe(const Vector& size, SpriteAnimation* spriteAnim, const std::string& description,
         float flatDamage, float flatAtkSpeed, float damageMultiplier,
         float atkSpeedMultiplier, int level,
         SpriteAnimation* axeProjectileAnim, float projSpeed, float projLifetime)
    : Weapon(size, spriteAnim, description, flatDamage, flatAtkSpeed, damageMultiplier, atkSpeedMultiplier, level),
      axeProjectileAnimation(axeProjectileAnim),
      projectileSpeed(projSpeed),
      projectileLifetime(projLifetime)
{}

void Axe::attack(const Vector& position, const Vector& direction, std::vector<Projectile*>& projectiles, Entity* owner) {
    Vector dirNorm = normalize(direction);
    Projectile* proj = new AxeProjectile(position, dirNorm, projectileSpeed, projectileLifetime, std::make_unique<SpriteAnimation>(*axeProjectileAnimation), owner);
    projectiles.push_back(proj);
}
