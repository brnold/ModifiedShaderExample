#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	oculusRift.baseCamera = &cam; //attach to your camera
    //opens the device, an Oculus must be plugged in 
    //as it uses the params returned from the head set to configure 
    //the resolution settings
    oculusRift.setup();

	
	ofSetVerticalSync(true);
	
	// this uses depth information for occlusion
	// rather than always drawing things on top of each other
	ofEnableDepthTest();


	ofEnableNormalizedTexCoords();

	ofLogo.loadImage("of.png");
	
	// draw the ofBox outlines with some weight
	ofSetLineWidth(10);
	
	// this sets the camera's distance from the object
	cam.setDistance(1000);
	
}	

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

	

	//move your camera wherever you'd like, this becomes the base
    //position of the view
	cam.begin();
    //cam.end();
    //now render using oculus flow
   
   
    
    oculusRift.beginLeftEye();
    drawScene();

    oculusRift.endLeftEye();

    oculusRift.beginRightEye();
   
    drawScene();  

    oculusRift.endRightEye();

    cam.end();

    //pushes the render texture to the viewer
    oculusRift.draw();
}




void ofApp::drawScene(){
	
	//ofBackground(0, 0, 30);
	
	float movementSpeed = .1;
	float cloudSize = ofGetWidth() / 2;
	float maxBoxSize = 100;
	float spacing = 1;
	int boxCount = 100;
	
	//cam.begin();
	
	for(int i = 0; i < boxCount; i++) {
		ofPushMatrix();
		
		float t = (ofGetElapsedTimef() + i * spacing) * movementSpeed;
		ofVec3f pos(
			ofSignedNoise(t, 0, 0),
			ofSignedNoise(0, t, 0),
			ofSignedNoise(0, 0, t));
		
		float boxSize = maxBoxSize * ofNoise(pos.x, pos.y, pos.z);
		
		pos *= cloudSize;
		ofTranslate(pos);
		ofRotateX(pos.x);
		ofRotateY(pos.y);
		ofRotateZ(pos.z);
		
		ofLogo.bind();
		ofFill();
		ofSetColor(255);
		ofDrawBox(boxSize);
		ofLogo.unbind();
		
		ofNoFill();
		ofSetColor(ofColor::fromHsb(sinf(t) * 128 + 128, 255, 255));
		ofDrawBox(boxSize * 1.1f);
		
		ofPopMatrix();
	}
	
	//cam.end();
}

void ofApp::drawInteractionArea(){
	ofRectangle vp = ofGetCurrentViewport();
	float r = MIN(vp.width, vp.height) * 0.5f;
	float x = vp.width * 0.5f;
	float y = vp.height * 0.5f;
	
	ofPushStyle();
	ofSetLineWidth(3);
	ofSetColor(255, 255, 0);
	ofNoFill();
	glDepthMask(false);
	ofCircle(x, y, r);
	glDepthMask(true);
	ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){ 
		switch(key) {
		case 'C':
		case 'c':
			if(cam.getMouseInputEnabled()) cam.disableMouseInput();
			else cam.enableMouseInput();
			break;
			
		case 'F':
		case 'f':
			ofToggleFullscreen();
			break;
		case 'H':
		case 'h':
			bShowHelp ^=true;
			break;
	}
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

