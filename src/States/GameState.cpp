#include "GameState.h"
#include "Snake.h"


//--------------------------------------------------------------
GameState::GameState() {
    foodSpawned = false;
    cellSize = 25;
    boardSizeWidth = 64;
    boardSizeHeight = 36;
    snake = new Snake(cellSize, boardSizeWidth, boardSizeHeight);

    // Static Entity Obstacles (BlackHoles)
    for (int i = 0; i <= 25; i++) 
    {
        WW.push_back(new StaticEntity(ofRandom(0, boardSizeWidth), ofRandom(0, boardSizeHeight)));
    }

    // Power Up Push Backs
    powereds.push_back("SpeedBoost");
    powereds.push_back("BetterApple");
    powereds.push_back("GodMode");
}
//--------------------------------------------------------------
GameState::~GameState() {
    delete snake;
}
//--------------------------------------------------------------
void GameState::reset() {
    delete snake;
    snake = new Snake(cellSize, boardSizeWidth, boardSizeHeight);
    foodSpawned = false;
    setFinished(false);
    setNextState("");
    snake->setScore(0);  //this will reset the score
    betterApple = false;
    godMode = false;
    speedBoost = false;
    doubleUp = false;
    godisActive = false;
    elapsed_time = 0;
    spedup= 10;
    powered = 0;
}
//--------------------------------------------------------------
void GameState::update() {
    // Checks if the game is paused
    if (paused == true)
    {
        // Sets the next state to the pause state
        this->setNextState("PauseState");
        // Sets the paused flag to false
        paused = false;
        // Exits the function
        return;
    }
    else
    {
        setNextState("");

        elapsed_time = ofGetElapsedTimeMillis();

        // Checks if the snake has crashed into a wall or itself
        if (!godisActive)
        {
            if(snake->isCrashed()) 
            {
                /*
                If it has crashed, the line of code below simply 
                finishes the game and sets the next state to 
                the "LoseState"
                */
                this->setNextState("LoseState");
                this->setFinished(true);
                return;
            }
        }

        // Checks if the snake's head is at the position of the current food in the game
        if(snake->getHead()[0] == currentFoodX && snake->getHead()[1] == currentFoodY && Snake::score % 50 == 0 &&Snake::score > 0) {
            /*
            Makes the snake grow and sets "foodSpawned" to false, 
            in order to spawn new food
            */
            snake->grow();
            foodSpawned = false;
            // Snake::score += 10;
            // Power Up Activating Code
            if (powereds[powered] == "SpeedBoost")
            {
                speedBoost = true;
                betterApple = false;
                godMode = false;
            }else if (powereds[powered] == "BetterApple")
            {
                speedBoost = false;
                betterApple = true;
                godMode = false;
            }else if (powereds[powered] == "GodMode")
            {
                speedBoost = false;
                betterApple = false;
                godMode = true;
            }
            powered++;

        }
        else if (snake->getHead()[0] == currentFoodX && snake->getHead()[1] == currentFoodY)
        {
            snake->grow();
            // If the better apple power up boolean is activated, the snake grown again/double
            if (doubleUp) {
                snake->grow();
            }
            foodSpawned = false;
            // Add 10 to the score
            // Snake::score += 10;
            dyingFood = 0;
        }
    
        // Spawns new food if necessary
        foodSpawner();
        // Update's the snake's movement every 10 frames
        if(ofGetFrameNum() % spedup== 0) {
            snake->update();
        }
        if(powered > 2)
        {
            powered = 0;
        }
    
        if(elapsed_time >= istime)
        {
            spedup= 10;
            godisActive = false;
            doubleUp = false;
            godMode = false;
            snake->godMode = false;
        }
        if (foodSpawned)
        {
            if (elapsed_time >= isfood) {
                foodSpawned = false;
                dyingFood = 0;
            }
            dyingFood += 0.10;
        }
    
        for(auto it = WW.begin(); it != WW.end(); it++)
        {
            if(snake->getHead()[0] == (*it)->getPosX() && snake->getHead()[1] == (*it)->getPosY())
            {
                this->setNextState("LoseState");
                this->setFinished(true);
                return;
            }
        }

        if (speedBoost) {
            spedup= 5; // increase the speed
            if (ofGetElapsedTimeMillis() >= elapsed_time + 15000) {
                // 15 seconds have passed, disable the power-up
                spedup= 10;
                speedBoost = false;
            }
        }

        if (betterApple) {
            if (ofGetElapsedTimeMillis() >= elapsed_time + 15000) {
                // 15 seconds have passed, disable the power-up
                doubleUp = false;
                betterApple = false;
            }
        }
        if (godMode) {
            if (ofGetElapsedTimeMillis() >= elapsed_time + 15000) {
                // 10 seconds have passed, disable the power-up
                godisActive = false;
                godMode = false;
                snake->godMode = false;
            }
        }


    }

}
//--------------------------------------------------------------
void GameState::draw() {
    drawBoardGrid();
    snake->draw();
    drawFood();

    // Draws Static Entity Obstacles (BlackHoles)
    for(auto it = WW.begin(); it != WW.end(); it++) { (*it)->drawObj1(); }


    // Check Power Up Checkers
    if(godMode)
    {
        ofDrawBitmapStringHighlight("Power Up Available: God Mode. Press B to activate!" + to_string(Snake::score), ofGetWidth() / 3, 20, ofColor::yellow, ofColor::black);
    }
    if (speedBoost)
    {
        ofDrawBitmapStringHighlight("Power Up Available: spedupBoost. Press B to activate!" + to_string(Snake::score), ofGetWidth() / 3, 20, ofColor::blue, ofColor::black);
    }
    if (betterApple)
    {
        ofDrawBitmapStringHighlight("Power Up Available: Better Apple. Press B to activate!" + to_string(Snake::score), ofGetWidth() / 3, 20, ofColor::darkRed, ofColor::black);
    }
}
//--------------------------------------------------------------
void GameState::keyPressed(int key) {
    // Checks if the key pressed is not a directionnal key
    if(key != OF_KEY_LEFT && key != OF_KEY_RIGHT && key != OF_KEY_UP && key != OF_KEY_DOWN)
    {
        /*
        Debug key 'a' that when pressed, will increase the current
        score by 10 points.
        */
        if (key == 'a' || key == 'A')
        {
            snake->setScore(snake->getScore() + 10);
        }
        /*
        Debug key 'u' that when pressed, removes the 
        tail of the snake 
        */
        if (key == 'u' || key == 'U')
        {
            snake->undo();
        }

        // Toggle pause with key 'p'
        if (key == 'p' || key == 'P')
        {
            if (paused == false)
            {
                paused = true;
            }else
            {
                paused = false;
            }
        }
        return;

        // Key B for Power Up Activation
        if (key == 'b' || key == 'B')
        {
            if (speedBoost)
            {
                spedup= 5;
                istime = elapsed_time + 15000;
            }
            if (betterApple)
            {
                istime = elapsed_time + 15000;
                doubleUp = true;
                // betterApple = false;
            }
            if (godMode)
            {
                istime = elapsed_time + 10000;
                godisActive = true;
                snake->godMode = true;
            }
        }
    }  

    switch(key) {
        case OF_KEY_LEFT:
            snake->changeDirection(LEFT);
            break;
        case OF_KEY_RIGHT:
            snake->changeDirection(RIGHT);
            break;
        case OF_KEY_UP:
            snake->changeDirection(UP);
            break;
        case OF_KEY_DOWN:
            snake->changeDirection(DOWN);
            break;
    }
}
//--------------------------------------------------------------
void GameState::foodSpawner() {
    // Checks if food has already been spawned
    if(!foodSpawned) {
        bool isInSnakeBody;
        // Generates a new position for the food until it is not in the snake's body
        do {
            isInSnakeBody = false;
            // Generates random coordinates within the game board (excluding the borders)
            currentFoodX = ofRandom(1, boardSizeWidth-1);
            currentFoodY = ofRandom(1, boardSizeHeight-1);
            // Checks if the food position is already occupied by the snake's body
            for(unsigned int i = 0; i < snake->getBody().size(); i++) {
                if(currentFoodX == snake->getBody()[i][0] && currentFoodY == snake->getBody()[i][1]) {
                    isInSnakeBody = true;
                }
            }
        } while(isInSnakeBody);
        // Sets foodSpawned to true to indicate that a new food has been spawned
        foodSpawned = true;

        isfood = elapsed_time + 30000;
    }
}

