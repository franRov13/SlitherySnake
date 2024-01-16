#pragma once
#include <vector>

enum Direction {
        LEFT,
        RIGHT,
        UP,
        DOWN,
        NONE
    };

class Snake {

private:
    std::vector<std::vector<int>> body;
    Direction direction;
    int boardSizeWidth, boardSizeHeight;
    int segmentSize;
    bool crashed;
    std::vector<std::vector<bool>> visited; // To keep track of visited cells
    std::vector<std::vector<int>> parent; // To keep track of the parent of each cell
    int foodX; // X-coordinate of the food
    int foodY; // Y-coordinate of the food

public:
    Snake(int segmentSize, int boardSizeW, int boardSizeH);
    ~Snake();
    
   // score variable
    static int score;

    bool godMode = false;

    void update();
    void draw();
    void changeDirection(Direction d);
    void checkSelfCrash();
    void grow();
    void undo();
    void setFoodPosition(int x, int y);
    void highlightPathToFood();
    bool isCrashed() {
        return this->crashed;
    }
    // Getters
    std::vector<int> getHead() {
        return this->body[0];
    }
    std::vector<int> getTail() {
        return this->body[this->body.size() - 1];
    }
    std::vector<std::vector<int>> getBody() {
        return this->body;
    }
    int getScore() {
        return this->score;
    }
    // Setters
    void setScore(int newScore)
    {
        score = newScore;
    }
};



