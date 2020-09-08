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

	const float Size = 300.f;

	testLines.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

	glm::vec3 firstVertex(-Size, -Size, 0.f);
	glm::vec3 secondVertex(0.f, glm::length(firstVertex), 0.f);
	glm::vec3 thirdVertex(Size, -Size, 0.f);

	const float lengthThreshhold = 5.f;

	generateInsetTriangle(firstVertex, secondVertex, thirdVertex, lengthThreshhold);

	
}


void ofApp2020_09_07::generateInsetTriangle(const glm::vec3 first, const  glm::vec3 second, const  glm::vec3 third, const float lengthThreshold)
{
	const float TriangleEdgeLength = glm::length(first - second);
	if (TriangleEdgeLength < lengthThreshold)
	{
		return;
	}

	const int CurrentIndex = testLines.getNumVertices();

	testLines.addVertex(first);
	testLines.addVertex(second);
	testLines.addVertex(third);

	testLines.addColor(foregroundColor);
	testLines.addColor(foregroundColor);
	testLines.addColor(foregroundColor);

	testLines.addIndex(CurrentIndex + 0);
	testLines.addIndex(CurrentIndex + 1);

	testLines.addIndex(CurrentIndex + 1);
	testLines.addIndex(CurrentIndex + 2);

	testLines.addIndex(CurrentIndex + 2);
	testLines.addIndex(CurrentIndex + 0);

	const glm::vec3 nextFirst = glm::mix(first, second, 0.5f);
	const glm::vec3 nextSecond = glm::mix(second, third, 0.5f);
	const glm::vec3 nextThird = glm::mix(third, first, 0.5f);

	generateInsetTriangle(nextFirst, nextSecond, nextThird, lengthThreshold);
}


//--------------------------------------------------------------
void ofApp2020_09_07::update() {


	//currentRotation += 0.31f;
}


//--------------------------------------------------------------
void ofApp2020_09_07::draw() {
	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
	//ofRotateDeg(currentRotation);
	testLines.draw();

}

//--------------------------------------------------------------
void ofApp2020_09_07::keyPressed(int key) {

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
