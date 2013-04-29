#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    ofSetLogLevel(OF_LOG_VERBOSE);

    sender.setup(HOST, PORT);

    setGUI1(); 

    serial.listDevices();
	vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
		
	serial.setup(5, 9600); //open the 5th in list
	//serial.setup("COM4"); // windows example
	//serial.setup("/dev/tty.usbserial-A4001JEC",9600); // mac osx example
    
    Logo.loadImage("logo.png");
    diagram.loadImage("diagram.png");
    table.loadModel("table3.obj");
    A0.loadModel("arrows/0.obj");
    A45.loadModel("arrows/45.obj");
    A90.loadModel("arrows/90.obj");
    A135.loadModel("arrows/135.obj");
    A180.loadModel("arrows/180.obj");
    A225.loadModel("arrows/225.obj");
    A270.loadModel("arrows/270.obj");
    A225.loadModel("arrows/225.obj");
    A315.loadModel("arrows/315.obj");
    cam.setDistance(1200);
    ofSetBackgroundColor(0, 0, 0);

}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    const char myByte = 225;
    unsigned char buf[5] = {'H','0', '0', '1','\n'};
    serial.writeBytes(&buf[0],5);
    
    ofBackground(60, 60, 60);
    cam.begin();
    table3D();
    cam.end();
    Logo.draw(ofGetWindowWidth() -280, 10);
    diagram.draw(310, 35, 150, 150);
}
//--------------------------------------------------------------
void testApp::table3D(){

    ofSetColor(0, 255, 230);
    ofPushMatrix();
    ofTranslate(table.getPosition().x, table.getPosition().y-500,0);
    ofRotate(0, 0, 1, 0);
    ofTranslate(-table.getPosition().x, -table.getPosition().y, 0);
    table.setScale(0.8, -0.8, 0.8);
    table.drawWireframe();
    ofSetColor(0, 0, 0);
    A0.setScale(0.52, -0.52, 0.52);
    A0.drawWireframe();
    A45.setScale(0.32, -0.32, 0.32);
    A45.drawWireframe();
    A90.setScale(0.62, -0.52, 0.52);
    A90.drawWireframe();
    A135.setScale(0.32, -0.32, 0.32);
    A135.drawWireframe();
    A180.setScale(0.52, -0.52, 0.52);
    A180.drawWireframe();
    A225.setScale(0.32, -0.32, 0.32);
    A225.drawWireframe();
    A270.setScale(0.62, -0.52, 0.52);
    A270.drawWireframe();
    A315.setScale(0.32, -0.32, 0.32);
    A315.drawWireframe();
    
    ofPopMatrix();
}
//------------------
void testApp::guiEvent(ofxUIEventArgs &e)
{
}
//---------------
void testApp::setGUI1()
{	
	float dim = 16; 
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING; 
    float length = 255-xInit; 
	
    vector<string> names; 
	names.push_back("FORWARD");
	names.push_back("BACKWARD");
	names.push_back("LEFT");
	names.push_back("RIGHT");
	names.push_back("45Degree");
	names.push_back("135Degree");
	names.push_back("225Degree");
    names.push_back("315Degree");
   
    vector<string> tableModes; 
    tableModes.push_back("Evasive");
    tableModes.push_back("Curious");
	
	gui1 = new ofxUICanvas(0, 0, length+xInit, ofGetHeight()); 
	gui1->addWidgetDown(new ofxUILabel("TableControl 001", OFX_UI_FONT_LARGE)); 

    gui1->addSpacer(length-xInit, 2);

    gui1->addSpacer(length-xInit, 2);
	gui1->addRadio("REMOTE CONTROL", names, OFX_UI_ORIENTATION_VERTICAL, dim, dim); 
    gui1->addToggle( "ENABLE/DISABLE", false, 75, 75);

    gui1->addSpacer(length-xInit, 2);
    gui1->addWidgetDown(new ofxUILabel("ZOOMORPHISE", OFX_UI_FONT_MEDIUM)); 
    gui1->addToggle( "ENABLE/DISABLE", false, dim, dim);
    gui1->addWidgetDown(new ofxUILabel("MODE", OFX_UI_FONT_SMALL)); 
    gui1->addRadio("TableModes", tableModes, OFX_UI_ORIENTATION_VERTICAL, dim, dim); 
    
    
    gui1->addSpacer(length-xInit, 2);
	gui1->addWidgetDown(new ofxUILabel("RECORD", OFX_UI_FONT_MEDIUM)); 
	gui1->addToggle( "RECORD TOGGLE", false, dim, dim);
    gui1->addButton( "LOAD RECORDING", false, dim, dim);
    gui1->addWidgetDown(new ofxUILabel("Currently loaded:", OFX_UI_FONT_SMALL)); 
    gui1->addButton( "PLAY", false, dim, dim);

    
    gui1->addSpacer(length-xInit, 2);
	gui1->addWidgetDown(new ofxUILabel("TOGGLES", OFX_UI_FONT_MEDIUM)); 
	gui1->addToggle( "DRAW_GRID", false, dim, dim);
        
	ofAddListener(gui1->newGUIEvent,this,&testApp::guiEvent);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if (key == 'f'){
        ofToggleFullscreen();
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}