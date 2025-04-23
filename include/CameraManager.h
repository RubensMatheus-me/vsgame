#pragma once

#include "Vector.h"

class CameraManager{
    public:
        CameraManager(int screenWidth, int screenHeight);

        void follow(const Vector& targetPosition);
        Vector getOffSet() const {return this->offSet;}

    private:
        int screenWidth;
        int screenHeight;
        Vector offSet;
};