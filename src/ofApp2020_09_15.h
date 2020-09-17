#pragma once

#include "ofMain.h"

// sin wave oscillator
class prototypeOscillator
{
public:
	void update()
	{
		currentValue = sin(ofGetElapsedTimef());
	}
	float getValue() 
	{ 
		if (nonNegative)
		{
			return (1.f + currentValue) / 2.f;
		}
		else
		{
			return currentValue; 
		}
	}

	float scale = 1.0f;
	float currentValue;
	bool nonNegative = true;
};


class ofApp2020_09_15 : public ofBaseApp {

public:
	void setup() override;
	void update() override;
	void draw() override;

	virtual void keyPressed(ofKeyEventArgs & key) override;
	virtual void keyReleased(ofKeyEventArgs & key) override;


	virtual void mouseDragged(int x, int y, int button) override;

private: // cubes mesh
	ofVboMesh cubeFieldMesh;
	const int cubeFieldDimensions = 100;
	const int cubeSize = 60;
	//ofEasyCam cam;

private: // peak stuff
	int peakX;
	int peakY;
	const int peakFalloff = 30;
	const float peakHeight = 1500.f;

private: // animation variables
	float peakMoveTimer;
	const float peakMoveTimerBaseTarget = 1.0f; // seconds
	prototypeOscillator peakHeightOsc;

private: // debug camera
	glm::vec3 cameraTranslation;
	glm::vec3 cameraRotation; // kept for only one frame currently
	const float cameraSpeed = 5.f;

private: // debug input
	// todo : that's enough keys, maybe change this to a map
	bool isWDown, isADown, isSDown, isDDown,isQDown,isEDown;

};