#include "ofApp.h"
// constants
const int framerate = 60;
float r = 150;
float angle = 360/60;
float angle2 = 360/50;
ofVec2f fbocenter(200,200);

// declared in setup
float winW,winH;
ofVec2f mid;
ofFbo fboNormal,fboCry,fboAngry,fboDizzy,fboL,fboR,
      fboTitle,
      fboMushroom, fboBoat;

// colors & fonts & images
ofColor stroke(0,0,0);
ofColor white(255,255,255);
ofTrueTypeFont walterturncoat;
string title, subtitle;
string textToDraw;
int timeBeginWait;
ofImage headingleft, headingright,
        backpack,bgS1,
        mushroom1, mushroom2, mushroom3, mushroom4, mushroom5,
        mushroom6, mushroom7, mushroom8, mushroom9,
        bgS3, bgS4, bee, sock, bush, bgS7, bgS8,
        treehole;
ofSoundPlayer bgm;
// changing vars
int scene;
ofVec2f cur,mouse;
float currentT;
float stepX, stepY, stepAngle, stepScale;
float imgW, imgH;

// seesaw vars
ofVec2f v0(1,0), cur0;
const int seesawL = 350; // half length of seesaw
float delta;
int updown; // dummy value for up/down
float maxAngle; // maximum angle of seesaw
bool flyaway;

// crying vars
float fallspeed;
float tearStart, tearMid, tearEnd, tearY;

// dizzy vars
float eyeR;


//--------------------------------------------------------------
void ofApp::setup(){
    /********************* basic settings **********************/
    ofSetFrameRate(framerate);
    ofSetCircleResolution(100);
    ofSetCurveResolution(100);
    ofBackground(white);
    winW = ofGetWidth();
    winH = ofGetHeight();
    mid = ofVec2f(winW/2,winH/2);
    /***********************************************************/
    
    /********************* fonts & images **********************/
    walterturncoat.load("WalterTurncoat.ttf", 24, false);
//    walterturncoat.setLineHeight(18.0f);
//    walterturncoat.setLetterSpacing(1.037);
    title = "Zehn kleine Igelkinder";
    subtitle = "Ten Little Hedgehogs";
    textToDraw ="";
    timeBeginWait = ofGetElapsedTimeMillis();
    headingleft.load("headingLeft.png");
    headingright.load("headingright.png");
    backpack.load("backpack.png");
    bgS1.load("bgS1.png");
    mushroom1.load("Mushroom1.png");
    mushroom2.load("Mushroom2.png");
    mushroom3.load("Mushroom3.png");
    mushroom4.load("Mushroom4.png");
    mushroom5.load("Mushroom5.png");
    mushroom6.load("Mushroom6.png");
    mushroom7.load("Mushroom7.png");
    mushroom8.load("Mushroom8.png");
    mushroom9.load("Mushroom9.png");
    bgS3.load("bgS3.png");
    bgS4.load("bgS4.JPG");
    bee.load("bee.png");
    sock.load("sock.png");
    bush.load("bush.png");
    bgS7.load("bgS7.png");
    bgS8.load("bgS8.png");
    treehole.load("treehole.JPG");
    bgm.load("bgm.wav");
    bgm.play();
    /***********************************************************/
    
    /********************** fbo settings ***********************/
    fboNormal.allocate(400, 400, GL_RGBA32F);
    fboCry.allocate(400, 400, GL_RGBA32F);
    fboAngry.allocate(400, 400, GL_RGBA32F);
    fboDizzy.allocate(400, 400, GL_RGBA32F);
    fboL.allocate(400, 400, GL_RGBA32F);
    fboR.allocate(400, 400, GL_RGBA32F);
    fboTitle.allocate(400, 120, GL_RGBA32F);
    fboMushroom.allocate(400, 400, GL_RGBA32F);
    fboBoat.allocate(400, 400, GL_RGBA32F);
    
    fboNormal.setAnchorPoint(fbocenter.x,fbocenter.y);
    fboCry.setAnchorPoint(fbocenter.x,fbocenter.y);
    fboAngry.setAnchorPoint(fbocenter.x,fbocenter.y);
    fboDizzy.setAnchorPoint(fbocenter.x,fbocenter.y);
    fboL.setAnchorPoint(fbocenter.x,fbocenter.y);
    fboR.setAnchorPoint(fbocenter.x,fbocenter.y);
    fboTitle.setAnchorPoint(200,60);
    fboMushroom.setAnchorPoint(fbocenter.x,fbocenter.y);
    fboBoat.setAnchorPoint(fbocenter.x,fbocenter.y);
    
    fboNormal.begin();
    ofClear(255,255,255, 0);
    fboNormal.end();
    fboCry.begin();
    ofClear(255,255,255, 0);
    fboCry.end();
    fboAngry.begin();
    ofClear(255,255,255, 0);
    fboAngry.end();
    fboDizzy.begin();
    ofClear(255,255,255, 0);
    fboDizzy.end();
    fboL.begin();
    ofClear(255,255,255, 0);
    fboL.end();
    fboR.begin();
    ofClear(255,255,255, 0);
    fboR.end();
    fboTitle.begin();
    ofClear(255,255,255, 0);
    fboTitle.end();
    fboMushroom.begin();
    ofClear(255,255,255, 0);
    fboMushroom.end();
    fboBoat.begin();
    ofClear(255,255,255, 0);
    fboBoat.end();
    /***********************************************************/
    
    /********************** update settings ********************/
    delta = 0.7; // change in angle
    cur0 = v0*seesawL; // starting position
    
    updown = 1;
    maxAngle = v0.angle(mid);
    tearStart = fbocenter.y-56+20;
    tearMid = fbocenter.y-56+40;
    tearEnd = fbocenter.y+140-56;
    tearY = tearStart;
    eyeR = 0;

    flyaway = false;
    /***********************************************************/
}

