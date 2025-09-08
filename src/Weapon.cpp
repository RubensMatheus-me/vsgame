#include "Weapon.h"
#include "Attack.h"
#include "Weapon.h"
#include "Enemy.h"
#include "Player.h"
#include "Attack.h"

Weapon::Weapon(const Vector& size, SpriteAnimation *spriteAnimation, const std::string& description,
               float flatDamage, float flatAtkSpeed, float damageMultiplier,
               float atkSpeedMultiplier, int level, float cooldown, int id, float knockback)
    : Item(size, spriteAnimation, description),
      flatDamage(flatDamage), flatAtkSpeed(flatAtkSpeed),
      damageMultiplier(damageMultiplier), atkSpeedMultiplier(atkSpeedMultiplier),
      level(level), cooldown(cooldown), currentCooldown(0.0f), id(id), knockback(knockback) {}


void Weapon::update(float deltaTime) {
    currentCooldown -= deltaTime;
    for (auto &attack : attacks) {
        attack->update(deltaTime);
    }
}
