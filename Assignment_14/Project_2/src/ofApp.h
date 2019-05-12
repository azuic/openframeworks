#pragma once

#include "ofMain.h"
#include "ofxJSON.h"
//Particle class
class Particle {
public:
    Particle();                //Class constructor
    void setup(ofPoint _eCenter, float _eRad, ofColor _color, float _speed, float _gust, int _bearing);              //Start particle
    void update( float dt );   //Recalculate physics
    void draw();               //Draw particle
    
    ofPoint pos;               //Position
    ofPoint vel;               //Velocity
    float time;                //Time of living
    float lifeTime;            //Allowed lifetime
    bool live;                 //Is particle live
    ofColor color;
    float windspeed;
    float windgust;
    int windbearing;
    ofPoint eCenter;
    float eRad;
};

//Particle class
class Wind {
public:
    void setup(ofPoint _center, float _rad, ofColor _color, float _speed, float _gust, int _bearing);
    void update();
    void draw();
    
    float bornCount=0;
    float history = 0.2;       //Control parameter for trails
    float time0;          //Time value for computing dt
    float bornRate = 800;       //Particles born rate per second
    
//    const float velRad = 0;
//    const float life=2.0;
//    const float friction=0.05;
    ofColor color;
    float speed;
    float gust;
    int bearing;
    ofPoint center;
    float rad;
    vector<Particle> p;      //Particles
//    ofFbo fbo;
    Wind();
};

//openFrameworks' class
class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
//    ofxJSONElement jsonNY, jsonAA, jsonSD, jsonNT;
    Wind newyork, annarbor, sandiego, nantong;
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
};
