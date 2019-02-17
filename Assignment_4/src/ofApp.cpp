#include "ofApp.h"
ofVec2f mid, cur;
float delta;
ofVec2f v0(1,0);
const int seesawL = 250; // half length of seesaw
int updown; // dummy value for up/down
float maxAngle; // maximum angle of seesaw
int ind, sec;
bool dest, show;
float fallspeed, eyeR;

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetFrameRate(60);
    ofBackground(255, 255, 255);
    ofSetWindowTitle("project objects emotions & more");
    mid = ofVec2f(ofGetWidth()/2,ofGetHeight()/2);
    
    delta = 0.7; // change in angle
    cur = v0*seesawL; // starting position

    updown = 1;
    maxAngle = v0.angle(mid);
    
    eyeR = 0;
}

//--------------------------------------------------------------

void ofApp::update(){
    
    
//    dest = (ofGetFrameNum() / 60) % 3 == 1 ;
    show = (ofGetFrameNum() / 60) % 3 != 1 ;
    sec = (ofGetFrameNum() / 60) % 60;
    if (sec <= 3){
        ind = 1;
    } else if (sec <= 6) {
        ind = 2;
    } else if (sec <= 9) {
        ind = 3;
    } else if (sec <= 12){
        ind = 4;
    }
    fallspeed += 1;
    
    // current angle
    float alpha;
    alpha = v0.angle(cur);
    
    // ease
    float counter;
    counter = ofMap(alpha, 0, maxAngle, 0, 0.01);
    delta -= counter;
    
    // switch from up to down / down to up
    if (abs(alpha) > abs(maxAngle/2)){
        updown *= -1;
    }
    
    eyeR += 0.033f;
    
    // rotate
    cur = cur.getRotated(delta*updown);
//    cout<<alpha<<endl;
}


