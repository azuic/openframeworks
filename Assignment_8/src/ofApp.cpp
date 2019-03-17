#include "ofApp.h"
#include <stdio.h>      /* puts, printf */
#include <time.h>       /* time_t, struct tm, time, gmtime */
#define CET (+1)
using namespace std;
const int framerate = 60;
time_t currentT;
time_t sunriseT, sunsetT;
time_t rawtime;
struct tm * ptm;
struct tm * ptm1;
struct tm * ptm2;
struct tm * ptm3;
int currentMon, currentD, currentH, currentMin;
int sunriseH, sunriseM, sunsetH, sunsetM;
int hr,dd;

//--------------------------------------------------------------
void ofApp::setup(){
    string url = "https://api.darksky.net/forecast/c70210b918c80126aee8cb34ee2fdbda/47.5696,10.7004";
    bool parsingSuccessful = json.open(url);
    if (parsingSuccessful)
    {
        
        currentT = json["currently"]["time"].asInt();
        cout<<"Epoch time: ";
        cout<<currentT<<endl;
        time ( &currentT );
        ptm1 = gmtime ( &currentT );
        currentMon = ptm1->tm_mon+1; // tm_month range: 0-11
        currentD = ptm1->tm_mday;
        currentH = (ptm1->tm_hour+CET)%24;
        currentMin = ptm1->tm_min;
        sunriseT = json["daily"]["data"][0]["sunriseTime"].asInt();
        sunsetT = json["daily"]["data"][0]["sunsetTime"].asInt();
        ptm2 = gmtime ( &sunriseT );
        sunriseH = (ptm2->tm_hour+CET)%24;
        sunriseM = ptm2->tm_min;
        ptm3 = gmtime ( &sunsetT );
        sunsetH = (ptm3->tm_hour+CET)%24;
        sunsetM = ptm3->tm_min;

        puts("Current date and time: ");
        printf("Füssen, Germany:  %02d/%02d %02d:%02d\n",
               currentMon,currentD,currentH,currentMin);
        puts("Sunrise and sunset time: ");
        printf("Sunrise: %02d:%02d\n",
               sunriseH,sunriseM);
        printf("Sunset: %02d:%02d\n",
               sunsetH,sunsetM);
        puts("Weather: ");
        printf("Temperature: %.2f Fahrenheit\n", json["currently"]["temperature"].asFloat());
        printf("Cloud cover: %.2f\n", json["currently"]["cloudCover"].asFloat());
        printf("Humidity: %.2f", json["currently"]["humidity"].asFloat());
//        cout<<json["currently"]<<endl;
//        cout<<json["daily"]["data"][0]<<endl;
//        for (Json::ArrayIndex i = 0; i < 24; i++){
//            rawtime = json["hourly"]["data"][i]["time"].asInt();
//            ptm = gmtime ( &rawtime );
//            dd = ptm->tm_mday;
//            hr = (ptm->tm_hour+CET)%24;
//            printf("Date: %02d; Hour: %02d\n",dd,hr);
//        }

//        ofLogNotice("ofApp::setup") << json.getRawString(true);
    } else {
        ofLogNotice("ofApp::setup") << "Failed to parse JSON.";
    }
    ofSetFrameRate(framerate);
    ofBackground(255, 255, 255);
    gui.setup();
    gui.add(cloud.setup("Cloud Cover", json["currently"]["cloudCover"].asFloat(), 0, 1));
    gui.add(temperature.setup("Temperature", json["currently"]["temperature"].asFloat(), json["daily"]["data"][0]["temperatureLow"].asFloat(), json["daily"]["data"][0]["temperatureHigh"].asFloat()));
    gui.add(hour.setup("Hour of day", currentH, 0, 23));
    gui.add(current.setup("Realtime", true));
    gui.add(sunrise.setup("Sunrise", false));
    gui.add(sunset.setup("Sunset", false));

}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofFill();
    ofSetColor(0, 191, 255, 100*cloud);
    ofDrawRectangle(0, 0, ofGetWindowWidth()/24*(hour+1), ofGetWindowHeight());
//    ofSetColor(255, 255, 255,100);
//    ofDrawRectangle(0, 0, ofGetWindowWidth()/24*(hour+1), ofGetWindowHeight());
    ofSetColor(255, 69, 0);
    ofDrawRectangle(0, ofGetWindowHeight()/2-10,
                    ofGetWindowWidth()/24*(currentH+currentMin/60), temperature);
    ofSetColor(255, 165, 0);
    ofSetCircleResolution(100);
    if (sunrise){
        ofDrawCircle(ofGetWindowWidth()/24*(sunriseH+sunriseM/60), ofGetWindowWidth()/2-120, 50);
    }
    ofSetColor(255, 215, 0);
    if (sunset){
        ofDrawCircle(ofGetWindowWidth()/24*(sunsetH+sunsetM/60), ofGetWindowWidth()/2-120, 50);
    }
    gui.draw();
//    for (Json::ArrayIndex i = 0; i < json["response"]["docs"].size(); ++i)
//    {
//        string title  = json["response"]["docs"][i]["headline"]["main"].asString();
//        string author = json["response"]["docs"][i]["byline"]["original"].asString();
//        string date   = json["response"]["docs"][i]["pub_date"].asString();
//        string text   = title + " - " + author + " (" + date + ")";
//        ofDrawBitmapString(text, 20, i * 24 + 40);
//    }
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
