#include "Axe.h"
#include "AxeProjectile.h"
#include "TimedLifeTime.h"
#include "WaveMotion.h"
#include "Attack.h"
#include "OrbitMotion.h"
#include "Player.h"

Axe::Axe(const Vector& size, SpriteAnimation* spriteAnim, const std::string& description,
         float flatDamage, float flatAtkSpeed, float damageMultiplier,
         float atkSpeedMultiplier, int level, float projSpeed, float projLifetime, float cooldown, int id)
    : Weapon(size, spriteAnim, description, flatDamage, flatAtkSpeed, damageMultiplier, atkSpeedMultiplier, level, cooldown, id),
      projectileSpeed(projSpeed),
      projectileLifetime(projLifetime)
{}
Axe::Axe(const Vector& size,
         SpriteAnimation* spriteAnimation,
         const std::string& description)
    : Axe(size, spriteAnimation, description, 100.0f, 10.0f, 10.0f, 10.0f, 1, 150.0f, 10.0f, 3.0f, 1)   
{
}

void Axe::attack(const Vector& position, const Vector& direction, Player* owner) {
    auto anim = std::make_unique<SpriteAnimation>();
    anim->addAnimation("axe-idle", "axe", 0, 0, 32, 32, 1, false);
    anim->addAnimation("axe-right", "axe", 0, 0, 32, 32, 5, true);
    anim->addAnimation("axe-left", "axe", 160, 0, 32, 32, 5, true);
    anim->play("axe-right");

	auto p = std::make_unique<Attack>(
		Vector(50.0f, 50.0f),                       
		position + Vector(10.0f, 0.0f),             
		50.0f,                                      
		std::move(anim),                            
		std::make_unique<OrbitMotion>(
			owner,        
			50.0f,         
			2.0f,          
			0.0f           
		),
		std::make_unique<TimedLifetime>(5.0f),    
		false
	);

    getAttacks().push_back(std::move(p));
    currentCooldown = cooldown / owner->getAtkRate();
}

void Axe::render(SDL_Renderer* renderer) {
    if (getSprite()) {
        getSprite()->render(renderer, 1, 1);
    }
}

void Axe::levelUp(int levelUp) {
	level++;
}

