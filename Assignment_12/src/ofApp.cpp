#include "ofApp.h"
#include <cmath>
//--------------------------------------------------------------
//----------------------  Params -------------------------------
//--------------------------------------------------------------

float windspeed, windgust;
int windbearing;
float currenteRad;
float windspeedNY, windgustNY, windspeedAA, windgustAA,
      windspeedSD, windgustSD, windspeedNT, windgustNT;
int windbearingNY, windbearingAA, windbearingSD, windbearingNT;
float currentlon,currentlat;
int city;
string url;
bool parseSuccessful;
ofColor color;
int w,h;
float scaleNY, scaleAA, scaleSD, scaleNT;
ofVec2f ny,aa,sd,nt;
float fboSize = 1000;
ofPoint eCenter(fboSize/2, fboSize/2);
const float eRad = 300;
const float velRad = 0;
const float life=2.0;
const float friction=0.05;
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
void Particle::setup() {
    pos = eCenter + randomPointInCircle( eRad );
    vel = randomPointInCircle( velRad );
    time = 0;
    lifeTime = life;
    live = true;
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
        float size = ofMap(fabs(time - lifeTime/2), 0, lifeTime/2, 3, 1 );
        
        //Compute color
        float hue = ofMap( time, 0, lifeTime, 128, 255 );
        color.setHue( hue );
        ofSetColor( color );
        
        ofDrawCircle( pos, size );  //Draw particle
    }
}

//--------------------------------------------------------------
//----------------------  ofApp  -----------------------------
//--------------------------------------------------------------
void ofApp::setup(){
    string urlNY = "https://api.darksky.net/forecast/0ee7fd4cd92e1e605f638d376e1818d9/47.5696,10.7004";
    string urlAA = "https://api.darksky.net/forecast/0ee7fd4cd92e1e605f638d376e1818d9/42.2808,-83.7430";
    string urlSD = "https://api.darksky.net/forecast/0ee7fd4cd92e1e605f638d376e1818d9/32.7157,-117.1611";
    string urlNT = "https://api.darksky.net/forecast/0ee7fd4cd92e1e605f638d376e1818d9/31.9802,120.8943";
    bool nyGET = jsonNY.open(urlNY);
    bool aaGET = jsonAA.open(urlAA);
    bool sdGET = jsonSD.open(urlSD);
    bool ntGET = jsonNT.open(urlNT);
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
    
    ofSetFrameRate( 60 );    //Set screen frame rate
    w = ofGetWidth();
    h = ofGetHeight();
    
    scaleNY = std::sqrt(486/28.77);
    scaleAA = 1; //28.77
    scaleSD =  std::sqrt(372.4/28.77);
    scaleNT =  std::sqrt(320/28.77);
    
    ny = ofVec2f(ofMap(10.7004,-115,125,50,w-200),ofMap(47.5696,50,30,50,h-150));
    aa = ofVec2f(ofMap(-83.7430,-115,125,50,w-200),ofMap(42.2808,50,30,50,h-150));
    sd = ofVec2f(ofMap(-117.1611,-115,125,50,w-200),ofMap(32.7157,50,30,50,h-150));
    nt = ofVec2f(ofMap(120.8943,-115,125,50,w-200),ofMap(31.9802,50,30,50,h-150));
    
    //Allocate drawing buffer
    fbo.allocate( fboSize, fboSize, GL_RGB32F_ARB );
    fboNY.allocate( fboSize, fboSize, GL_RGB32F_ARB );
    fboAA.allocate( fboSize, fboSize, GL_RGB32F_ARB );
    fboSD.allocate( fboSize, fboSize, GL_RGB32F_ARB );
    fboNT.allocate( fboSize, fboSize, GL_RGB32F_ARB );
    //Set up parameters
    setup();        //Global parameters
    history = 0.2;
    bornRate = 800;
    
    bornCount = 0;
    time0 = ofGetElapsedTimef();
    
}

