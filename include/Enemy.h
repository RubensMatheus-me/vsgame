#pragma once
#include "Character.h"
#include "Player.h"

class Enemy : public Character {
    public:
        Enemy(float width, float height, SDL_Texture *image, const Vector& pos, const Vector& speed,
        float hp, float atkRate, float movSpeed, float xpDrop, int spawnWeight);

        void setTarget(const Player* newTarget) {this->target = newTarget;}

        float getXpDrop() const { return this->xpDrop; }
        int getSpawnWeight() const { return this->spawnWeight; }

        void setXpDrop(float xpDrop) { this->xpDrop = xpDrop; }
        void setSpawnWeight(int spawnWeight) { this->spawnWeight = spawnWeight; }

		void render(SDL_Renderer* renderer, const Vector& cameraOffSet) override;
        void update(float deltaTime) override;

    private:
        const Player* target;
        float xpDrop;
        int spawnWeight;
};