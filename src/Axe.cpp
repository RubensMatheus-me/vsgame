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
void updateProjetics() {

}



void Axe::attack(const Vector& position, const Vector& direction,  std::vector<std::unique_ptr<Projectile>>& projectiles, Entity* owner) {
	auto anim = std::make_unique<SpriteAnimation>();
	anim->addAnimation("axe-idle", "axe", 0, 0, 32, 32, 1, false);
	anim->addAnimation("axe-right", "axe", 0, 0, 32, 32, 5, true);
	anim->addAnimation("axe-left", "axe", 160, 0, 32, 32, 5, true);
	anim->play("axe-right");

	auto p = std::make_unique<AxeProjectile>(
		position + 10.0f,
		direction,
		projectileSpeed,
		projectileLifetime,
		std::move(anim),
		flatDamage * damageMultiplier,
		owner
	);
    projectiles.push_back(std::move(p));
}

void Axe::render(SDL_Renderer* renderer) {

    if (getSprite()) {
        getSprite()->render(renderer,  1,  1);
    }
    
}

void Axe::update(float deltaTime) {
    if (getSprite()) {
        getSprite()->update(deltaTime); 
    }  
}
