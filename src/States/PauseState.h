#pragma once

#include "State.h"
#include "GameState.h"
#include "ofMain.h"

class PauseState : public State
{
    private:
		ofImage pauseState_img;
    public:
        PauseState();
		void reset();
		void update();
		void draw();
		void tick();
		void render();
		void keyPressed(int key);
		// void mousePressed(int x, int y, int button);
		// void keyReleased(int key);
};