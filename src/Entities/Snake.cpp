#include "Snake.h"
#include "ofMain.h"

Snake::Snake(int segmentSize, int boardSizeW, int boardSizeH) {
    // Initializes the body of the snake with an initial length of 4 segments
    body.push_back({8, 9});
    body.push_back({9, 9});
    body.push_back({10, 9});
    body.push_back({11, 9});

    // Sets the initial direction of the snake
    this->direction = LEFT;

    // Set the initial state of the snake to not crashed
    this->crashed = false;

    // Set the size of each segment of the snake and the size of the game board
    this->segmentSize = segmentSize;
    this->boardSizeWidth = boardSizeW;
    this->boardSizeHeight = boardSizeH; 

    // Sets the initial score of the snake to 0
    this->score = 0; 
}

Snake::~Snake() {
    // TODO Auto-generated destructor stub
}

void Snake::update() {
    // Gets the position of the old head of the snake
    vector<int> oldHead = this->getHead();

    // Update the position of the head of the snake based on the current direction
    switch(this->direction) {
        case LEFT: {
            this->body[0][0] -= 1;
            break;
        }
        case DOWN: {
            this->body[0][1] += 1;
            break;
        }
        case RIGHT: {
            this->body[0][0] += 1;
            break;
        }
        case UP: {
            this->body[0][1] -= 1;      
            break;
        }
        case NONE: {
            break;
        }
    }
    // Checks if the snake has collided with the boundaries of the game board
    if(oldHead[0] == -1 || oldHead[0] == boardSizeWidth || oldHead[1] == -1 || oldHead[1] == boardSizeHeight) {
        crashed = true;
        return;
    }
    // Updates the position of the body segments of the snake
    int prevX = oldHead[0];
    int prevY = oldHead[1];
    for (unsigned int i = 1; i < this->body.size(); i++) {
        int currX = this->body[i][0];
        int currY = this->body[i][1];
        // The current body segment takes the position of the previous body segment
        this->body[i][0] = prevX;
        this->body[i][1] = prevY;
        prevX = currX;
        prevY = currY;
    }

    // Check if the snake has collided with itself
    checkSelfCrash();
}

void Snake::draw() {
    // Iterates through each segment of the snake's body
    for (unsigned int i = 0; i < body.size(); i++) {
        int curX = this->body[i][0];
        int curY = this->body[i][1];
        // If this is the head of the snake
        if(i == 0)
        {
            // Changed the color of the snake's head.
            ofSetColor(ofColor::paleVioletRed); 
        }
        else 
        {
            // Changed the color of the snake’s body.
            ofSetColor(ofColor::lightSteelBlue); 
        }
        // Draw a rectangle to represent the current segment of the snake
        ofDrawRectangle(curX * segmentSize, curY * segmentSize, segmentSize, segmentSize);
    }
    // Displays the score.
    ofDrawBitmapStringHighlight("Score:" + ofToString(this->score), ofGetWidth() / 2, 20, ofColor::beige, ofColor::paleVioletRed);
}

void Snake::changeDirection(Direction d) {

    if(this->direction == LEFT and d == RIGHT)
        return;
    if(this->direction == RIGHT and d == LEFT) 
        return;
    if(this->direction == UP and d == DOWN) 
        return;
    if(this->direction == DOWN and d == UP)
        return;
    
    this->direction = d;
}

void Snake::checkSelfCrash() {
    while (godMode)
    {
        // Creates a copy of the snake's body
        vector<vector<int>> snake = this->body;
        // Gets the position of the head
        vector<int> head = snake[0];
        // Iterates through the rest of the snake's body
        for(unsigned int i = 1; i < snake.size(); i++) {
            // If the head is at the same position as another segment in the body
            if(head[0] == snake[i][0] and head[1] == snake[i][1]) {
                // Set crashed to true and exit the function
                crashed = true;
                return;
            }
        }
    }
}

void Snake::grow() {
    // Getx the coordinates of the tail of the snake
    vector<int> newSegment = this->getTail();
    // Add a new segment to the end of the snake's body
    this->body.push_back(newSegment);
    this->score += 10; // Everytime the snake eats food, the score increases by 10 points. 
}

/*
Snake::undo() function that removes the tail of the snake, as long
as the snake is longer than 2 segments, including the head
*/
void Snake::undo()
{
    if (body.size() > 2)
    {
        body.pop_back();
    }   
}

// Definition for the static member variable score
int Snake::score = 0;