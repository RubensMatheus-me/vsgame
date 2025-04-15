#pragma once
#include "Player.h"

class Keyboard {

    public:
        Keyboard();
        enum DIRECTION {
            UP,
            DOWN,
            LEFT,
            RIGHT,
            NONE
        };

        Keyboard(DIRECTION state, bool isMoviment);

        void update(Player& player, float deltaTime);

        bool getIsMoviment() const {return isMoviment;}
        void setIsMoviment(bool moviment) {this->isMoviment = moviment;}

    private:
        DIRECTION state;
        bool isMoviment;
};