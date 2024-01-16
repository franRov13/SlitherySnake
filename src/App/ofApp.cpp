#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("Snake");

    // Initializes game states
    gameState = new GameState();
    menuState = new MenuState();
    loseState = new LoseState();
    pauseState = new PauseState();

    // Sets the current state to the menu state
    currentState = menuState;

    // Music
    Sound.load("peaches.wav");
    Sound.setLoop(true);
    Sound.play();

}

//--------------------------------------------------------------
void ofApp::update(){
    // Checks if the current state has finished
    if(currentState->hasFinished()) {

        // If the next state is the game state, reset the game and change the current state to the game state
        if(currentState->getNextState() == "GameState") {
            gameState->reset();
            currentState = gameState;

        // If the next state is the menu state, reset the menu and change the current state to the menu state
        } else if(currentState->getNextState() == "MenuState") {
            menuState->reset();
            currentState = menuState;

        // If the next state is the lose state, change the current state to the lose state
        } else if (currentState->getNextState() == "LoseState") {
            loseState->reset();
            currentState = loseState;
        } 
    }
    // If the next state is the pause state, change the current state to the pause state
    if (currentState->getNextState() == "PauseState") {
        pauseState->reset();
        currentState = pauseState;
    // If the current state is the pause state and the next state is the Game state
    }else if (currentState == pauseState && currentState->getNextState() == "GameState")
    {
        /*
        Change the current state to the gamestate, this allows the game
        to keep its progress throghout pause state activation
        */
        currentState = gameState;
    }
    // Update the current state
    currentState->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    // Draw the current state
    currentState->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // Handle key press for the current state
    currentState->keyPressed(key);
}
//--------------------------------------------------------------
