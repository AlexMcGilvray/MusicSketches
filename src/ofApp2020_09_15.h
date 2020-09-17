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

private: // cubes mesh
	ofMesh cubeFieldMesh;
	const int cubeFieldDimensions = 100;
	const int cubeSize = 20;
	//ofEasyCam cam;

private: // peak stuff
	int peakX;
	int peakY;
	const int peakFalloff = 30;
	const float peakHeight = 1000.f;

private: // animation variables
	float peakMoveTimer;
	const float peakMoveTimerBaseTarget = 1.0f; // seconds
	prototypeOscillator peakHeightOsc;

private: // debug camera
	glm::vec3 cameraTranslation;
	const float cameraSpeed = 20.f;

private: // debug input
	bool isWDown, isADown, isSDown, isDDown;

};