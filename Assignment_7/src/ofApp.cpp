#include "ofApp.h"
const int framerate = 60;
ofVec2f mid, cur;
float delta;
ofVec2f v0(1,0);
const int seesawL = 250; // half length of seesaw
int updown; // dummy value for up/down
float maxAngle; // maximum angle of seesaw
int ind, sec;
bool dest, show;
float fallspeed, eyeR;
float tearStart, tearMid, tearEnd, tearY;
int playCounter;
//--------------------------------------------------------------
void ofApp::setup(){
    gui.setup();
    gui.add(volumn.setup("sound volumn", 0.7f, 0, 1));
    gui.add(center.setup("center", ofVec2f(ofGetWidth()*.5, ofGetHeight()*.5), ofVec2f(0, 0), ofVec2f(ofGetWidth(), ofGetHeight())));
    gui.add(color.setup("thorn color", ofColor(100, 100, 140), ofColor(0, 0), ofColor(255, 255)));
    gui.add(degree.setup("emotion degree", 1, 1, 10));
    gui.add(showcry.setup("crying hedgehog",false));
    gui.add(showangry.setup("angry hedgehog",false));
    gui.add(showconfuse.setup("confused hedgehog",false));
    gui.add(showseesaw.setup("hedgehogs playing seesaw",true));

    
    cry.load("cry.wav");
    fire.load("fire.wav");
    confusion.load("confusion.wav");
    seesaw.load("seesaw.wav");
    ofSetFrameRate(framerate);
    ofBackground(255, 255, 255);
    ofSetWindowTitle("project objects emotions with gui controls");
    mid = ofVec2f(ofGetWidth()/2,ofGetHeight()/2);
    
    delta = 0.7; // change in angle
    cur = v0*seesawL; // starting position
    
    updown = 1;
    maxAngle = v0.angle(mid);
    
    eyeR = 0;
    
    tearStart = mid.y-56+20;
    tearMid = mid.y-56+40;
    tearEnd = mid.y+140-56;
    tearY = tearStart;
    ofSetCircleResolution(100);
    
}

//--------------------------------------------------------------

void ofApp::update(){
    
    sec = ofGetFrameNum() % 4;

    mid = (ofVec2f)center;
    // teardrops
    fallspeed = ofMap(tearY, tearStart, tearEnd, 1, 10*degree);
    tearY += fallspeed;
    if (tearY >= tearEnd){
        tearY = tearStart;
    }
    
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
    cur = cur.getRotated(delta*updown*degree);
    //    cout<<alpha<<endl;
    
}

////--------------------------------------------------------------
//void ofApp::exit(){
//    showcry.removeListener(this, &ofApp::cryButtonPressed);
//}
//
//
////--------------------------------------------------------------
//void ofApp::buttonPressed(){
//    sound.play();
//}