//--------------------------------------------------------------
void ofApp::update(){
//    if (city < 1){
//        currenteRad = 180; //486
//        windspeed = windspeedNY;
//        windgust = windgustNY;
//        windbearing = windbearingNY;
//        color=ofColor(232,48,21);
//    }
//    else if (city < 2){
//        currenteRad = 28.77/486*270;
//        windspeed = windspeedAA;
//        windgust = windgustAA;
//        windbearing = windbearingAA;
//        color=ofColor(255,196,8);
//    }
//    else if (city < 3){
//        currenteRad = 372.4/486*180;
//        windspeed = windspeedSD;
//        windgust = windgustSD;
//        windbearing = windbearingSD;
//        color=ofColor(129,199,212);
//    }
//    else {
//        currenteRad = 320/486*180;
//        windspeed = windspeedNT;
//        windgust = windgustNT;
//        windbearing = windbearingNT;
//        color=ofColor(34,125,81);
//    }
//    switch (city) {
//        case 1:
//        {
//            currenteRad = 180; //486
//            windspeed = windspeedNY;
//            windgust = windgustNY;
//            windbearing = windbearingNY;
//            color=ofColor(232,48,21);
//        }
//            break;
//        case 2:
//        {
//            currenteRad = 28.77/486*270;
//            windspeed = windspeedAA;
//            windgust = windgustAA;
//            windbearing = windbearingAA;
//            color=ofColor(255,196,8);
//        }
//            break;
//        case 3:
//        {
//            currenteRad = 372.4/486*180;
//            windspeed = windspeedSD;
//            windgust = windgustSD;
//            windbearing = windbearingSD;
//            color=ofColor(129,199,212);
//        }
//            break;
//        case 4:
//        {
//            currenteRad = 320/486*180;
//            windspeed = windspeedNT;
//            windgust = windgustNT;
//            windbearing = windbearingNT;
//            color=ofColor(34,125,81);
//        }
//            break;
//        default:
//            break;
//    }
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
            newP.setup();            //Start a new particle
            p.push_back( newP );     //Add this particle to array
        }
    }
    
    //Update the particles
    for (int i=0; i<p.size(); i++) {
        p[i].update( dt );
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground( 255, 255, 255 );  //Set white background
    
    //Drawing particle buffer
    fbo.begin();
    ofEnableAlphaBlending(); //Enable transparency to slightly clear a buffer
    float alpha = (1-history) * 255;
    ofSetColor( 255, 255, 255, alpha );
    ofFill();
    ofDrawCircle( fboSize/2,  fboSize/2,  fboSize/2,  fboSize/2 );
    ofDisableAlphaBlending();        //Disable transparency
    //Draw the particles
    ofFill();
    for (int i=0; i<p.size(); i++) {
        p[i].draw();
    }
    fbo.end();
    
    fboNY.begin();
    currenteRad = 180; //486
    windspeed = windspeedNY;
    windgust = windgustNY;
    windbearing = windbearingNY;
    color=ofColor(232,48,21);
//    city = 1;
    fbo.draw(0,0);
    fboNY.end();
    
    fboAA.begin();
    currenteRad = 28.77/486*270;
    windspeed = windspeedAA;
    windgust = windgustAA;
    windbearing = windbearingAA;
    color=ofColor(255,196,8);
//    city = 2;
    fbo.draw(0,0);
    fboAA.end();
    
    fboSD.begin();
    currenteRad = 372.4/486*180;
    windspeed = windspeedSD;
    windgust = windgustSD;
    windbearing = windbearingSD;
    color=ofColor(129,199,212);
//    city = 3;
    fbo.draw(0,0);
    fboSD.end();
    
    fboNT.begin();
    currenteRad = 320/486*180;
    windspeed = windspeedNT;
    windgust = windgustNT;
    windbearing = windbearingNT;
    color=ofColor(34,125,81);
//    city = 4;
    fbo.draw(0,0);
    fboNT.end();
    
    //2. Draw buffer on the screen
    ofSetColor( 255, 255, 255 );
    
    fboNY.draw(ny,fboSize/20*scaleNY,fboSize/20*scaleNY);
    fboAA.draw(aa,fboSize/20*scaleAA,fboSize/20*scaleAA);
    fboSD.draw(sd,fboSize/20*scaleSD,fboSize/20*scaleSD);
    fboNT.draw(nt,fboSize/20*scaleNT,fboSize/20*scaleNT);
    

    



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
