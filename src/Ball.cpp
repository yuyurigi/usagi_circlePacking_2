#include "Ball.h"
#include "ofxEasing.h"

//--------------------------------------------------------------
void Ball::setup(int _centerX, int _centerY, int _maxWidth){
    centerX = _centerX;
    centerY = _centerY;
    maxWidth = _maxWidth;
    initTime = ofGetElapsedTimef();
}
//--------------------------------------------------------------
void Ball::update(){
    auto duration = 0.4f;
    auto endTime = initTime + duration;
    auto now = ofGetElapsedTimef();
    radius = ofxeasing::map_clamp(now, initTime, endTime, 0, maxWidth/2, &ofxeasing::back::easeOut_s, 10.0);
}
//--------------------------------------------------------------
void Ball::draw(){
    ofDrawCircle(centerX, centerY, radius);
}
