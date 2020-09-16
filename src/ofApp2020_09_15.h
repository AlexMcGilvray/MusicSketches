#pragma once

#include "ofMain.h"

class ofApp2020_09_15 : public ofBaseApp {

public:
	void setup() override;
	void update() override;
	void draw() override;



private: // cubes mesh
	ofMesh cubeFieldMesh;
	const int cubeFieldDimensions = 10;
	const int cubeSize = 100;

	ofEasyCam cam;
};