//--------------------------------------------------------------
void ofApp::draw(){

    switch (ind) {
        case 1: {
            // crying hedgehog
            ofSetHexColor(0x000000);
            ofFill();
            ofDrawCircle(mid.x, mid.y-25, 10); // nose
            ofDrawCircle(mid.x-50, mid.y-50, 5); // left eye
            ofDrawCircle(mid.x+50, mid.y-50, 5); // right eye

            if (sec >=1 ){
                for (int i =0; i< 140; i+=20){
                    ofDrawTriangle(mid+ofVec2f(-50, -56+fallspeed+i),
                                   mid+ofVec2f(-54, -46+fallspeed+i),
                                   mid+ofVec2f(-46, -46+fallspeed+i));
                    ofDrawTriangle(mid+ofVec2f(50, -56+fallspeed+i),
                                   mid+ofVec2f(46, -46+fallspeed+i),
                                   mid+ofVec2f(54, -46+fallspeed+i));
                }
            } else {
                for (int i =0; i< 140; i+=20){
                    ofDrawTriangle(mid+ofVec2f(-50, -56+i),
                                   mid+ofVec2f(-54, -46+i),
                                   mid+ofVec2f(-46, -46+i));
                    ofDrawTriangle(mid+ofVec2f(50, -56+i),
                                   mid+ofVec2f(46, -46+i),
                                   mid+ofVec2f(54, -46+i));
                }
            }
            ofNoFill();
            ofSetLineWidth(3.5);
            ofDrawBezier(mid.x-100, mid.y-50, mid.x-120, mid.y-70,
                         mid.x-105, mid.y-85, mid.x-90, mid.y-75); // left ear
            ofDrawBezier(mid.x+100, mid.y-50, mid.x+120, mid.y-70,
                         mid.x+105, mid.y-85, mid.x+90, mid.y-75); // right ear
            ofSetLineWidth(2);
            float r = 150;
            float angle = 360/60;
            for (int i=0; i < 60; i++){
                float l = ofRandom(0, 20);
                ofDrawLine(mid.x+r*sin(angle*i), mid.y+r*cos(angle*i),
                           mid.x+(r+l)*sin(angle*i), mid.y+(r+l)*cos(angle*i));
            }
            float angle2 = 360/50;
            for (int i=0; i < 60; i++){
                float l = ofRandom(0, 20);
                ofDrawLine(mid.x+r*sin(angle2*i), mid.y+r*cos(angle2*i),
                           mid.x+(r+l)*sin(angle2*i), mid.y+(r+l)*cos(angle2*i));
            }
            ofSetLineWidth(2);
            ofDrawBezier(mid.x-75, mid.y+35, mid.x-15, mid.y+45,
                         mid.x-17.5, mid.y+60, mid.x-90, mid.y+43); // lefthand
            ofDrawBezier(mid.x+75, mid.y+35, mid.x+15, mid.y+45,
                         mid.x+17.5, mid.y+60, mid.x+90, mid.y+43); // righthand
            ofDrawBezier(mid.x-65, mid.y+145, mid.x-55, mid.y+190,
                         mid.x-35, mid.y+180, mid.x-25, mid.y+150); // leftfoot
            ofDrawBezier(mid.x+65, mid.y+145, mid.x+55, mid.y+190,
                         mid.x+35, mid.y+180, mid.x+25, mid.y+150); // rightfoot
            break;
        }
        case 2: {
            // angry hedgehog
            ofFill();
            ofDrawCircle(mid.x, mid.y-25, 10); // nose
            if (show){
                ofSetColor(ofRandom(100,255),0,0);
            }
            ofDrawTriangle(mid+ofVec2f(-50,-40), mid+ofVec2f(-62,-60),
                           mid+ofVec2f(-38,-60));
            ofDrawTriangle(mid+ofVec2f(50,-40), mid+ofVec2f(62,-60),
                           mid+ofVec2f(38,-60));
            
            ofSetHexColor(0x000000);
            ofNoFill();
            ofSetLineWidth(3.5);
            ofDrawBezier(mid.x-100, mid.y-50, mid.x-120, mid.y-70,
                         mid.x-105, mid.y-85, mid.x-90, mid.y-75); // left ear
            ofDrawBezier(mid.x+100, mid.y-50, mid.x+120, mid.y-70,
                         mid.x+105, mid.y-85, mid.x+90, mid.y-75); // right ear
            ofSetLineWidth(2);
            float r = 150;
            float angle = 360/60;
            for (int i=0; i < 60; i++){
                float l = ofRandom(0, 20);
                ofDrawLine(mid.x+r*sin(angle*i), mid.y+r*cos(angle*i),
                           mid.x+(r+l)*sin(angle*i), mid.y+(r+l)*cos(angle*i));
            }
            float angle2 = 360/50;
            for (int i=0; i < 60; i++){
                float l = ofRandom(0, 20);
                ofDrawLine(mid.x+r*sin(angle2*i), mid.y+r*cos(angle2*i),
                           mid.x+(r+l)*sin(angle2*i), mid.y+(r+l)*cos(angle2*i));
            }
            ofSetLineWidth(2);
            ofDrawBezier(mid.x-75, mid.y+35, mid.x-15, mid.y+45,
                         mid.x-17.5, mid.y+60, mid.x-90, mid.y+43); // lefthand
            ofDrawBezier(mid.x+75, mid.y+35, mid.x+15, mid.y+45,
                         mid.x+17.5, mid.y+60, mid.x+90, mid.y+43); // righthand
            ofDrawBezier(mid.x-65, mid.y+145, mid.x-55, mid.y+190,
                         mid.x-35, mid.y+180, mid.x-25, mid.y+150); // leftfoot
            ofDrawBezier(mid.x+65, mid.y+145, mid.x+55, mid.y+190,
                         mid.x+35, mid.y+180, mid.x+25, mid.y+150); // rightfoot
            break;
        }
//
        case 3: {
            // dizzy hedgehog
            ofSetHexColor(0x000000);
            ofFill();
            ofDrawCircle(mid.x, mid.y-25, 10); // nose
   
            ofNoFill();
            ofDrawCircle(mid.x-50, mid.y-50, 10);
            ofDrawCircle(mid.x+50, mid.y-50, 10);
            if (show){
                float rad1 = 10 + 5*sin(eyeR);
                float rad2 = 10 - 5*sin(eyeR);
                ofDrawCircle(mid.x-50, mid.y-50, rad1); // left eye
                ofDrawCircle(mid.x+50, mid.y-50, rad1); // right eye
                ofDrawCircle(mid.x-50, mid.y-50, rad2); // left eye
                ofDrawCircle(mid.x+50, mid.y-50, rad2); // right eye
            }

            ofSetLineWidth(3.5);
            ofDrawBezier(mid.x-100, mid.y-50, mid.x-120, mid.y-70,
                         mid.x-105, mid.y-85, mid.x-90, mid.y-75); // left ear
            ofDrawBezier(mid.x+100, mid.y-50, mid.x+120, mid.y-70,
                         mid.x+105, mid.y-85, mid.x+90, mid.y-75); // right ear
            ofSetLineWidth(2);
            float r = 150;
            float angle = 360/60;
            for (int i=0; i < 60; i++){
                float l = ofRandom(0, 20);
                ofDrawLine(mid.x+r*sin(angle*i), mid.y+r*cos(angle*i),
                           mid.x+(r+l)*sin(angle*i), mid.y+(r+l)*cos(angle*i));
            }
            float angle2 = 360/50;
            for (int i=0; i < 60; i++){
                float l = ofRandom(0, 20);
                ofDrawLine(mid.x+r*sin(angle2*i), mid.y+r*cos(angle2*i),
                           mid.x+(r+l)*sin(angle2*i), mid.y+(r+l)*cos(angle2*i));
            }
            ofSetLineWidth(2);
            ofDrawBezier(mid.x-75, mid.y+35, mid.x-15, mid.y+45,
                         mid.x-17.5, mid.y+60, mid.x-90, mid.y+43); // lefthand
            ofDrawBezier(mid.x+75, mid.y+35, mid.x+15, mid.y+45,
                         mid.x+17.5, mid.y+60, mid.x+90, mid.y+43); // righthand
            ofDrawBezier(mid.x-65, mid.y+145, mid.x-55, mid.y+190,
                         mid.x-35, mid.y+180, mid.x-25, mid.y+150); // leftfoot
            ofDrawBezier(mid.x+65, mid.y+145, mid.x+55, mid.y+190,
                         mid.x+35, mid.y+180, mid.x+25, mid.y+150); // rightfoot
            break;
        }
        case 4:{
            // seesaw hedgehog
            ofSetHexColor(0x000000);
            ofFill();
            ofSetLineWidth(5);
            if (!show){
                cur = ofVec2f(seesawL,0);
            }
            ofDrawLine(mid-cur, cur+mid);
            ofDrawTriangle(mid, mid+ofVec2f(-2,3)*15, mid+ofVec2f(2,3)*15);
            
            // hedgehog left
            ofSetLineWidth(1);
            ofVec2f lcenter(mid-cur+ofVec2f(20,-50));
            ofNoFill();
            float r = 45;
            float angle = 360/60;
            for (int i=0; i < 60; i++){
                if (sin(angle*i)<0.5){
                    float l = ofRandom(0, 7);
                    ofVec2f dir(sin(angle*i), cos(angle*i));
                    ofDrawLine(lcenter+dir*(r-2),lcenter+dir*(r+l));
                }
            }
            float angle2 = 360/50;
            for (int i=0; i < 60; i++){
                if (sin(angle2*i)<0.5){
                    float l = ofRandom(0, 7);
                    ofVec2f dir(sin(angle2*i), cos(angle2*i));
                    ofDrawLine(lcenter+dir*(r-5),lcenter+dir*(r-3+l));
                }
            }
            
            ofDrawBezier(lcenter.x-18,lcenter.y-20,
                         lcenter.x-24,lcenter.y-21, lcenter.x-26, lcenter.y-17,
                         lcenter.x-22,lcenter.y-18); // ear
            ofDrawCurve(lcenter.x+60,lcenter.y-10,
                        lcenter.x+r/2+2,lcenter.y+r*cos(60)+8, lcenter.x+43, lcenter.y-20,
                        lcenter.x+100,lcenter.y-10); // face
            ofDrawCurve(lcenter.x-40,lcenter.y+24,
                        lcenter.x+45, lcenter.y-12, lcenter.x+r/2+2,lcenter.y-r*cos(60)-8,
                        lcenter.x-60,lcenter.y+20); // body
            ofFill();
            ofDrawCircle(lcenter+ofVec2f(20,-18), 3); // eye
            ofDrawCircle(lcenter+ofVec2f(48,-18), 2.5); // nose
            
            // hedgehog right
            ofSetLineWidth(1);
            ofVec2f rcenter(mid+cur+ofVec2f(-20,-50));
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


