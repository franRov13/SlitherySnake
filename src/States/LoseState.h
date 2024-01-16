#pragma once

#include "State.h"
#include "GameState.h"
#include "Snake.h"
#include "ofMain.h"



class LoseState : public State
{
    private:
		ofImage loseState_img;
    public:
        LoseState();
		void reset();
		void update();
		void draw();
		void tick();
		void render();
		void keyPressed(int key);
		void mousePressed(int x, int y, int button);
		void keyReleased(int key);

};  