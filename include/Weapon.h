#pragma once
#include "Item.h"

class Weapon : public Item {
    public:
        Weapon(float width, float height, SDL_Texture *image, const std::string& description,
            float flatDamage, float flatAtkSpeed, float damageMultiplier,
            float atkSpeedMultiplier, int level);

        float getFlatDamage() const { return this->flatDamage; }
        float getFlatAtkSpeed() const { return this->flatAtkSpeed; }
        float getDamageMultiplier() const { return this->damageMultiplier; }
        float getAtkSpeedMultiplier() const { return this->atkSpeedMultiplier; }
        int getLevel() const { return this->level; }
        
        void setFlatDamage(float flatDamage) { this->flatDamage = flatDamage; }
        void setFlatAtkSpeed(float flatAtkSpeed) { this->flatAtkSpeed = flatAtkSpeed; }
        void setDamageMultiplier(float damageMultiplier) { this->damageMultiplier = damageMultiplier; }
        void setAtkSpeedMultiplier(float atkSpeedMultiplier) { this->atkSpeedMultiplier = atkSpeedMultiplier; }
        void setLevel(int level) { this->level = level; }

    private:
        float flatDamage;
        float flatAtkSpeed;
        float damageMultiplier;
        float atkSpeedMultiplier;
        int level;
};