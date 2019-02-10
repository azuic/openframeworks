#include "ofApp.h"
int midX, midY;
int ind;
float counter;
bool up;
int upangle;
//--------------------------------------------------------------
void ofApp::setup(){
    midX = ofGetWidth() / 2;
    midY = ofGetHeight() / 2;
    counter = 0;
    ofSetFrameRate(60);
    ofBackground(255, 255, 255);
    ofSetWindowTitle("project objects sketch");
}

//--------------------------------------------------------------
void ofApp::update(){
    ind = (ofGetFrameNum() / 120) % 8;
//    counter = counter + 0.033f;
    int sec=(ofGetFrameNum() / 60) % 60;
    up=sec<30;
    counter = counter + 0.033f;
    

}

//--------------------------------------------------------------
void ofApp::draw(){
    switch (ind) {
        case 1: {
            // hedgehog
            ofSetHexColor(0x000000);
            ofFill();
            ofDrawCircle(midX, midY-25, 10); // nose
            ofDrawCircle(midX-50, midY-50, 5); // left eye
            ofDrawCircle(midX+50, midY-50, 5); // right eye
            ofNoFill();
            ofSetLineWidth(3.5);
            ofDrawBezier(midX-100, midY-50, midX-120, midY-70, midX-105, midY-85, midX-90, midY-75); // left ear
            ofDrawBezier(midX+100, midY-50, midX+120, midY-70, midX+105, midY-85, midX+90, midY-75); // right ear
            ofSetLineWidth(2);
            float r = 150;
            float angle = 360/60;
            for (int i=0; i < 60; i++){
                float l = ofRandom(0, 20);
                ofDrawLine(midX+r*sin(angle*i), midY+r*cos(angle*i), midX+(r+l)*sin(angle*i), midY+(r+l)*cos(angle*i));
            }
            float angle2 = 360/50;
            for (int i=0; i < 60; i++){
                float l = ofRandom(0, 20);
                ofDrawLine(midX+r*sin(angle2*i), midY+r*cos(angle2*i), midX+(r+l)*sin(angle2*i), midY+(r+l)*cos(angle2*i));
            }
            ofSetLineWidth(2);
            ofDrawBezier(midX-75, midY+35, midX-15, midY+45, midX-17.5, midY+60, midX-90, midY+43); // left hand
            ofDrawBezier(midX+75, midY+35, midX+15, midY+45, midX+17.5, midY+60, midX+90, midY+43); // right hand
            ofDrawBezier(midX-65, midY+145, midX-55, midY+190, midX-35, midY+180, midX-25, midY+150); // left foot
            ofDrawBezier(midX+65, midY+145, midX+55, midY+190, midX+35, midY+180, midX+25, midY+150); // right foot
            break;
        }
        case 2: {
            // seesaw
            
            ofFill();
            ofSetCircleResolution(100);
            ofDrawCircle(midX, midY+50, 50); // support
//            float x1 = midX+250*sin(counter);
//            float y1 = midY+250*cos(counter);
//            float x2 = midX-250*sin(counter);
//            float y2 = midY-250*cos(counter);
//            ofNoFill();
//            ofSetLineWidth(5);
//            ofDrawLine(x1,y1,x2,y2);
            
            if (up){
                upangle = 30+counter;
            } else {
                upangle = -30+counter;
            }
            float x1 = midX+250*sin(upangle);
            float y1 = midY+250*cos(upangle);
            float x2 = midX-250*sin(upangle);
            float y2 = midY-250*cos(upangle);
            ofSetLineWidth(100);
            ofDrawLine(x1,y1,x2,y2);
            break;
        }
//
        case 3:{
            // mushroom
            ofFill();
            ofSetColor((int)ofRandom(0,255),(int)ofRandom(0,255),(int)ofRandom(0,255),255);
            ofDrawBezier(midX-100, midY, midX-17, midY-100, midX+17, midY-100, midX+100, midY);
            ofDrawBezier(midX-100, midY, midX-50, midY+50, midX+50, midY+50, midX+100, midY);
            ofDrawCircle(midX-85, midY-5, 15);
            ofDrawCircle(midX+85, midY-5, 15);
            ofDrawBezier(midX-20, midY, midX-10, midY+120, midX+10, midY+120, midX+20, midY);
            break;
        }
        case 4:{
            // square
            ofSetLineWidth(2);
            float side = 50 * sin(counter);
            ofSetHexColor(0x000000);
            ofFill();
            ofDrawRectangle(midX, midY, side, side);
            ofNoFill();
            float rand = ofRandom(0,50);
            ofDrawRectangle(midX, midY, rand, rand);
//            ofDrawCircle(midX,midY,(int)ofRandom(30));
            break;
        }
        default:
            break;
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