//--------------------------------------------------------------
void GameState::drawFood() {
    ofSetColor(ofColor::red);
     FoodRectangle.set(currentFoodX*cellSize, currentFoodY*cellSize, cellSize, cellSize);
    // Checks if the food has been spawned on the board.
    if(foodSpawned) {
        /*
        Draw the food as a rectangle with its position speciBfied by its x and y coordinates
        multiplied by the size of each cell.
        */
        ofDrawRectangle(currentFoodX*cellSize, currentFoodY*cellSize, cellSize, cellSize);
        if(Snake::score % 50 == 0 && Snake::score > 0)
        {
            if(powereds[powered] == "SpeedBoost")
            {
                ofSetColor(ofColor::blue);
                 FoodRectangle.set(currentFoodX*cellSize, currentFoodY*cellSize, cellSize, cellSize);
                ofDrawRectangle( FoodRectangle);
            }
            else if(powereds[powered] == "BetterApple")
            {
                ofSetColor(ofColor::purple);
                 FoodRectangle.set(currentFoodX*cellSize, currentFoodY*cellSize, cellSize, cellSize);
                ofDrawRectangle( FoodRectangle);
            }
            else if(powereds[powered] == "GodMode")
            {
                ofSetColor(ofColor::yellow);
                 FoodRectangle.set(currentFoodX*cellSize, currentFoodY*cellSize, cellSize, cellSize);
                ofDrawRectangle( FoodRectangle);
            }
        }
    }else
    {
        ofSetColor(255 - dyingFood, 0, 0);
    }
    foodSpawned = true;
    ofDrawRectangle( FoodRectangle);
}
//--------------------------------------------------------------
void GameState::drawStartScreen() {
    ofSetColor(ofColor::black);
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    ofSetColor(ofColor::white);
    string text = "Press any arrow key to start.";
    ofDrawBitmapString(text, ofGetWidth()/2-8*text.length()/2, ofGetHeight()/2-11);
    return;
}
//--------------------------------------------------------------
void GameState::drawLostScreen() {
}
//--------------------------------------------------------------
void GameState::drawBoardGrid() {
    
    ofDrawGrid(25, 64, false, false, false, true);
}
//--------------------------------------------------------------

