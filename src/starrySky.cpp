#include "starrySky.h"

//--------------------------------------------------------------
void starrySky::setup(){
    CIRCLE_NUM = 20; //星の数
    x.resize(CIRCLE_NUM);
    y.resize(CIRCLE_NUM);
    rad.resize(CIRCLE_NUM);
    rot.resize(CIRCLE_NUM);
    s.resize(CIRCLE_NUM);
    b.resize(CIRCLE_NUM);
    for (int i = 0; i < CIRCLE_NUM; i++){
        x[i] = ofRandom(20, ofGetWidth()-20);
        y[i] = ofRandom(20, ofGetHeight()-20);
        rad[i] = ofRandom(2, 6); //星の大きさ
        rot[i] = ofRandom(360);
        s[i] = (int)ofRandom(2);
    }
}
//--------------------------------------------------------------
void starrySky::setup(ofImage _myPhoto){
    myPhoto = _myPhoto;
}
//--------------------------------------------------------------
void starrySky::draw(){
    for (int i = 0; i < CIRCLE_NUM; i++) {
        if (readBackground(x[i], y[i]) != ofColor(0, 0, 0)){
        ofSetColor(248, 206, 193, 200); //ピンク
        if (s[i] == 0) {
            ofDrawCircle(x[i], y[i], rad[i]);
        } else {
            ofPushMatrix();
            ofTranslate(x[i], y[i]);
            ofRotateDeg(rot[i]);
        ofDrawStar(0, 0, rad[i]*2);
            ofPopMatrix();
        }
    }
    }
}

//--------------------------------------------------------------

void starrySky::ofDrawStar(int x, int y, int r){
    int vertexNum = 5 * 2;
    int R;
    int outR = r;
    int inR = outR/2;
    
    ofPushMatrix();
    ofTranslate(x, y);
    ofRotateDeg(-90);
    ofBeginShape();
    for (int i = 0; i < vertexNum; i++) {
        if (i%2 == 0) {
            R = outR;
        } else {
            R = inR;
        }
        ofVertex(R*cos(DEG_TO_RAD*(360*i/vertexNum)), R*sin(DEG_TO_RAD*(360*i/vertexNum)));
    }
    ofEndShape();
    ofPopMatrix();
}

//--------------------------------------------------------------
ofColor starrySky::readBackground(float x, float y){
    ofPixels colorPixels = myPhoto.getPixels();
    ofColor c = colorPixels.getColor(x, y);
    return c;
}
