#include "ofApp.h"
#include <cmath>
//--------------------------------------------------------------
//----------------------  Global Variables ---------------------
//--------------------------------------------------------------
ofTrueTypeFont tradewindsTitle,tradewinds;
const float velRad = 0;
const float life=2.0;
const float friction=0.05;

float windspeedNY, windgustNY, windspeedAA, windgustAA,
      windspeedSD, windgustSD, windspeedNT, windgustNT;
int windbearingNY, windbearingAA, windbearingSD, windbearingNT;

int w,h;
float scaleNY, scaleAA, scaleSD, scaleNT;
ofVec2f ny,aa,sd,nt;

ofxJSONElement jsonNY, jsonAA, jsonSD, jsonNT;
string urlNY = "https://api.darksky.net/forecast/9039c38c69ca76396eec16512cae1a10/47.5696,10.7004";
string urlAA = "https://api.darksky.net/forecast/9039c38c69ca76396eec16512cae1a10/42.2808,-83.7430";
string urlSD = "https://api.darksky.net/forecast/9039c38c69ca76396eec16512cae1a10/32.7157,-117.1611";
string urlNT = "https://api.darksky.net/forecast/9039c38c69ca76396eec16512cae1a10/31.9802,120.8943";
bool nyGET = jsonNY.open(urlNY);
bool aaGET = jsonAA.open(urlAA);
bool sdGET = jsonSD.open(urlSD);
bool ntGET = jsonNT.open(urlNT);
//--------------------------------------------------------------
//----------------------  Particle  ----------------------------
//--------------------------------------------------------------
Particle::Particle() {
    live = false;
}

//--------------------------------------------------------------
ofPoint randomPointInCircle( float maxRad ){
    ofPoint pnt;
    float rad = ofRandom( 0, maxRad );
    float angle = ofRandom( 0, M_TWO_PI );
    pnt.x = cos( angle ) * rad;
    pnt.y = sin( angle ) * rad;
    return pnt;
}

//--------------------------------------------------------------
void Particle::setup(ofPoint _eCenter, float _eRad, ofColor _color, float _speed, float _gust, int _bearing) {
    eRad = _eRad;
    eCenter = _eCenter;
    pos = eCenter + randomPointInCircle( eRad );
    vel = randomPointInCircle( velRad );
    time = 0;
    lifeTime = life;
    live = true;
    color = _color;
    windspeed = _speed;
    windgust = _gust;
    windbearing = _bearing;
}

//--------------------------------------------------------------
void Particle::update( float dt ){

    if ( live ) {
        //Rotate vel
        vel.rotate( 0, 0, windbearing * dt );
        
        ofPoint acc;         //Acceleration
        ofPoint delta = pos - eCenter;
        float len = delta.length();
        if ( ofInRange( len, 0, eRad ) ) {
            delta.normalize();
            
            //Attraction/repulsion force
            acc += delta * 100*windspeed;
            
            //Spinning force
            acc.x += -delta.y * 100*windgust;
            acc.y += delta.x * 100*windgust;
        }
        vel += acc * dt;            //Euler method
        vel *= ( 1 - friction );  //Friction
        
        //Update pos
        pos += vel * dt;    //Euler method
        
        //Update time and check if particle should die
        time += dt;
        if ( time >= lifeTime ) {
            live = false;   //Particle is now considered as died
        }
    }
}

//--------------------------------------------------------------
void Particle::draw(){
    if ( live ) {
        //Compute size
        float size = ofMap(fabs(time - lifeTime/2), 0, lifeTime/2, 1,0.1 );
        
        //Compute color
        float hue = ofMap( time, 0, lifeTime, 128, 255 );
        color.setHue( hue );
        ofSetColor( color );
        
        ofDrawCircle( pos, size );  //Draw particle
    }
}
//--------------------------------------------------------------
//--------------------------  Wind  ----------------------------
//--------------------------------------------------------------
Wind::Wind(){
}
void Wind::setup(ofPoint _center, float _rad, ofColor _color, float _speed, float _gust, int _bearing){
    color = _color;
    speed = _speed;
    gust = _gust;
    bearing = _bearing;
    time0 = ofGetElapsedTimef();
    center = _center;
    rad = _rad;
//    fbo.allocate( 2*rad, 2*rad, GL_RGB32F_ARB );
//    bornCount=0;      //Integrated number of particles to born
}

