#include "ofApp.h"
const int framerate = 60;
ofTrueTypeFont seigetsu, gencyfb;
ofVec2f mid, cur, mouse;
ofFbo fbo, hedgehog9;  // framebuffer object
ofColor stroke(0,0,0);
ofColor white(255,255,255);
Boolean fading;
Boolean ending;
//Boolean move;
int direction;
float fboX;
//int startFrame;

//--------------------------------------------------------------
void ofApp::setup(){
    ofTrueTypeFont::setGlobalDpi(100);
    ofSetWindowTitle("more scenes for the story");
    seigetsu.load("Seigetsu.ttf", 24, false);
    seigetsu.setLineHeight(18.0f);
    seigetsu.setLetterSpacing(1.037);
    
    gencyfb.load("gencyfb.ttf", 10, false);
    gencyfb.setLineHeight(28.0f);
    gencyfb.setLetterSpacing(1.037);
    
    ofSetFrameRate(framerate);
    ofBackground(255, 255, 255);
    mid = ofVec2f(ofGetWidth()/2,ofGetHeight()/2);
    fboX = 0;
    
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA32F); // higher precision alpha (no artifacts)
    fbo.begin();
    ofClear(255,255,255, 0);
    fbo.end();
    ofSetBackgroundColor(255, 255, 255);
    cur = mid;
    fading = false;
    ending = false;
}

//--------------------------------------------------------------
void ofApp::update(){
    if (ending == true){
        fboX = ofMap(ofGetFrameRate(),0,120,0,-mid.x);
    }
    
    switch (direction) {
        case 1:
            cur.y-=10;
            break;
        case 2:
            cur.y+=10;
            break;
        case 3:
            cur.x-=10;
            break;
        case 4:
            cur.x+=10;
            break;
        default:
            break;
    }
//    cur = mouse;
}

//--------------------------------------------------------------
void ofApp::draw(){
//    ofPushMatrix();
//    string title = "Zwei kleine I";
//    bounds = verdana14A.getStringBoundingBox(scaleA, 0, 0);
//
//    ofTranslate(500 + bounds.width/2, 530 + bounds.height / 2, 0);
//    ofScale(2.0 + cos(ofGetElapsedTimef()), 2.0 + cos(ofGetElapsedTimef()), 1.0);
//
//    verdana14A.drawString(scaleA, -bounds.width/2, bounds.height/2 );
//    ofPopMatrix();
    ofSetColor(stroke);
    seigetsu.drawString("the 9th hegdehog", mid.x-150, 100);
    ofSetColor(stroke, 80);
    gencyfb.drawString("Press 'f' to toggle fading with mouse.", mid.x-80, 2*mid.y-100);
    gencyfb.drawString("Press 'w', 's', 'a', 's' to move the boat.", mid.x-80, 2*mid.y-80);
    gencyfb.drawString("Click the mouse to see the ending.", mid.x-80, 2*mid.y-60);
    if (fading == true)
        cur = mouse;
//    else
//        cur = mid;
    
    fbo.begin();
    ofSetColor(white, 10); // background color with alpha
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    ofSetColor(stroke);
    ofNoFill();
    float side = 40;
    
    ofDrawTriangle(cur+side*ofVec2f(-4, -2),
                   cur+side*ofVec2f(-2, 1), cur); // bottom left
    ofDrawTriangle(cur+side*ofVec2f(-2, 1), cur+side*ofVec2f(2, 1),
                   cur+side*ofVec2f(4, -2)); // bottom right
    ofDrawTriangle(cur+0.25*side*ofVec2f(-4, -2),
                   cur+side*ofVec2f(1, -2), cur); // top left
    ofDrawTriangle(cur+0.45*side*ofVec2f(4, -2),
                   cur+side*ofVec2f(1, -2), cur); // top right
    
    
    float r = 45;
    float angle = 360/60;
    float angle2 = 360/50;
    ofSetLineWidth(1);
    ofVec2f rcenter(cur+ofVec2f(-60,-80));
    ofNoFill();
    for (int i=0; i < 60; i++){
        if (sin(angle*i)>-0.5){
            float l = ofRandom(0, 7);
            ofVec2f dir(sin(angle*i), cos(angle*i));
            ofDrawLine(rcenter+dir*(r-2),rcenter+dir*(r+l));
        }
    }
    for (int i=0; i < 60; i++){
        if (sin(angle2*i)>-0.5){
            float l = ofRandom(0, 7);
            ofVec2f dir(sin(angle2*i), cos(angle2*i));
            ofDrawLine(rcenter+dir*(r-5),rcenter+dir*(r-3+l));
        }
    }
    
    ofDrawBezier(rcenter.x+18,rcenter.y-20,
                 rcenter.x+24,rcenter.y-21, rcenter.x+26, rcenter.y-17,
                 rcenter.x+22,rcenter.y-18); // ear
    ofDrawCurve(rcenter.x-60,rcenter.y-10,
                rcenter.x-r/2-2,rcenter.y+r*cos(60)+8, rcenter.x-43, rcenter.y-20,
                rcenter.x-100,rcenter.y-10); // face
    ofDrawCurve(rcenter.x+40,rcenter.y+24,
                rcenter.x-45, rcenter.y-12, rcenter.x-r/2-2,rcenter.y-r*cos(60)-8,
                rcenter.x+60,rcenter.y+20); // body
    ofFill();
    ofDrawCircle(rcenter+ofVec2f(-20,-18), 3); // eye
    ofDrawCircle(rcenter+ofVec2f(-48,-18), 2.5); // nose
    
    
    fbo.end();
    
    ofSetColor(255,255,255);  // always set the color before drawing the fbo
    if (ending == false)
        fbo.draw(0,0);
    else
        fbo.draw(fboX,0);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key=='f') fading = true;
//        int step = 10;

    if(key == 'w') direction = 1;
    if(key == 's') direction = 2;
    if(key == 'a') direction = 3;
    if(key == 'd') direction = 4;
//    if (key == 'w' || key == 's' || key == 'a' || key == 'd') move = true;

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    mouse = ofVec2f(x,y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    ending = true;
//    startFrame = ofGetFrameRate();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
