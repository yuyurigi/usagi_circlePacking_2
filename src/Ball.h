#include "ofMain.h"

class Ball {
private:
    int centerX, centerY, maxWidth;
    float duration, radius, initTime;
public:
    void setup(int _centerX, int _centerY, int _maxWidth);
    void update();
    void draw();
};
