#include "ofApp.h"

ofSoundPlayer boop;
float midX, midY;
float midX1, midX2, midY1, midY2;
float l1, l2, l3;
float dist;
int dir;
float counter;
//ofPolyline straightSegmentPolyline;
//ofPolyline curvedSegmentPolyline;


//--------------------------------------------------------------
void ofApp::setup(){
    // load every sound you will need here
    ofSetFrameRate(60);
    boop.loadSound("boopBoop.wav");
    midX = ofGetWidth()/2;
    midY = ofGetHeight()/2;
//    straightSegmentPolyline.addVertex(100, 100);  // Add a new point: (100, 100)
//    straightSegmentPolyline.addVertex(150, 150);  // Add a new point: (150, 150)
//    straightSegmentPolyline.addVertex(200, 100);  // etc...
//    straightSegmentPolyline.addVertex(250, 150);
//    straightSegmentPolyline.addVertex(300, 100);
//
//    curvedSegmentPolyline.curveTo(350, 100);  // These curves are Catmull-Rom splines
//    curvedSegmentPolyline.curveTo(350, 100);  // Necessary Duplicate for Control Point
//    curvedSegmentPolyline.curveTo(400, 150);
//    curvedSegmentPolyline.curveTo(450, 100);
//    curvedSegmentPolyline.curveTo(500, 150);
//    curvedSegmentPolyline.curveTo(550, 100);
//    curvedSegmentPolyline.curveTo(550, 100);  // Necessary Duplicate for Control Point
    dir = 1;
    dist = 200;
    l1 = 100;
    l2 = 50;
    l3 = 30;
//    midX1 = midX-dist/2;
//    midX2 = midX+dist/2;
//    midY1 = midY;
//    midY2 = midY;
//    closedShapePolyline1.addVertex(midX1, midY1+l1);
//    closedShapePolyline1.addVertex(midX1+l2/2, midY1+l3/2);
//    closedShapePolyline1.addVertex(midX1+l1, midY1);
//    closedShapePolyline1.addVertex(midX1+l2/2, midY1-l3/2);
//    closedShapePolyline1.addVertex(midX1, midY1-l1);
//    closedShapePolyline1.addVertex(midX1-l2/2, midY1-l3/2);
//    closedShapePolyline1.addVertex(midX1-l1, midY1);
//    closedShapePolyline1.addVertex(midX1-l2/2, midY1+l3/2);
//    closedShapePolyline1.close();  // Connect first and last vertices
//
//    closedShapePolyline2.addVertex(midX2, midY2+l1);
//    closedShapePolyline2.addVertex(midX2+l2/2, midY2+l3/2);
//    closedShapePolyline2.addVertex(midX2+l1, midY2);
//    closedShapePolyline2.addVertex(midX2+l2/2, midY2-l3/2);
//    closedShapePolyline2.addVertex(midX2, midY2-l1);
//    closedShapePolyline2.addVertex(midX2-l2/2, midY2-l3/2);
//    closedShapePolyline2.addVertex(midX2-l1, midY2);
//    closedShapePolyline2.addVertex(midX2-l2/2, midY2+l3/2);
//    closedShapePolyline2.close();  // Connect first and last vertices
    
}

int x = 100, y = 100;
int inc = 1;  // our increment will change!

//--------------------------------------------------------------
void ofApp::update(){
    
    // CLASSWORK: Comment out the "if" below after you run it.
    // Use ofGetWidth(), *=, and a logical "or" to make the ball
    // change direction and play the sound when you hit a side.
    
    // How would you speed the ball up?

    counter = ofMap(dist,l1*2,ofGetWidth()-l1*2,1,30);
    dist += counter*dir;
//    if ((dist + l1*2) >= ofGetWidth()){
//        dist -= counter;
//    } else if (dist <= 200){
    
//    }
    if ((dist + l1*2) >= ofGetWidth() || dist <= 200) {
        dir *= -1;
    }
    
//    dist += counter*dir;
    if (dist<=200) {  // every 500th update, play sound
        boop.play();
    }
    
//    x += inc; // add inc to x
}


//ofPolyline line;
//--------------------------------------------------------------
void ofApp::draw(){
//    ofSetColor(255,0,255);
//    ofDrawCircle(x,y,50);
//
//    line.addVertex(ofVec3f(100,100,0));
//    line.addVertex(ofVec3f(50,200,0));
//    line.addVertex(ofVec3f(150,200,0));
//    line.close();
//    line.draw();
    
    ofBackground(0);
    ofSetLineWidth(2.0);  // Line widths apply to polylines
//    ofSetColor(255,100,0);
//    straightSegmentPolyline.draw();  // This is how we draw polylines
//    curvedSegmentPolyline.draw();  // Nice and easy, right?
    
    midX1 = midX-dist/2;
    midX2 = midX+dist/2;
    midY1 = midY;
    midY2 = midY;
    ofPolyline closedShapePolyline1, closedShapePolyline2;
    
    closedShapePolyline1.addVertex(midX1, midY1+l1);
    closedShapePolyline1.addVertex(midX1+l2/2, midY1+l3/2);
    closedShapePolyline1.addVertex(midX1+l1, midY1);
    closedShapePolyline1.addVertex(midX1+l2/2, midY1-l3/2);
    closedShapePolyline1.addVertex(midX1, midY1-l1);
    closedShapePolyline1.addVertex(midX1-l2/2, midY1-l3/2);
    closedShapePolyline1.addVertex(midX1-l1, midY1);
    closedShapePolyline1.addVertex(midX1-l2/2, midY1+l3/2);
    closedShapePolyline1.close();  // Connect first and last vertices
    
    closedShapePolyline2.addVertex(midX2, midY2+l1);
    closedShapePolyline2.addVertex(midX2+l2/2, midY2+l3/2);
    closedShapePolyline2.addVertex(midX2+l1, midY2);
    closedShapePolyline2.addVertex(midX2+l2/2, midY2-l3/2);
    closedShapePolyline2.addVertex(midX2, midY2-l1);
    closedShapePolyline2.addVertex(midX2-l2/2, midY2-l3/2);
    closedShapePolyline2.addVertex(midX2-l1, midY2);
    closedShapePolyline2.addVertex(midX2-l2/2, midY2+l3/2);
    closedShapePolyline2.close();  // Connect first and last vertices
    ofSetColor(255,100,0);
    closedShapePolyline1.draw();
    ofSetColor(255,255,255);
    closedShapePolyline2.draw();
}

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
