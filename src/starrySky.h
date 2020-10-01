#include "ofMain.h"

class starrySky {
private:
    vector<float> x;
    vector<float> y;
    vector<float> rad;
    vector<float> rot;
    vector<int> s;
    vector<bool> b;
    int CIRCLE_NUM;
    ofImage myPhoto;
public:
    void setup();
    void setup(ofImage _myPhoto);
    void draw();
    void ofDrawStar(int x, int y, int r);
    ofColor readBackground(float x, float y);
};