//--------------------------------------------------------------
void ofApp::update(){
    currentT = ofGetElapsedTimef();
    if (currentT < 11){
        scene = 0;
        imgW = headingleft.getWidth();
        imgH = headingleft.getHeight();
        stepX = ofMap(currentT,0,11,0,winW);
    } else if (currentT < 21){
        scene = 1;
        imgW = backpack.getWidth();
        imgH = backpack.getHeight();
        cur.x = ofMap(currentT,11,21,100,winW-100);
        cur.y = winH+ofSignedNoise(currentT)*5-100;
    } else if (currentT< 30){
        scene = 2;
        eyeR += 0.033f;
        stepAngle = ofMap(currentT,21,30,0,2*PI);
    } else if (currentT < 40){
        scene = 3;
        imgW = bgS3.getWidth();
        imgH = bgS3.getHeight();
        // 780, 250
        // 920, 590
        cur.x = ofMap(currentT, 30, 40, 780, winW);
        cur.y = ofMap(currentT, 30, 40, 350, winH);
        stepAngle = ofMap(currentT, 15, 20, 0, 2*PI);
    } else if (currentT <49) {
        scene = 4;
        stepX = ofMap(currentT,40,49,0,400);
        if (cur.x>mid.x+300 || cur.x<mid.x-300){
            stepX *= -1;
        }
        cur.x = mid.x+stepX;
        cur.y = ofMap(currentT,40,49,100,winH-100);
        stepScale = ofMap(currentT,40,49, 0, 1);
        fallspeed = ofMap(tearY, tearStart, tearEnd, 1, 10);
        tearY += fallspeed;
        if (tearY >= tearEnd){
            tearY = tearStart;
        }
    } else if (currentT <57) {
        scene = 5;
        imgW = sock.getWidth();
        imgH = sock.getHeight();
        cur.x = ofMap(currentT,49,57,400,winW-200);
        cur.y = winH-50;
        stepScale = ofMap(currentT,49,57, 2, 1);
    } else if (currentT <67) {
        scene = 6;
        imgW = bush.getWidth();
        imgH = bush.getHeight();
    } else if (currentT <77) {
        scene = 7;
        imgW = bgS7.getWidth();
        imgH = bgS7.getHeight();
        // 870 550
        cur.x = 900;
        if (currentT<69){
            cur.y = ofMap(currentT, 67, 69, 0, 570);
        } else if (currentT<71){
            cur.y = ofMap(currentT, 69, 71, 570, 500);
        } else if (currentT<73){
            cur.y = ofMap(currentT, 71, 73, 500, 570);
        } else if (currentT<75){
            cur.y = ofMap(currentT, 73, 75, 570, 540);
        } else {
            cur.y = ofMap(currentT, 75, 77, 540, 570);
        }
    } else if (currentT <87) {
        scene = 8;
        imgW = bgS8.getWidth();
        imgH = bgS8.getHeight();
        // current angle
        float alpha;
        alpha = v0.angle(cur0);
        // ease
        float counter;
        counter = ofMap(alpha, 0, maxAngle, 0, 0.01);
        delta -= counter;
        // switch from up to down / down to up
        if (abs(alpha) > abs(maxAngle/2)){
            updown *= -1;
        }
        if (currentT>82){
            cur0 = ofVec2f(v0*seesawL).getRotated(-maxAngle/2);
            flyaway = true;
//            stepAngle = ofMap(currentT, 45, 50, 0, PI/2);
            stepX = ofMap(currentT,82,87,0,winW-cur0.x);
            stepAngle = stepX*PI/2/(winW-cur0.x);
            cur.x = cur0.x+stepX;
            cur.y = cur0.y-cur0.y*sin(stepAngle);
        } else {
            // rotate
            cur0 = cur0.getRotated(delta*updown);
        }
    } else if (currentT <96) {
        scene = 9;
        cur.x = ofMap(currentT,87,96,ofGetWidth()-20,20);
        cur.y = ofSignedNoise(currentT*0.4)*200+ofGetHeight()/2;
    } else if (currentT <105) {
        scene = 10;
        imgW = mushroom9.getWidth();
        imgH = mushroom9.getHeight();
        
    } else if (currentT <110) {
        scene = 11;
    } else {
        scene = 12;
    }
    
}


