#include "ofApp.h"
#include <iostream>
#include <algorithm>

float* maxF;
float freqR;
float hitR;
bool hit;
int score;
bool match;

//float const bps = 60/116;
//--------------------------------------------------------------
void ofApp::setup(){
    beat.load("Fine_Line.mp3");
    pine.load("pine_rc.ttf",24);
    ofSetCircleResolution(100);
    hit = false;
    match = false;
    score = 0;
    ofBackground(0);
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSoundUpdate();
    float * val = ofSoundGetSpectrum(nBandsToGet);
    float curT = ofGetElapsedTimef();
    hitR = 20+200*sin(curT*116/60);
    for (int i = 0;i < nBandsToGet; i++){
        
        // let the smoothed value sink to zero:
        fftSmoothed[i] *= 0.97f;
        
        // take the max, either the smoothed or the incoming:
        if(fftSmoothed[i]<val[i]) fftSmoothed[i] = val[i];
        
    }
}


//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    maxF = std::max_element(std::begin(fftSmoothed), std::end(fftSmoothed));
    for (int i=0; i<nBandsToGet; i++){
        // hit circle
        ofPushStyle();
        ofSetColor(231, 148, 96);
        ofNoFill();
        ofSetLineWidth(4);
        ofDrawCircle(ofGetWidth()/2,ofGetHeight()/2,hitR);
        ofPopStyle();
        
        if(fftSmoothed[i]>0.2){
            ofDrawCircle(ofGetWidth()/2,ofGetHeight()/2,fftSmoothed[i]*100);
        }
        if (hit) {
            match = abs(hitR-fftSmoothed[i])<=5;
        } else {
            match = false;
        }
//        cout<<curR<<endl;
    }
    if (match){
        score += 1;
        ofPushStyle();
        ofBackground(190, 194, 63);
        ofPopStyle();
    }
    cout<<hit<<endl;
    ofPushStyle();
    ofSetColor(247, 217, 76);
    pine.drawString(ofToString(score), ofGetWidth()/2-pine.stringWidth(ofToString(score))/2,ofGetHeight()/2-pine.stringHeight(ofToString(score))/2);
    ofPopStyle();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case '1':
            beat.play();
            break;
        case '2':
            beat.stop();
            break;
        case 32:
            hit = true;
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if (key==32) hit = false;
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
