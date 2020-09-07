#pragma once

#include "ofMain.h"


class ofApp2 : public ofBaseApp {

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

	ofSoundPlayer player;

	//ofMesh mesh;
	const int meshCount = 20;
	std::vector<ofMesh> meshes;

	// update
	float squareSizeMultiplier;
	// this is added and subtracted from the base gradually over the course of the run
	float sizeModifier = 0.f;
	const float BaseSquareSize = 50;

	// draw
	float currentRotation = 0;
	float rotationSpeed = 0.003f;

	// background lerp
	ofColor backgroundColorInitial;
	ofColor backgroundColorFinal;
	ofColor currentBackground;

	// tracking time/position through song
	double currentTimeThroughSong;
	const double SongLength = 114.f;
	double startTime;
	float getNormalizedSongPosition() const;
};

