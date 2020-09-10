#pragma once

#include "ofMain.h"

class ofApp2020_09_07 : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void generateInsetTriangle(
		const glm::vec3 first,
		const glm::vec3 second,
		const glm::vec3 third,
		const float lengthThreshold);

	// how many function calls deep we are in the recursive generateInsetTriangle function
	int currentRecursionDepth = 0;


	ofColor backgroundColor;
	ofColor foregroundColor;

	ofMesh triangleMesh;

	float triangleEdgeMidPointOffset = 0;

	ofShader shaderBlurX;
	ofShader shaderBlurY;
	ofShader shaderBase;


	ofFbo fboBlurBasePass;

	ofFbo fboBlurOnePass;
	ofFbo fboBlurTwoPass;

	ofImage image;
};