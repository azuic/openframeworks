#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    gui.setup();
    gui.add(num.setup("Number of Triangles", 1, 1, 20));
}

//--------------------------------------------------------------
void ofApp::update(){
    
}
ofPoint tip;
float length;
void drawTri(ofPoint origin, int numTriangles){
    ofPushMatrix();
    ofPushStyle();
    ofTranslate(origin);
    ofSetColor(255, 177, 27+numTriangles,100-numTriangles);
    ofFill();
    tip = ofPoint(origin.x+200/numTriangles,origin.y);
    ofDrawTriangle(tip, origin-ofPoint(0,100/numTriangles), origin+ofPoint(0,100/numTriangles));
    ofRotateZDeg(360/numTriangles);
    if(--numTriangles>1){
        drawTri(tip,numTriangles);
    }
    ofPopStyle();
    ofPopMatrix();
}
//--------------------------------------------------------------
void ofApp::draw(){
    gui.draw();
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2,ofGetHeight()/2);
    for (int i=0; i<=360; i+=360/num) {
        ofPushMatrix();
        ofPushStyle();
        ofRotateZDeg(i);
        drawTri(ofPoint(0,0),num);
        ofPopStyle();
        ofPopMatrix();
    }
    ofPopMatrix();
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
