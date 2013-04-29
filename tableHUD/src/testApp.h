#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "ofxAssimpModelLoader.h"
#include "ofxOsc.h"

#define HOST "localhost"
#define PORT 12345

class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        void setGUI1(); 
        void table3D();
        void stringBuild();
        ofxUICanvas *gui1;   
        void guiEvent(ofxUIEventArgs &e);
    
        ofSerial	serial;


        ofImage Logo;
        ofImage diagram;
    
        ofxAssimpModelLoader table;
        ofxAssimpModelLoader A0;
        ofxAssimpModelLoader A45;
        ofxAssimpModelLoader A90;
        ofxAssimpModelLoader A135;
        ofxAssimpModelLoader A180;
        ofxAssimpModelLoader A225;
        ofxAssimpModelLoader A270;
        ofxAssimpModelLoader A315;

    ofTrueTypeFont font;

    ofxOscSender sender;

        ofEasyCam cam; // add mouse controls for camera movement

    int x;
    int y;
    int z;
    
    bool remoteOnOff;
    string str;
};
