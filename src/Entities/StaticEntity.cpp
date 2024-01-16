#include "StaticEntity.h"
#include "Snake.h"

StaticEntity::StaticEntity(int currentObjX, int currentObjY) 
{
    this->currentObjX = currentObjX;
    this->currentObjY = currentObjY;
}


StaticEntity::~StaticEntity()
{

}


void StaticEntity::drawObj1()
{
    ofSetColor(ofColor::black);
    ofDrawRectangle(currentObjX * 25, currentObjY * 25, 25, 25);
}


void StaticEntity::impact()
{

}