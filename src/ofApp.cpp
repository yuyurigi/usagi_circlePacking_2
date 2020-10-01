#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetCircleResolution(50);
    ofEnableSmoothing();
    
    //myPhoto.load("u1.jpg"); //シルエット取得用の画像
    myPhoto.load("u2.jpg");
    //myPhoto.load("u3.jpg");
    myPhoto2 = myPhoto;
    
    myPhoto.resize(400, 400);
    myPhoto.setImageType(OF_IMAGE_GRAYSCALE);
    width = myPhoto.getWidth();
    height = myPhoto.getHeight();
    
    pixelsOrigin = myPhoto.getPixels().getData();
    pixels = new unsigned char [width * height];
    
    //画像を白黒変換
    int threshold = 100;
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            if(pixelsOrigin[i*width+j]>=threshold){
                pixelsOrigin[i*width+j] = 255;
                pixels[i*width+j] = 255;
            }else{
                pixelsOrigin[i*width+j] = 0;
                pixels[i*width+j] = 0;
            }
        }
    }
    
    //フォント
    font.load("Sacramento-Regular.ttf", 72);
    fw = font.stringWidth("Mid Autumn");
    fh = font.stringHeight("Mid Autumn");
    fx = ofGetWidth() / 2 - fw / 2;
    fy = ofGetHeight() - 200;
    
    //文字と背景の星が重ならないようにする
    int width2 = myPhoto2.getWidth();
    int height2 = myPhoto2.getHeight();
    unsigned char * data = myPhoto2.getPixels().getData();
    for (int i = fy-fh; i < fy + fh; i++) {
        for (int j = fx; j < fx + fw; j++) {
            data[3*(i*width2+j)] = 0;
            data[3*(i*width2+j)+1] = 0;
            data[3*(i*width2+j)+2] = 0;
        }
    }
    myPhoto2.update();
    sky.setup(); //背景の星
    sky.setup(myPhoto2);
}

//--------------------------------------------------------------
void ofApp::update(){
    int currentFrame = ofGetFrameNum();
    if (currentFrame >= 3) { //nフレーム後から描き始める
        
    if(!onePixelLeft){
        maxWidth = 0;
        for(int i=0;i<height;i++){
            for(int j=0;j<width;j++){
                if(pixels[i*width+j]==0){
                    // --> algorithm for finding the largest one
                    int range = 1;
                    bool dtct = 0;
                    
                    for(int k = 1; k<width+1; k+=2){
                            range = k;
                        if(((j-range/2)<0)||((j+range/2)>width)) dtct = 1;
                        if(((i-range/2)<0)||((i+range/2)>height)) dtct = 1;
                        if(dtct) {
                            range -= 2;
                            break;
                        }
                        dtct = 0;
                        for(int l=j-range/2; l<=j+range/2; l++){
                            for(int m=i-range/2; m<=i+range/2; m++){ // think about the case of l or m elss than 0
                                dist = sqrt((l-j)*(l-j)+(m-i)*(m-i));
                                if((dist<=(float)range/2)&&(pixels[m*width+l] == 255)) dtct = 1;
                            }
                        }
                    }
                    if(maxWidth<range){
                        
                        maxWidth = range;
                        centerX = j;
                        centerY = i;
                    }
                }
            }
        }
        
        
        for(int i=centerY-maxWidth/2; i<=centerY+maxWidth/2; i++){
            for(int j=centerX-maxWidth/2; j<=centerX+maxWidth/2; j++){
                dist = sqrt((j-centerX)*(j-centerX)+(i-centerY)*(i-centerY));
                if(dist<=maxWidth/2) {
                    pixels[i*width+j] = 255;
                }
            }
        }
        if(maxWidth <4) onePixelLeft = 1; //円の直径の最小値　4未満は描かれない
    }
     
    }
    
    if(!onePixelLeft){
        Ball b;
        b.setup(centerX, centerY, maxWidth); //centerX, centerY, maxWidth
        balls.push_back(b);
    }
    for(int i = 0; i < balls.size(); i++){
        balls[i].update();
    }
     
}

//--------------------------------------------------------------
void ofApp::draw(){
    //背景
    ofBackground(57, 83, 112);
    /*
    ofColor c1 = ofColor(57, 83, 112);
    ofColor c2 = c1;
    c2.setBrightness(c2.getBrightness()-30);
    ofBackgroundGradient(c1, c2);
     */
    sky.draw(); //背景の星
    
    //文字
    ofSetColor(248, 206, 193);
    font.drawString("Mid Autumn", fx, fy);
    
    //うさぎ
    ofScale(2);
    for(int i = 0; i < balls.size(); i++){
        ofSetColor(248, 206, 193, 240);
        balls[i].draw();
    }
    
    myImage.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
 
    if (key == 'S' || key == 's') {
            myImage.save(ofGetTimestampString("%Y%m%d%H%M%S")+"##.jpg");
    }
    if (key == 'C' || key == 'c'){
        balls.clear();
        for(int i=0; i<height; i++){
            for(int j=0; j<width; j++){
                    pixels[i*width+j] = pixelsOrigin[i*width+j];
            }
        }
        onePixelLeft = 0;
        sky.setup();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}
