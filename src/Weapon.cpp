#include "Weapon.h"

Weapon::Weapon(const Vector& size, SpriteAnimation* spriteAnimation, const std::string& description,
               float flatDamage, float flatAtkSpeed, float damageMultiplier,
               float atkSpeedMultiplier, int level, float cooldown, int id) : Item(size, spriteAnimation, description),
      flatDamage(flatDamage), flatAtkSpeed(flatAtkSpeed),
      damageMultiplier(damageMultiplier), atkSpeedMultiplier(atkSpeedMultiplier), 
      level(level), cooldown(cooldown), id(id), currentCooldown(0.0f) {}

void Weapon::update(float deltatime) {
    currentCooldown -= deltatime;
    for(auto& attack : getAttacks()) {
        attack->update(deltatime);
    }
}