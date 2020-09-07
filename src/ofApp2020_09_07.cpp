#include "ofApp.h"

//--------------------------------------------------------------
void ofApp2020_09_07::setup() {
	ofSetFrameRate(60);
	ofSetWindowTitle("2020-09-07 - Cubes rising");

	/*foregroundColor.r = 190;
	foregroundColor.g = 190;
	foregroundColor.b = 240;
	foregroundColor.a = 0;

	backgroundColor.r = 240;
	backgroundColor.g = 240;
	backgroundColor.b = 240;
	backgroundColor.a = 0;
*/


	foregroundColor = ofColor::orange;
	backgroundColor = ofColor::black;

	ofBackground(backgroundColor);

	const float Size = 400.f;

	testLines.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

	testLines.addVertex(glm::vec3(-Size, -Size, 0.f));
	testLines.addVertex(glm::vec3(0.f, Size, 0.f));
	testLines.addVertex(glm::vec3(Size, -Size, 0.f));

	testLines.addColor(foregroundColor);
	testLines.addColor(foregroundColor);
	testLines.addColor(foregroundColor);

	testLines.addIndex(0);
	testLines.addIndex(1);

	testLines.addIndex(1);
	testLines.addIndex(2);

	testLines.addIndex(2);
	testLines.addIndex(0);

	
}

//--------------------------------------------------------------
void ofApp2020_09_07::update() {



}


//--------------------------------------------------------------
void ofApp2020_09_07::draw() {
	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	testLines.draw();

}

//--------------------------------------------------------------
void ofApp2020_09_07::keyPressed(int key) {

	//if (key == 'z')
	//{
	//	startTime = ofGetCurrentTime().getAsSeconds();
	//	started = true;
	//}
}

//--------------------------------------------------------------
void ofApp2020_09_07::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp2020_09_07::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp2020_09_07::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp2020_09_07::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp2020_09_07::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp2020_09_07::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp2020_09_07::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp2020_09_07::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp2020_09_07::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp2020_09_07::dragEvent(ofDragInfo dragInfo) {

}
