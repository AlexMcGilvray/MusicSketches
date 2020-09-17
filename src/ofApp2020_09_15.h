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
			return std::abs(currentValue);
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

private: // cubes mesh
	ofMesh cubeFieldMesh;
	const int cubeFieldDimensions = 9;
	const int cubeSize = 100;
	ofEasyCam cam;

private: // peak stuff
	int peakX;
	int peakY;
	const int peakFalloff = 3;
	const float peakHeight = 100.f;

private: // animation variables
	float peakMoveTimer;
	const float peakMoveTimerBaseTarget = 1.0f; // seconds
	prototypeOscillator peakHeightOsc;

};