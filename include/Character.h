#include "Entity.h"

class Character : public Entity {
    public:
        Character(float width, float height, SDL_Texture *image, const Vector& pos, const Vector& speed,
        float hp, float atkRate, float movSpeed);

        float getHp() const { return this->hp; }
        float getAtkRate() const { return this->atkRate; }
        float getMovSpeed() const { return this->movSpeed; }

        void setHp(float hp) { this->hp = hp; }
        void setAtkRate(float atkRate) { this->atkRate = atkRate; }
        void setMovSpeed(float movSpeed) { this->movSpeed = movSpeed; }

    private:
        float hp;
        float atkRate;
        float movSpeed;
};