//--------------------------------------------------------------
void ofApp::draw(){
    /***************************************************************
     ************************* CREATE FBOS *************************
     **************************************************************/
    
    /********************** normal hedgehog **********************/
    fboNormal.begin();
        ofSetColor(white); // background color with alpha
        ofDrawCircle(fbocenter.x, fbocenter.y,200);
        ofSetColor(stroke);
        ofFill();
        ofDrawCircle(fbocenter.x, fbocenter.y-25, 10); // nose
        ofDrawCircle(fbocenter.x-50, fbocenter.y-50, 5); // left eye
        ofDrawCircle(fbocenter.x+50, fbocenter.y-50, 5); // right eye
        ofNoFill();
        ofSetLineWidth(3);
        ofDrawBezier(fbocenter.x-100, fbocenter.y-50,
                     fbocenter.x-120, fbocenter.y-70,
                     fbocenter.x-105, fbocenter.y-85,
                     fbocenter.x-90, fbocenter.y-75); // left ear
        ofDrawBezier(fbocenter.x+100, fbocenter.y-50,
                     fbocenter.x+120, fbocenter.y-70,
                     fbocenter.x+105, fbocenter.y-85,
                     fbocenter.x+90, fbocenter.y-75); // right ear
        // body
        ofSetLineWidth(2);
        for (int i=0; i < 60; i++){
            float l = ofRandom(0, 20);
            ofDrawLine(fbocenter.x+r*sin(angle*i),
                       fbocenter.y+r*cos(angle*i),
                       fbocenter.x+(r+l)*sin(angle*i),
                       fbocenter.y+(r+l)*cos(angle*i));
        }
        for (int i=0; i < 60; i++){
            float l = ofRandom(0, 20);
            ofDrawLine(fbocenter.x+r*sin(angle2*i),
                       fbocenter.y+r*cos(angle2*i),
                       fbocenter.x+(r+l)*sin(angle2*i),
                       fbocenter.y+(r+l)*cos(angle2*i));
        }
        // limbs
        ofSetLineWidth(2);
        ofDrawBezier(fbocenter.x-75, fbocenter.y+35,
                     fbocenter.x-15, fbocenter.y+45,
                     fbocenter.x-17.5, fbocenter.y+60,
                     fbocenter.x-90, fbocenter.y+43); // lefthand
        ofDrawBezier(fbocenter.x+75, fbocenter.y+35,
                     fbocenter.x+15, fbocenter.y+45,
                     fbocenter.x+17.5, fbocenter.y+60,
                     fbocenter.x+90, fbocenter.y+43); // righthand
        ofDrawBezier(fbocenter.x-65, fbocenter.y+145,
                     fbocenter.x-55, fbocenter.y+190,
                     fbocenter.x-35, fbocenter.y+180,
                     fbocenter.x-25, fbocenter.y+150); // leftfoot
        ofDrawBezier(fbocenter.x+65, fbocenter.y+145,
                     fbocenter.x+55, fbocenter.y+190,
                     fbocenter.x+35, fbocenter.y+180,
                     fbocenter.x+25, fbocenter.y+150); // rightfoot
    fboNormal.end();
    /*************************************************************/
    
    /********************** crying hedgehog **********************/
    fboCry.begin();
        ofSetColor(white); // background color with alpha
        ofDrawCircle(fbocenter.x, fbocenter.y,200);
        ofSetColor(stroke);
        ofFill();
        ofDrawCircle(fbocenter.x, fbocenter.y-25, 10); // nose
        ofDrawCircle(fbocenter.x-50, fbocenter.y-50, 5); // left eye
        ofDrawCircle(fbocenter.x+50, fbocenter.y-50, 5); // right eye
        // tears
        ofDrawTriangle(fbocenter.x-50, tearY,
                       fbocenter.x-54, tearY+10,
                       fbocenter.x-46, tearY+10);
        ofDrawTriangle(fbocenter.x+50, tearY,
                       fbocenter.x+46, tearY+10,
                       fbocenter.x+54, tearY+10);
        ofNoFill();
        ofSetLineWidth(3);
        ofDrawBezier(fbocenter.x-100, fbocenter.y-50,
                     fbocenter.x-120, fbocenter.y-70,
                     fbocenter.x-105, fbocenter.y-85,
                     fbocenter.x-90, fbocenter.y-75); // left ear
        ofDrawBezier(fbocenter.x+100, fbocenter.y-50,
                     fbocenter.x+120, fbocenter.y-70,
                     fbocenter.x+105, fbocenter.y-85,
                     fbocenter.x+90, fbocenter.y-75); // right ear
        // body
        ofSetLineWidth(2);
        for (int i=0; i < 60; i++){
            float l = ofRandom(0, 20);
            ofDrawLine(fbocenter.x+r*sin(angle*i), fbocenter.y+r*cos(angle*i),
                       fbocenter.x+(r+l)*sin(angle*i), fbocenter.y+(r+l)*cos(angle*i));
        }
        for (int i=0; i < 60; i++){
            float l = ofRandom(0, 20);
            ofDrawLine(fbocenter.x+r*sin(angle2*i), fbocenter.y+r*cos(angle2*i),
                       fbocenter.x+(r+l)*sin(angle2*i), fbocenter.y+(r+l)*cos(angle2*i));
        }
        // limbs
        ofSetLineWidth(2);
        ofDrawBezier(fbocenter.x-75, fbocenter.y+35,
                     fbocenter.x-15, fbocenter.y+45,
                     fbocenter.x-17.5, fbocenter.y+60,
                     fbocenter.x-90, fbocenter.y+43); // lefthand
        ofDrawBezier(fbocenter.x+75, fbocenter.y+35,
                     fbocenter.x+15, fbocenter.y+45,
                     fbocenter.x+17.5, fbocenter.y+60,
                     fbocenter.x+90, fbocenter.y+43); // righthand
        ofDrawBezier(fbocenter.x-65, fbocenter.y+145,
                     fbocenter.x-55, fbocenter.y+190,
                     fbocenter.x-35, fbocenter.y+180,
                     fbocenter.x-25, fbocenter.y+150); // leftfoot
        ofDrawBezier(fbocenter.x+65, fbocenter.y+145,
                     fbocenter.x+55, fbocenter.y+190,
                     fbocenter.x+35, fbocenter.y+180,
                     fbocenter.x+25, fbocenter.y+150); // rightfoot
    fboCry.end();
    /*************************************************************/
    
    /**********************  angry hedgehog **********************/
    fboAngry.begin();
        ofSetColor(white); // background color with alpha
        ofDrawCircle(fbocenter.x, fbocenter.y,200);
        ofSetColor(stroke);
        ofFill();
        ofDrawCircle(fbocenter.x, fbocenter.y-25, 10); // nose
        ofSetColor(ofRandom(100,255),0,0);
        ofDrawTriangle(fbocenter+ofVec2f(-50,-40),
                       fbocenter+ofVec2f(-62,-60),
                       fbocenter+ofVec2f(-38,-60)); // left eye
        ofDrawTriangle(fbocenter+ofVec2f(50,-40),
                       fbocenter+ofVec2f(62,-60),
                       fbocenter+ofVec2f(38,-60)); // right eye
        ofSetColor(stroke);
        ofNoFill();
        ofSetLineWidth(3);
        ofDrawBezier(fbocenter.x-100, fbocenter.y-50,
                     fbocenter.x-120, fbocenter.y-70,
                     fbocenter.x-105, fbocenter.y-85,
                     fbocenter.x-90, fbocenter.y-75); // left ear
        ofDrawBezier(fbocenter.x+100, fbocenter.y-50,
                     fbocenter.x+120, fbocenter.y-70,
                     fbocenter.x+105, fbocenter.y-85,
                     fbocenter.x+90, fbocenter.y-75); // right ear
        // body
        ofSetLineWidth(2);
        for (int i=0; i < 60; i++){
            float l = ofRandom(0, 20);
            ofDrawLine(fbocenter.x+r*sin(angle*i),
                       fbocenter.y+r*cos(angle*i),
                       fbocenter.x+(r+l)*sin(angle*i),
                       fbocenter.y+(r+l)*cos(angle*i));
        }
        for (int i=0; i < 60; i++){
            float l = ofRandom(0, 20);
            ofDrawLine(fbocenter.x+r*sin(angle2*i),
                       fbocenter.y+r*cos(angle2*i),
                       fbocenter.x+(r+l)*sin(angle2*i),
                       fbocenter.y+(r+l)*cos(angle2*i));
        }
        ofSetLineWidth(2);
        ofDrawBezier(fbocenter.x-75, fbocenter.y+35,
                     fbocenter.x-15, fbocenter.y+45,
                     fbocenter.x-17.5, fbocenter.y+60,
                     fbocenter.x-90, fbocenter.y+43); // lefthand
        ofDrawBezier(fbocenter.x+75, fbocenter.y+35,
                     fbocenter.x+15, fbocenter.y+45,
                     fbocenter.x+17.5, fbocenter.y+60,
                     fbocenter.x+90, fbocenter.y+43); // righthand
        ofDrawBezier(fbocenter.x-65, fbocenter.y+145,
                     fbocenter.x-55, fbocenter.y+190,
                     fbocenter.x-35, fbocenter.y+180,
                     fbocenter.x-25, fbocenter.y+150); // leftfoot
        ofDrawBezier(fbocenter.x+65, fbocenter.y+145,
                     fbocenter.x+55, fbocenter.y+190,
                     fbocenter.x+35, fbocenter.y+180,
                     fbocenter.x+25, fbocenter.y+150); // rightfoot
    fboAngry.end();
    /*************************************************************/
    
    /********************** dizzy hedgehog **********************/
    fboDizzy.begin();
        ofSetColor(white); // background color with alpha
        ofDrawCircle(fbocenter.x, fbocenter.y,200);
        ofSetColor(stroke);
        ofFill();
        ofDrawCircle(fbocenter.x, fbocenter.y-25, 10); // nose
        // eyes
        ofNoFill();
        ofDrawCircle(fbocenter.x-50, fbocenter.y-50, 10);
        ofDrawCircle(fbocenter.x+50, fbocenter.y-50, 10);
        float rad1 = 10 + 5*sin(eyeR);
        float rad2 = 10 - 5*sin(eyeR);
        ofDrawCircle(fbocenter.x-50, fbocenter.y-50, rad1); // left eye
        ofDrawCircle(fbocenter.x+50, fbocenter.y-50, rad1); // right eye
        ofDrawCircle(fbocenter.x-50, fbocenter.y-50, rad2); // left eye
        ofDrawCircle(fbocenter.x+50, fbocenter.y-50, rad2); // right eye
        // ears
        ofSetLineWidth(3);
        ofDrawBezier(fbocenter.x-100, fbocenter.y-50,
                     fbocenter.x-120, fbocenter.y-70,
                     fbocenter.x-105, fbocenter.y-85,
                     fbocenter.x-90, fbocenter.y-75); // left ear
        ofDrawBezier(fbocenter.x+100, fbocenter.y-50,
                     fbocenter.x+120, fbocenter.y-70,
                     fbocenter.x+105, fbocenter.y-85,
                     fbocenter.x+90, fbocenter.y-75); // right ear
        // body
        ofSetLineWidth(2);
        for (int i=0; i < 60; i++){
            float l = ofRandom(0, 20);
            ofDrawLine(fbocenter.x+r*sin(angle*i),
                       fbocenter.y+r*cos(angle*i),
                       fbocenter.x+(r+l)*sin(angle*i),
                       fbocenter.y+(r+l)*cos(angle*i));
        }
        for (int i=0; i < 60; i++){
            float l = ofRandom(0, 20);
            ofDrawLine(fbocenter.x+r*sin(angle2*i),
                       fbocenter.y+r*cos(angle2*i),
                       fbocenter.x+(r+l)*sin(angle2*i),
                       fbocenter.y+(r+l)*cos(angle2*i));
        }
        // limbs
        ofSetLineWidth(2);
        ofDrawBezier(fbocenter.x-75, fbocenter.y+35,
                     fbocenter.x-15, fbocenter.y+45,
                     fbocenter.x-17.5, fbocenter.y+60,
                     fbocenter.x-90, fbocenter.y+43); // lefthand
        ofDrawBezier(fbocenter.x+75, fbocenter.y+35,
                     fbocenter.x+15, fbocenter.y+45,
                     fbocenter.x+17.5, fbocenter.y+60,
                     fbocenter.x+90, fbocenter.y+43); // righthand
        ofDrawBezier(fbocenter.x-65, fbocenter.y+145,
                     fbocenter.x-55, fbocenter.y+190,
                     fbocenter.x-35, fbocenter.y+180,
                     fbocenter.x-25, fbocenter.y+150); // leftfoot
        ofDrawBezier(fbocenter.x+65, fbocenter.y+145,
                     fbocenter.x+55, fbocenter.y+190,
                     fbocenter.x+35, fbocenter.y+180,
                     fbocenter.x+25, fbocenter.y+150); // rightfoot
    fboDizzy.end();
    /*************************************************************/
    
    /**********************  left hedgehog **********************/
    fboL.begin();
        ofSetColor(white); // background color with alpha
        ofDrawCircle(fbocenter.x, fbocenter.y,200);
        ofSetColor(stroke);
        ofSetLineWidth(2);
        //    ofVec2f lcenter(-cur+ofVec2f(20,-50)+ofVec2f(flyaway*flyaway,        -25*flyaway));
        ofNoFill();
        for (int i=0; i < 60; i++){
            if (sin(angle*i)<0.5){
                float l = ofRandom(0, 20);
                ofVec2f dir(sin(angle*i), cos(angle*i));
                ofDrawLine(fbocenter+dir*(r-6),fbocenter+dir*(r+l));
            }
        }
        for (int i=0; i < 60; i++){
            if (sin(angle2*i)<0.5){
                float l = ofRandom(0, 20);
                ofVec2f dir(sin(angle2*i), cos(angle2*i));
                ofDrawLine(fbocenter+dir*(r-15),fbocenter+dir*(r-9+l));
            }
        }
        ofSetLineWidth(2.5);
        ofDrawBezier(fbocenter.x-100+40, fbocenter.y-50,
                     fbocenter.x-120+40, fbocenter.y-70,
                     fbocenter.x-105+40, fbocenter.y-85,
                     fbocenter.x-90+40, fbocenter.y-75); // ear
        ofSetLineWidth(1.5);
        ofDrawCurve(fbocenter.x+60*3-20,fbocenter.y-10*3,
                    fbocenter.x+r/2+2*3,fbocenter.y+r*cos(60)+8*3,
                    fbocenter.x+43*3, fbocenter.y-20*3,
                    fbocenter.x+100*3,fbocenter.y-10*3); // face
        ofDrawCurve(fbocenter.x,fbocenter.y-24*6,
                    fbocenter.x+45*3+10, fbocenter.y-12*3,
                    fbocenter.x+r/2+2*3,fbocenter.y-r*cos(60)-8*3,
                    fbocenter.x-60*3,fbocenter.y+20*3); // body
        ofFill();
        ofDrawCircle(fbocenter+ofVec2f(20*3,-18*3), 3*3); // eye
        ofDrawCircle(fbocenter+ofVec2f(48*3,-18*3), 2*3); // nose
    fboL.end();
    /*************************************************************/
    
    /********************** right hedgehog **********************/
    fboR.begin();
        ofSetColor(white); // background color with alpha
        ofDrawCircle(fbocenter.x, fbocenter.y,200);
        ofSetColor(stroke);
        ofSetLineWidth(2);
        //    ofVec2f lcenter(-cur+ofVec2f(20,-50)+ofVec2f(flyaway*flyaway,        -25*flyaway));
        ofNoFill();
        for (int i=0; i < 60; i++){
            if (sin(angle*i)>-0.5){
                float l = ofRandom(0, 20);
                ofVec2f dir(sin(angle*i), cos(angle*i));
                ofDrawLine(fbocenter+dir*(r-6),fbocenter+dir*(r+l));
            }
        }
        for (int i=0; i < 60; i++){
            if (sin(angle2*i)>-0.5){
                float l = ofRandom(0, 20);
                ofVec2f dir(sin(angle2*i), cos(angle2*i));
                ofDrawLine(fbocenter+dir*(r-15),fbocenter+dir*(r-9+l));
            }
        }
        ofSetLineWidth(2.5);
        ofDrawBezier(fbocenter.x+100-40, fbocenter.y-50,
                     fbocenter.x+120-40, fbocenter.y-70,
                     fbocenter.x+105-40, fbocenter.y-85,
                     fbocenter.x+90-40, fbocenter.y-75); // ear
        ofSetLineWidth(1.5);
        ofDrawCurve(fbocenter.x-60*3+20,fbocenter.y-10*3,
                    fbocenter.x-r/2-2*3,fbocenter.y+r*cos(60)+8*3,
                    fbocenter.x-43*3, fbocenter.y-20*3,
                    fbocenter.x-100*3,fbocenter.y-10*3); // face
        ofDrawCurve(fbocenter.x,fbocenter.y-24*6,
                    fbocenter.x-45*3-10, fbocenter.y-12*3,
                    fbocenter.x-r/2-2*3,fbocenter.y-r*cos(60)-8*3,
                    fbocenter.x+60*3,fbocenter.y+20*3); // body
        ofFill();
        ofDrawCircle(fbocenter+ofVec2f(-20*3,-18*3), 3*3); // eye
        ofDrawCircle(fbocenter+ofVec2f(-48*3,-18*3), 2*3); // nose
    fboR.end();
    /**************************************************************/
    
    /********************** title & subtitle **********************/
    fboTitle.begin();
        ofSetColor(163,94,71); // background color with alpha
        ofDrawRectangle(0, 0,400,120);
        ofSetColor(stroke);
        walterturncoat.drawString(title, 35, 50);
        ofSetColor(white);
        walterturncoat.drawString(subtitle,45,100);
    fboTitle.end();
    /**************************************************************/
    
    /************************** Mushroom **************************/
    fboMushroom.begin();
        ofFill();
        ofSetColor((int)ofRandom(0,255),(int)ofRandom(0,255),(int)ofRandom(0,255));
        ofDrawBezier(fbocenter.x-100, fbocenter.y-100, fbocenter.x-17, fbocenter.y-200,
                     fbocenter.x+17, fbocenter.y-200, fbocenter.x+100, fbocenter.y-100);
        ofDrawBezier(fbocenter.x-100, fbocenter.y-100, fbocenter.x-50, fbocenter.y+50-100,
                     fbocenter.x+50, fbocenter.y+50-100, fbocenter.x+100, fbocenter.y-100);
    fboMushroom.end();
    /**************************************************************/
    
    /**************************** Boat ****************************/
    fboBoat.begin();
        ofNoFill();
        ofSetColor(stroke);
        float side = 50;
        ofDrawTriangle(fbocenter+side*ofVec2f(-4, -2),
                       fbocenter+side*ofVec2f(-2, 1), fbocenter); // bottom left
        ofDrawTriangle(fbocenter+side*ofVec2f(-2, 1), fbocenter+side*ofVec2f(2, 1),
                       fbocenter+side*ofVec2f(4, -2)); // bottom right
        ofDrawTriangle(fbocenter+0.25*side*ofVec2f(-4, -2),
                       fbocenter+side*ofVec2f(1, -2), fbocenter); // top left
        ofDrawTriangle(fbocenter+0.45*side*ofVec2f(4, -2),
                       fbocenter+side*ofVec2f(1, -2), fbocenter); // top right
    fboBoat.end();
    /**************************************************************/
    
    /**************************** END ******************************
     ***************************************************************
     **************************************************************/
    
    /***************************************************************
     ************************* CREATE SCENES ***********************
     **************************************************************/
    switch (scene) {
        case 0: {
            /************************ Scene 0: OP *************************/
            headingleft.draw(winW-stepX, 0,
                             winW, imgH*winW/imgW);
            headingright.draw(stepX-winW, imgH*winW/imgW,
                              winW,imgH*winW/imgW);
            fboTitle.draw(mid);
            headingleft.draw(winW-stepX, winH-imgH*winW/imgW*2,
                             winW, imgH*winW/imgW);
            headingright.draw(stepX-winW, winH-imgH*winW/imgW,
                              winW,imgH*winW/imgW);
            /**************************************************************/
        }
            break;
            
        case 1: {
            /************************** Scene 1 ***************************/
            bgS1.draw(-200,0, imgW*winH/imgH, winH);
            fboL.draw(cur,200,200);
            backpack.draw(cur+ofVec2f(-250,-175), imgW/2, imgH/2);
            /**************************************************************/
        }
            break;
            
        case 2: {
            /************************** Scene 2 ***************************/
            fboDizzy.draw(mid+ofVec2f(100,100),200,200);
            fboMushroom.draw(mid+ofVec2f(0,50),400,300);
            for (int i=1; i<9; i++){
                fboDizzy.draw(mid+300*ofVec2f(0.4+cos(stepAngle+i*2*PI/8),
                                              0.4+sin(stepAngle+i*2*PI/8)),
                              150,150);
            }
            for (int i=1; i<9; i++){
                ofVec2f mushroomPos(mid+200*ofVec2f(-0.6+cos(i*2*PI/8),
                                                    -0.7+sin(i*2*PI/8)));
                float mushroomDim = 220;
                switch (i) {
                    case 1:
                        mushroom1.draw(mushroomPos,mushroomDim,mushroomDim);
                        break;
                    case 2:
                        mushroom2.draw(mushroomPos,mushroomDim,mushroomDim);
                        break;
                    case 3:
                        mushroom3.draw(mushroomPos,mushroomDim,mushroomDim);
                        break;
                    case 4:
                        mushroom4.draw(mushroomPos,mushroomDim,mushroomDim);
                        break;
                    case 5:
                        mushroom5.draw(mushroomPos,mushroomDim,mushroomDim);
                        break;
                    case 6:
                        mushroom6.draw(mushroomPos,mushroomDim,mushroomDim);
                        break;
                    case 7:
                        mushroom7.draw(mushroomPos,mushroomDim,mushroomDim);
                        break;
                    case 8:
                        mushroom8.draw(mushroomPos,mushroomDim,mushroomDim);
                        break;
                    default:
                        break;
                }
            }
            /**************************************************************/
        }
            break;
            
        case 3: {
            /************************** Scene 3 ***************************/
            bgS3.draw(0,0,imgW*winH/imgH, winH);
//            ofMatrix m(cos(stepY),sin(stepAngle),
//                          -sin(stepAngle),cos(stepAngle));
//            ofPushMatrix();
//            ofRotateZ(stepAngle);
            fboL.draw(cur,100,100);
//            ofPopMatrix();
            /**************************************************************/
        }
            break;
            
        case 4: {
            /************************** Scene 4 ***************************/
            bgS4.draw(0,0,imgW*winH/imgH, winH);
            fboCry.draw(cur, 50+250*stepScale,50+250*stepScale);
            bee.draw(cur-ofVec2f(0,150),20+100*stepScale,20+100*stepScale);
            /**************************************************************/
        }
            break;
            
        case 5: {
            /************************** Scene 5 ***************************/
            sock.draw(winW-400,winH-2*imgH*400/imgW,400,imgH*400/imgW);
            fboL.draw(cur,120*stepScale,120*stepScale);
            /**************************************************************/
        }
            break;
            
        case 6: {
            /************************** Scene 6 ***************************/
            bush.draw(mid-ofVec2f(100,100),imgW*400/imgH,400);
            fboAngry.draw(mid+ofVec2f(300,300),150,150);
            /**************************************************************/
        }
            break;
            
        case 7: {
            /************************** Scene 7 ***************************/
            bgS7.draw(0,0, imgW*winH/imgH, winH);
            fboL.draw(cur,100,100);
            /**************************************************************/
        }
            break;
            
        case 8: {
            /************************** Scene 8 ***************************/
            bgS8.draw(0,50, winW, imgH*winW/imgW);
            // seesaw
            ofPushStyle();
            ofSetColor(67, 52, 27);
            ofFill();
            ofSetLineWidth(8);
            ofDrawLine(mid+ofVec2f(0,100)-cur0, mid+ofVec2f(0,100)+cur0);
            ofDrawTriangle(mid+ofVec2f(0,100), mid+ofVec2f(0,100)+ofVec2f(-2,3)*30,
                           mid+ofVec2f(0,100)+ofVec2f(2,3)*30);
            ofPopStyle();
            // hedgehogs
            fboL.draw(mid-cur0+ofVec2f(20,-50)+ofVec2f(150, 250),100,100);
            if (!flyaway){
                fboR.draw(mid+cur0+ofVec2f(-20,-50)+ofVec2f(150, 250),100,100);
            } else {
                fboR.draw(mid+cur+ofVec2f(-20,-50)+ofVec2f(150, 250),100,100);
            }
            
            /**************************************************************/
        }
            break;
            
        case 9: {
            /************************** Scene 9 ***************************/
            
            fboR.draw(cur+ofVec2f(-20,-40),200,200);
            fboBoat.draw(cur);
            ofPushStyle();
            ofSetColor(125, 185, 222);
            ofDrawRectangle(0, cur.y, winW, winH-cur.y);
            ofPopStyle();
            /**************************************************************/
        }
            break;
            
        case 10: {
            /************************** Scene 10 ***************************/
            fboL.draw(mid+ofVec2f(200,250),150,150);
            mushroom9.draw(mid+ofVec2f(-250,-100), imgW, imgH);
            ofPushStyle();
            ofPushMatrix();
            ofSetColor(stroke);
            string scaleA = "Z";
            ofRectangle bounds = walterturncoat.getStringBoundingBox(scaleA, 0, 0);
            ofTranslate(mid.x + bounds.width/2+100, mid.y + bounds.height / 2, 0);
            ofScale(2.0 + cos(ofGetElapsedTimef()), 2.0 + cos(ofGetElapsedTimef()), 1.0);
            walterturncoat.drawString(scaleA, -bounds.width/2, bounds.height/2 );
            ofPopMatrix();
            ofPopStyle();
            /**************************************************************/
        }
            break;
            
        case 11: {
            /************************** Scene 11 ***************************/
            treehole.draw(0,0, winW, winH);
            for (int i =0; i<10; i++){
                fboNormal.draw(490+55*i,550,55,55);
            }
            /**************************************************************/
        }
            break;
            
        case 12: {
            /************************** THE END ***************************/
            ofPushStyle();
                ofSetColor(stroke);
                walterturncoat.drawString("THE END", mid.x-100, mid.y);
            ofPopStyle();
            /**************************************************************/
        }
            break;
            
        default:
            break;
    }


    ofDrawBitmapString(ofToString(mouse.x)+" ,"+ofToString(mouse.y), mouse.x, mouse.y);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
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
