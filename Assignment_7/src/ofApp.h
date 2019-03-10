#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
//        void buttonPressed();
//        void exit();
        ofxPanel gui;
        ofxToggle showcry;
        ofxToggle showangry;
        ofxToggle showconfuse;
        ofxToggle showseesaw;
        ofxFloatSlider volumn;
        ofxColorSlider color;
        ofxVec2Slider center;
        ofxIntSlider degree;
    
        ofSoundPlayer cry, fire, confusion, seesaw;
		
};
