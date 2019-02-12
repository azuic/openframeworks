#include "ofApp.h"
float x,y;
float side, length;
//float counter;
//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    x = 0.000;
    y = 0.000;
    side = 30.000;
    length = 40.000;
}

//--------------------------------------------------------------
void ofApp::update(){
//    counter = counter + 0.033f;
}

//--------------------------------------------------------------
void ofApp::draw(){
    for (int i=0; i<ofGetHeight()-side; i++){
        ofSetColor(x/ofGetWidth()*255,0,0);
        ofDrawRectangle(x, y, length, side);
        x+=0.001;
        y+=0.001;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
