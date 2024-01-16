#pragma once

#include "State.h"
#include "Snake.h"
#include "ofMain.h"
#include "Entity.h"
#include "StaticEntity.h"

class GameState : public State {
    public:
        GameState();
        ~GameState();
        void reset();
        void update();
        void draw();
        void keyPressed(int key);
        void foodSpawner();
        void drawFood();
        void drawStartScreen();
        void drawLostScreen();
        void drawBoardGrid();

        Snake* snake;

        vector<StaticEntity*> WW;
        
        bool foodSpawned = false;
        bool paused = false;

        int currentFoodX;
        int currentFoodY;

        int boardSizeWidth, boardSizeHeight;
        int cellSize; // Pixels


        // Power Up Variables
        ofRectangle  FoodRectangle;
        vector<string> powereds;

        bool speedBoost = false;
        bool doubleUp = false;
        bool betterApple = false;
        bool godisActive = false;
        bool godMode = false;

        // float elapsedT = ofGetElapsedTimeMillis();
        float elapsed_time;
        float istime;
        float isfood;

        int powered = 0;
        int spedup= 10;
        float dyingFood;
};