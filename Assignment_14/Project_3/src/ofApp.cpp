#include "ofApp.h"
#include <iostream>
#include <algorithm>

//float* maxF;
float freqR;
float hitR;
bool hit;
int score;
bool match;
bool start;
float *hitvalue;
ofColor whitecircle = ofColor(61,117,242);
float hue;

//--------------------------------------------------------------
void ofApp::setup(){
    beat.load("Fine_Line.mp3");
    pine.load("pine_rc.ttf",24);
    ofSetCircleResolution(100);
    hit = false;
    match = false;
    score = 0;
    ofBackground(8,8,8);
    start = false;
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
//    if (hit){
//        float *hitvalue = std::find(std::begin(fftSmoothed), std::end(fftSmoothed), hitR/100);
//        if (hitvalue != std::end(fftSmoothed)) {
//            match = true;
//            cout<<"match"<<endl;
//        } else {
//            match = false;
//        }
//        cout<<match<<endl;
//    }
//    hit = false;
}


//--------------------------------------------------------------
void ofApp::draw(){
    if (!start){
        ofDrawBitmapString("press [1] to start/restart", ofGetWidth()/2-100, ofGetWidth()/2+100);
        ofDrawBitmapString("press [2] to stop", ofGetWidth()/2-70, ofGetWidth()/2+125);
        ofDrawBitmapString("press [space] to hit the frequency", ofGetWidth()/2-130, ofGetWidth()/2+150);
        ofDrawBitmapString("Scored when orange circle hit the center blue circle", ofGetWidth()/2-190, ofGetWidth()/2+175);
    }
//    ofSetColor(255);
//    maxF = std::max_element(std::begin(fftSmoothed), std::end(fftSmoothed));
    for (int i=0; i<nBandsToGet; i++){
        // hit circle
        ofPushStyle();
        hue = ofMap( i, 1, nBandsToGet, 110, 250 );
        ofSetColor(231, 148, 96);
        ofNoFill();
        ofSetLineWidth(4);
        ofDrawCircle(ofGetWidth()/2,ofGetHeight()/2,hitR);
        ofPopStyle();
        
        // freq circle
        ofPushStyle();
        ofSetLineWidth(20);
//        ofSetColor(0, 10); // background color with alpha
//        ofFill();
//        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
        whitecircle.setSaturation(hue);
        ofSetColor(whitecircle);
        ofNoFill();
        ofDrawCircle(ofGetWidth()/2,ofGetHeight()/2,fftSmoothed[i]*100);
        ofPopStyle();
        
        // check
        if (hit) {
            match = abs(hitR-fftSmoothed[i])<=20;
        } else {
            match = false;
        }

        if (match){
            score += 1;
            ofPushStyle();
            ofBackground(190, 194, 63);
            ofPopStyle();
        }
        hit = false;
    }
    if (match){
        score += 1;
        ofPushStyle();
        ofBackground(190, 194, 63);
        ofPopStyle();
    }

    // scores
    ofPushStyle();
    ofSetColor(247, 217, 76);
    pine.drawString("Scores: "+ofToString(score), 20,40);
    ofPopStyle();
//    hit = false;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case '1':
            start = true;
            score = 0;
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
//    if (key==32) hit = false;
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
