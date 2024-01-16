#include "PauseState.h"

PauseState::PauseState()
{
    pauseState_img.load("images/pauseScreen.jpg");
}

void PauseState::reset()
{
    setFinished(false);
	setNextState("");
}

void PauseState::update()
{

}

void PauseState::draw()
{
    ofSetColor(ofColor::black);
    // Draws the image
    ofSetColor(255, 255, 255);
    pauseState_img.draw(0, 0, ofGetWidth(), ofGetHeight());
    ofSetColor(ofColor::white);
    string text = "PAUSED";
    string text2 = "Press [Enter] to continue.";
    ofDrawBitmapString(text, (ofGetWidth() / 2 - 8 * text.length() / 2), ofGetHeight() / 2 - 11 - 50);
    ofDrawBitmapString(text2, (ofGetWidth() / 2 - 8 * text2.length() / 2), ofGetHeight() / 2 + 2 - 40);
    return;

}

void PauseState::keyPressed(int key)
{
    if(key == OF_KEY_RETURN) {
        this->setNextState("GameState");
    }
}