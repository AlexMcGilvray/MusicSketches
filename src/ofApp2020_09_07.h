#pragma once

#include "ofMain.h"

class ofApp2020_09_07 : public ofBaseApp {

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
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	void generateInsetTriangle(
		const glm::vec3 first,
		const glm::vec3 second,
		const glm::vec3 third,
		const float lengthThreshold);


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