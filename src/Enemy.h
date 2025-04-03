#include "Character.h"

class Enemy : public Character {
    public:
        Enemy(float width, float height, SDL_Texture *image, const Vector& pos, const Vector& speed,
        float hp, float atkRate, float movSpeed, float xpDrop, int spawnWeight);

        float getXpDrop() const { return this->xpDrop; }
        int getSpawnWeight() const { return this->spawnWeight; }

        void setXpDrop(float xpDrop) { this->xpDrop = xpDrop; }
        void setSpawnWeight(int spawnWeight) { this->spawnWeight = spawnWeight; }

    private:
        float xpDrop;
        int spawnWeight;
};