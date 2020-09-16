#include "ofMain.h"
#include "ofApp.h"
#include "ofApp2020_09_07.h"
//========================================================================
int main( ){
	//ofSetupOpenGL(1920,1080, ofWindowMode::OF_WINDOW);			// <-------- setup the GL context
	//ofGLWindowSettings settings;
	//settings.setGLVersion(3, 2);
	//ofCreateWindow(settings);

	ofGLWindowSettings settings;
	settings.setGLVersion(3, 2);
	settings.setSize(1920, 1080);
	settings.windowMode = ofWindowMode::OF_FULLSCREEN;
	ofCreateWindow(settings);


	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	//ofRunApp(new ofApp2());
	ofRunApp(new ofApp2020_09_07());
	//
}
