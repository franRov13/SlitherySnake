#pragma once

#include "Entity.h"
#include "Snake.h"

class StaticEntity : public Entity {
    private:
        int currentObjX;
        int currentObjY;

    public:
        StaticEntity(int currentObjX, int currentObjY);
        ~StaticEntity();
        void drawObj1();
        void impact();

        int getPosX() {return currentObjX; }
        int getPosY() {return currentObjY; }
};