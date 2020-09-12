#pragma once

#include "ofMain.h"

struct verticalLine
{
	float xPos;
	float speed;
	bool isMovingRight;
	ofColor color;
};

class ofApp2020_09_07 : public ofBaseApp {

public:
	void setup();
	void update();
	void updateLines();
	void draw();
	void generateLines();

	void generateInsetTriangle(
		const glm::vec3 first,
		const glm::vec3 second,
		const glm::vec3 third,
		const float lengthThreshold);

	// how many function calls deep we are in the recursive 
	// generateInsetTriangle function
	int currentRecursionDepth = 0;

	ofColor backgroundColor;
	ofColor foregroundColor;

	ofMesh triangleMesh;
	ofMesh lineMesh;

	float triangleEdgeMidPointOffset = 0;

	ofShader shaderBlurX;
	ofShader shaderBlurY;
	ofShader shaderBase;

	ofFbo fboBlurBasePass;
	ofFbo fboBlurOnePass;
	ofFbo fboBlurTwoPass;

	//ofImage image;
	const float MaxSpeed = 2.f;
	const int NumLines = 2255;
	std::vector<verticalLine> lines;

	// base pass uniforms
	float yLine;


	ofSoundPlayer player;
};