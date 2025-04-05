#include "Item.h"

class Upgrade : public Item {
    public:
        Upgrade(float width, float height, SDL_Texture *image, const std::string& description,
                float hpMultiplier, float damageMultiplier, float movSpeedMultiplier);

        float getHpMultiplier() const { return this->hpMultiplier; }
        float getDamageMultiplier() const { return this->damageMultiplier; }
        float getMovSpeedMultiplier() const { return this->movSpeedMultiplier; }

        void setHpMultiplier(float hpMultiplier) { this->hpMultiplier = hpMultiplier; }
        void setDamageMultiplier(float damageMultiplier) { this->damageMultiplier = damageMultiplier; }
        void setMovSpeedMultiplier(float movSpeedMultiplier) { this->movSpeedMultiplier = movSpeedMultiplier; }

    private:
        float hpMultiplier;
        float damageMultiplier;
        float movSpeedMultiplier;
};
