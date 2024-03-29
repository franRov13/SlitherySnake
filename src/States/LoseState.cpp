#include "LoseState.h"


LoseState::LoseState() 
{
	loseState_img.load("images/marioGameOver.jpg");
    
}
void LoseState::tick() 
{
    setNextState("LoseState");
	setFinished(true);
}

void LoseState::keyPressed(int key)
{
    if(key == OF_KEY_LEFT || key == OF_KEY_RIGHT || key == OF_KEY_UP || key == OF_KEY_DOWN) {
        setFinished(true);
        setNextState("GameState");
        return;
    }
}

void LoseState::reset()
{
	setFinished(false);
	setNextState("");
	return;
}

void LoseState::draw()
{
    ofSetColor(ofColor::black);
    // Draws the image
    ofSetColor(255, 255, 255);
    loseState_img.draw(0, 0, ofGetWidth(), ofGetHeight());
    ofSetColor(ofColor::white);
    string text = "You lost! Press any arrow key to play again";
    string text2 = "or press [ESC] to exit.";
    string text3 = "Score:" + to_string(Snake::score);
    ofDrawBitmapString(text, ofGetWidth() / 2 - 8 * text.length() / 2, ofGetHeight() / 2 - 11 - 25);
    ofDrawBitmapString(text2, ofGetWidth() / 2 - 8 * text2.length() / 2, ofGetHeight() / 2 + 2 - 15);
    // Display the score 
    ofDrawBitmapString(text3, ofGetWidth() / 2 - 8 * text3.length() / 2, ofGetHeight() / 2 + 2);
    return;
}

void LoseState::update()
{

}