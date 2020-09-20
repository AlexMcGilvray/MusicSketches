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
	float getValue() const
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

	float currentValue;
	bool nonNegative = true;
};

class ofApp2020_09_15 : public ofBaseApp {

public:
	void setup() override;
	void update() override;
	void updatePeakCoorindates();
	void draw() override;

	virtual void keyPressed(ofKeyEventArgs & key) override;
	virtual void keyReleased(ofKeyEventArgs & key) override;

	float getOscValue() const
	{
		return ofMap(peakHeightOsc.getValue(), 0.f, 1.f, oscMin, oscMax);
	}

	virtual void mouseDragged(int x, int y, int button) override;

private: // cubes mesh
	ofVboMesh planeFieldMesh;
	const int planeFieldDimensions = 100;
	const int planeSize = 60;
	// don't render a plane if its lower that this 
	const float renderingHeightThreshold = 50.f; 
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
	const float oscMin = 0.4f;
	const float oscMax = 1.0f;

private: // debug camera
	glm::vec3 cameraTranslation;
	glm::vec3 cameraRotation; // kept for only one frame currently
	const float cameraSpeed = 1.f;

private: // debug input
	// todo : that's enough keys, maybe change this to a map
	bool isWDown, isADown, isSDown, isDDown,isQDown,isEDown;

private: //styling
	ofColor backgroundColor;
	ofColor foregroundColor;
};