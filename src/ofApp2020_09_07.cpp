#include "ofApp.h"

//--------------------------------------------------------------
void ofApp2020_09_07::setup() {
	ofSetFrameRate(60);
	ofSetWindowTitle("2020-09-07 - Cubes rising");

	shaderBlurX.load("ofApp2020_09_07/shaderBlurX");
	shaderBlurY.load("ofApp2020_09_07/shaderBlurY");
	shaderBase.load("ofApp2020_09_07/shaderBasePass");

	fboBlurOnePass.allocate(ofGetWidth(), ofGetHeight());
	fboBlurTwoPass.allocate(ofGetWidth(), ofGetHeight());
	fboBlurBasePass.allocate(ofGetWidth(), ofGetHeight());

	foregroundColor = ofColor::orange;
	backgroundColor = ofColor::black;

	ofBackground(backgroundColor);

	triangleMesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}


void ofApp2020_09_07::generateInsetTriangle(const glm::vec3 first, const  glm::vec3 second, const  glm::vec3 third, const float lengthThreshold)
{
	if (
		glm::length(first - second) < lengthThreshold || 
		glm::length(second - third) < lengthThreshold ||
		glm::length(first - third) < lengthThreshold )
	{
		return;
	}

	const int CurrentIndex = triangleMesh.getNumVertices();

	triangleMesh.addVertex(first);
	triangleMesh.addVertex(second);
	triangleMesh.addVertex(third);

	triangleMesh.addColor(foregroundColor);
	triangleMesh.addColor(foregroundColor);
	triangleMesh.addColor(foregroundColor);

	triangleMesh.addIndex(CurrentIndex + 0);
	triangleMesh.addIndex(CurrentIndex + 1);

	triangleMesh.addIndex(CurrentIndex + 1);
	triangleMesh.addIndex(CurrentIndex + 2);

	triangleMesh.addIndex(CurrentIndex + 2);
	triangleMesh.addIndex(CurrentIndex + 0);

	const glm::vec3 nextFirst = glm::mix(first, second, 0.5f + triangleEdgeMidPointOffset);
	const glm::vec3 nextSecond = glm::mix(second, third, 0.5f + triangleEdgeMidPointOffset);
	const glm::vec3 nextThird = glm::mix(third, first, 0.5f + triangleEdgeMidPointOffset);
	generateInsetTriangle(nextFirst, nextSecond, nextThird, lengthThreshold);
}


//--------------------------------------------------------------
void ofApp2020_09_07::update() {

	triangleMesh.clear();
	auto curTime = ofGetCurrentTime();
	triangleEdgeMidPointOffset = sin(curTime.getAsSeconds())  / 2.25f;

	const float Size = 350.f;

	glm::vec3 firstVertex(-Size, -Size, 0.f);
	glm::vec3 secondVertex(0.f, glm::length(firstVertex), 0.f);
	glm::vec3 thirdVertex(Size, -Size, 0.f);

	const float lengthThreshhold = 10.f;

	generateInsetTriangle(firstVertex, secondVertex, thirdVertex, lengthThreshhold);
}

//--------------------------------------------------------------
void ofApp2020_09_07::draw() {
	auto curTime = ofGetCurrentTime();
	const float blur = sin(curTime.getAsSeconds()) / 2.f;

	fboBlurBasePass.begin();
	shaderBase.begin();
	ofClear(backgroundColor);
	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
	triangleMesh.draw();
	shaderBase.end();
	fboBlurBasePass.end();


	fboBlurOnePass.begin();
	shaderBlurX.begin();
	shaderBlurX.setUniform1f("blurAmnt", blur);
	ofClear(backgroundColor);
	fboBlurBasePass.draw(0, 0);
	shaderBlurX.end();
	fboBlurOnePass.end();

	fboBlurTwoPass.begin();
	shaderBlurY.begin();
	shaderBlurY.setUniform1f("blurAmnt", blur);
	ofClear(backgroundColor);

	fboBlurOnePass.draw(0, 0);

	shaderBlurY.end();
	fboBlurTwoPass.end();

	fboBlurTwoPass.draw(0, 0);
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
