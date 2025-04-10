#include "Character.h"

class Player : public Character {
    public:
        Player(float width, float height, SDL_Texture *image, const Vector& pos, const Vector& speed,
        float hp, float atkRate, float movSpeed, float xp, int level, float atkSpeed);
    
        float getXp() const { return this->xp; }
        int getLevel() const { return this->level; }
        float getAtkSpeed() const { return this->atkSpeed; }
    
        void setXp(float xp) { this->xp = xp; }
        void setLevel(int level) { this->level = level; }
        void setAtkSpeed(float atkSpeed) { this->atkSpeed = atkSpeed; }

        void render(SDL_Renderer* renderer) override;
        void update() override;
    
    private:
        float xp;
        int level;
        float atkSpeed;
};