//--------------------------------------------------------------
void ofApp::draw(){
    gui.draw();
    if (showcry){
            // crying hedgehog

            cry.play();
            cry.setVolume(volumn);
        ofPopMatrix(); 
        ofRotateYDeg(ofGetFrameNum()%360);
        ofPushMatrix();
            ofSetHexColor(0x000000);
            ofFill();
            ofDrawCircle(mid.x, mid.y-25, 10); // nose
            ofDrawCircle(mid.x-50, mid.y-50, 5); // left eye
            ofDrawCircle(mid.x+50, mid.y-50, 5); // right eye
            
            ofDrawTriangle(mid.x-50, tearY,
                           mid.x-54, tearY+10,
                           mid.x-46, tearY+10);
            ofDrawTriangle(mid.x+50, tearY,
                           mid.x+46, tearY+10,
                           mid.x+54, tearY+10);

            ofNoFill();
            ofSetLineWidth(3);

            ofPolyline rightEar, leftEar;
            leftEar.addVertex(mid.x-100, mid.y-50);
            leftEar.bezierTo(mid.x-120, mid.y-70,
                             mid.x-105, mid.y-85, mid.x-90, mid.y-75);
            rightEar.addVertex(mid.x+100, mid.y-50);
            rightEar.bezierTo(mid.x+120, mid.y-70,
                              mid.x+105, mid.y-85, mid.x+90, mid.y-75);
            leftEar.draw();
            rightEar.draw();

            ofSetLineWidth(2);
            ofDrawBezier(mid.x-75, mid.y+35, mid.x-15, mid.y+45,
                         mid.x-17.5, mid.y+60, mid.x-90, mid.y+43); // lefthand
            ofDrawBezier(mid.x+75, mid.y+35, mid.x+15, mid.y+45,
                         mid.x+17.5, mid.y+60, mid.x+90, mid.y+43); // righthand
            ofDrawBezier(mid.x-65, mid.y+145, mid.x-55, mid.y+190,
                         mid.x-35, mid.y+180, mid.x-25, mid.y+150); // leftfoot
            ofDrawBezier(mid.x+65, mid.y+145, mid.x+55, mid.y+190,
                         mid.x+35, mid.y+180, mid.x+25, mid.y+150); // rightfoot
            
            ofSetColor(color);
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
        
    } else if (showangry) {
            // angry hedgehog
        fire.play();
        fire.setVolume(volumn);
        ofSetHexColor(0x000000);
        ofFill();
        ofDrawCircle(mid.x, mid.y-25, 10); // nose
        
        ofSetHexColor(0x000000);
        ofNoFill();
        ofSetLineWidth(3);
        ofDrawBezier(mid.x-100, mid.y-50, mid.x-120, mid.y-70,
                     mid.x-105, mid.y-85, mid.x-90, mid.y-75); // left ear
        ofDrawBezier(mid.x+100, mid.y-50, mid.x+120, mid.y-70,
                     mid.x+105, mid.y-85, mid.x+90, mid.y-75); // right ear
        
        ofSetLineWidth(2);
        ofPolyline rightHand, leftHand;
        leftHand.addVertex(mid.x-75, mid.y+35);
        leftHand.bezierTo(mid.x-15, mid.y+45,
                          mid.x-17.5, mid.y+60, mid.x-90, mid.y+43);
        rightHand.addVertex(mid.x+75, mid.y+35);
        rightHand.bezierTo(mid.x+15, mid.y+45,
                           mid.x+17.5, mid.y+60, mid.x+90, mid.y+43);
        leftHand.draw();
        rightHand.draw();
        ofDrawBezier(mid.x-65, mid.y+145, mid.x-55, mid.y+190,
                     mid.x-35, mid.y+180, mid.x-25, mid.y+150); // leftfoot
        ofDrawBezier(mid.x+65, mid.y+145, mid.x+55, mid.y+190,
                     mid.x+35, mid.y+180, mid.x+25, mid.y+150); // rightfoot
        ofSetColor(color);
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
        ofSetColor(ofRandom(10*degree,255),0,0);
        ofFill();
        ofPopMatrix();
            ofRotateDeg(ofGetFrameNum()%360,0,0,1);
            ofTranslate(0,0,0);
//            mid = ofVec2f(ofGetWidth()/2,ofGetHeight()/2);
            ofDrawTriangle(mid+ofVec2f(-50,-40), mid+ofVec2f(-62,-60),
                           mid+ofVec2f(-38,-60));
            ofDrawTriangle(mid+ofVec2f(50,-40), mid+ofVec2f(62,-60),
                           mid+ofVec2f(38,-60));
        ofPushMatrix();

    } else if (showconfuse) {
            // dizzy hedgehog
        
            confusion.play();
            confusion.setVolume(volumn);

            ofSetHexColor(0x000000);
            ofFill();
            ofDrawCircle(mid.x, mid.y-25, 10); // nose
        
        ofPushMatrix();
        ofTranslate(sin(ofGetFrameNum()), cos(ofGetFrameNum()));
            ofNoFill();
            ofDrawCircle(mid.x-50, mid.y-50, 10);
            ofDrawCircle(mid.x+50, mid.y-50, 10);

            float rad1 = (10 + 5*sin(eyeR))*degree;
            float rad2 = (10 - 5*sin(eyeR))*degree;
            ofDrawCircle(mid.x-50, mid.y-50, rad1); // left eye
            ofDrawCircle(mid.x+50, mid.y-50, rad1); // right eye
            ofDrawCircle(mid.x-50, mid.y-50, rad2); // left eye
            ofDrawCircle(mid.x+50, mid.y-50, rad2); // right eye
        ofPopMatrix();
            ofSetLineWidth(3);
            ofDrawBezier(mid.x-100, mid.y-50, mid.x-120, mid.y-70,
                         mid.x-105, mid.y-85, mid.x-90, mid.y-75); // left ear
            ofDrawBezier(mid.x+100, mid.y-50, mid.x+120, mid.y-70,
                         mid.x+105, mid.y-85, mid.x+90, mid.y-75); // right ear

            ofSetLineWidth(2);
            ofDrawBezier(mid.x-75, mid.y+35, mid.x-15, mid.y+45,
                         mid.x-17.5, mid.y+60, mid.x-90, mid.y+43); // lefthand
            ofDrawBezier(mid.x+75, mid.y+35, mid.x+15, mid.y+45,
                         mid.x+17.5, mid.y+60, mid.x+90, mid.y+43); // righthand

            ofPolyline rightFoot, leftFoot;
            leftFoot.addVertex(mid.x-65, mid.y+145);
            leftFoot.bezierTo(mid.x-55, mid.y+190,
                              mid.x-35, mid.y+180, mid.x-25, mid.y+150);
            rightFoot.addVertex(mid.x+65, mid.y+145);
            rightFoot.bezierTo(mid.x+55, mid.y+190,
                               mid.x+35, mid.y+180, mid.x+25, mid.y+150);
            leftFoot.draw();
            rightFoot.draw();
            ofSetColor(color);
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

    } else if (showseesaw) {
            // seesaw hedgehog
            seesaw.play();
            seesaw.setVolume(volumn);
            ofSetHexColor(0x000000);
            ofFill();
            ofSetLineWidth(5);
//          start pose
//          cur = ofVec2f(seesawL,0);

            ofPolyline seesawBoard;
            seesawBoard.addVertex(mid.x-cur.x, mid.y-cur.y);
            seesawBoard.lineTo(mid.x+cur.x, mid.y+cur.y);
            seesawBoard.draw();

            ofDrawTriangle(mid, mid+ofVec2f(-2,3)*15, mid+ofVec2f(2,3)*15);
            
            // hedgehog left
            ofSetColor(color);
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
            
            ofSetHexColor(0x000000);
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
            ofSetColor(color);
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
            
            ofSetHexColor(0x000000);
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