void Wind::update(){
    //Compute dt
    float time = ofGetElapsedTimef();
    float dt = ofClamp( time - time0, 0, 0.1 );
    time0 = time;
    
    //Delete inactive particles
    int i=0;
    while (i < p.size()) {
        if ( !p[i].live ) {
            p.erase( p.begin() + i );
        }
        else {
            i++;
        }
    }
    
    //Born new particles
    bornCount += dt * bornRate;      //Update bornCount value
    if ( bornCount >= 1 ) {          //It's time to born particle(s)
        int bornN = int( bornCount );//How many born
        bornCount -= bornN;          //Correct bornCount value
        for (int i=0; i<bornN; i++) {
            Particle newP;
            newP.setup(center,rad,color,speed,gust,bearing);            //Start a new particle
            p.push_back( newP );     //Add this particle to array
        }
    }
    
    //Update the particles
    for (int i=0; i<p.size(); i++) {
        p[i].update( dt );
    }
}

void Wind::draw(){
    //Draw the particles
    ofFill();
    for (int i=0; i<p.size(); i++) {
        p[i].draw();
    }
}


//--------------------------------------------------------------
//----------------------  ofApp  -----------------------------
//--------------------------------------------------------------
void ofApp::setup(){
    windspeedNY = jsonNY["currently"]["windSpeed"].asFloat();
    windgustNY = jsonNY["currently"]["windGust"].asFloat();
    windbearingNY = jsonNY["currently"]["windBearing"].asInt();
    windspeedAA = jsonAA["currently"]["windSpeed"].asFloat();
    windgustAA = jsonAA["currently"]["windGust"].asFloat();
    windbearingAA = jsonAA["currently"]["windBearing"].asInt();
    windspeedSD = jsonSD["currently"]["windSpeed"].asFloat();
    windgustSD = jsonSD["currently"]["windGust"].asFloat();
    windbearingSD = jsonSD["currently"]["windBearing"].asInt();
    windspeedNT = jsonNT["currently"]["windSpeed"].asFloat();
    windgustNT = jsonNT["currently"]["windGust"].asFloat();
    windbearingNT = jsonNT["currently"]["windBearing"].asInt();
//    cout<<windspeedNY<<endl;
    ofSetFrameRate( 60 );    //Set screen frame rate
    w = ofGetWidth();
    h = ofGetHeight();
    
    scaleNY = std::sqrt(486/28.77);
    scaleAA = 1; //28.77
    scaleSD =  std::sqrt(372.4/28.77);
    scaleNT =  std::sqrt(320/28.77);
    
    ny = ofPoint(ofMap(10.7004,-115,125,150,w-125),ofMap(47.5696,50,30,125,h-75));
    aa = ofPoint(ofMap(-83.7430,-115,125,150,w-125),ofMap(42.2808,50,30,125,h-75));
    sd = ofPoint(ofMap(-117.1611,-115,125,150,w-125),ofMap(32.7157,50,30,125,h-75));
    nt = ofPoint(ofMap(120.8943,-115,125,150,w-125),ofMap(31.9802,50,30,125,h-75));
    
    // NY: 486
    newyork.setup(ny,30*scaleNY,ofColor(232,48,21), windspeedNY, windgustNY, windbearingNY);
    annarbor.setup(aa,30*scaleAA,ofColor(255,196,8), windspeedAA, windgustAA, windbearingAA);
    sandiego.setup(sd,30*scaleSD,ofColor(129,199,212), windspeedSD, windgustSD, windbearingSD);
    nantong.setup(nt,30*scaleNT,ofColor(34,125,81), windspeedSD, windgustSD, windbearingSD);
    
    tradewindsTitle.load("TradeWinds-Regular.ttf", 24);
    tradewinds.load("TradeWinds-Regular.ttf", 12);
}

//--------------------------------------------------------------
void ofApp::update(){
    newyork.update();
    annarbor.update();
    sandiego.update();
    nantong.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground( 255, 255, 255 );
//
    newyork.draw();
    annarbor.draw();
    sandiego.draw();
    nantong.draw();
    
    ofPushStyle();
    ofSetColor(80);
    tradewindsTitle.drawString("Wind Donuts", w/2-20, h/2);
    tradewinds.drawString("New York", ny.x,ny.y);
    tradewinds.drawString("Ann Arbor", aa.x,aa.y);
    tradewinds.drawString("San Diego", sd.x,sd.y);
    tradewinds.drawString("Nantong", nt.x, nt.y);
    ofPopStyle();

}


//--------------------------------------------------------------
//----------------------  ofApp again  -----------------------
//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}
//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
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
