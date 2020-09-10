#include "ofApp.h"
bool started = false;

//--------------------------------------------------------------
void ofApp2::setup() {
	ofSetFrameRate(60);
	ofSetWindowTitle("2020-09-04");

	meshes.resize(meshCount);
	for (auto && mesh : meshes)
	{
		mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
	}
	startTime = ofGetCurrentTime().getAsSeconds();
	started = true;// disable this and enable the key check in the input function further down to make capturing with OBS easier
	
	player.load("../DR0000_0338_mastered.mp3");
	player.play();
}

//--------------------------------------------------------------
void ofApp2::update() {
	
	if (!started)
	{
		return;
	}

	currentTimeThroughSong = ofGetCurrentTime().getAsSeconds() - startTime;

	for (auto && mesh : meshes)
	{
		mesh.clear();
	}

	auto makeSquare = [this](ofMesh & mesh, float sizeMultiplier)
	{
		const float sizeTest = currentTimeThroughSong * 3;
		const int vertexBufferSize = mesh.getNumVertices();
		const float newSize = sizeTest + BaseSquareSize * sizeMultiplier;
		glm::vec3 sq1(-newSize, -newSize, 0);
		glm::vec3 sq2(newSize, -newSize, 0);
		glm::vec3 sq3(-newSize, newSize, 0);
		glm::vec3 sq4(newSize, newSize, 0); 
		mesh.addVertex(sq1);
		mesh.addVertex(sq2);
		mesh.addVertex(sq3);
		mesh.addVertex(sq4);

		for (int i = 0; i < mesh.getNumVertices(); i++)
		{
			mesh.addColor(ofColor(1, 1, 1));
		}

		mesh.addIndex(vertexBufferSize + 0);
		mesh.addIndex(vertexBufferSize + 1);

		mesh.addIndex(vertexBufferSize + 1);
		mesh.addIndex(vertexBufferSize + 3);

		mesh.addIndex(vertexBufferSize + 0);
		mesh.addIndex(vertexBufferSize + 2);

		mesh.addIndex(vertexBufferSize + 2);
		mesh.addIndex(vertexBufferSize + 3);
	};

	auto curTime = ofGetCurrentTime(); 
	squareSizeMultiplier = (float)sin(curTime.getAsSeconds());
	float currentSizeModifier = (5.f * squareSizeMultiplier) / (10 - ofClamp((10 * getNormalizedSongPosition()),1.0f,10.f));

	sizeModifier = (squareSizeMultiplier / 2) * 3;

	for (auto & mesh : meshes)
	{
		makeSquare(mesh, currentSizeModifier);
		currentSizeModifier += .1f;
		//currentSizeModifier = ofClamp(currentSizeModifier, 1.f,5.f);
	}
	
	auto lerpVal = getNormalizedSongPosition();
	ofBackground(backgroundColorInitial.lerp(backgroundColorFinal, lerpVal));

}


//--------------------------------------------------------------
void ofApp2::draw() {


	if (!started)
	{
		return;
	}

	ofPushMatrix();
	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
	currentRotation += rotationSpeed;

	for (auto && mesh : meshes)
	{
		currentRotation += rotationSpeed;
		if (currentRotation > 360.f)
		{
			currentRotation = 0.f;
		}
		ofRotateDeg(currentRotation);
		mesh.drawWireframe();
	}
	ofPopMatrix();
	ofTranslate(0,0);

	//ofSetColor(ofColor::black);
	//ofDrawBitmapString("squareSizeMultiplier: " + ofToString(squareSizeMultiplier), 10, 10);
}

float ofApp2::getNormalizedSongPosition() const
{
	  return ofClamp(currentTimeThroughSong / SongLength, 0.f, 1.f); 
}