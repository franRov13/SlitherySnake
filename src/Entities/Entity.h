#pragma once

#include "ofMain.h"
#include "Snake.h"

class Entity {
    public:
        virtual void drawObj1() = 0;
        virtual void impact() = 0;
};