#include "ofApp2020_09_15.h"

void makeQuad(ofMesh & cubeFieldMesh, const glm::vec3 topLeft, const glm::vec3 topRight, const glm::vec3 bottomLeft, const glm::vec3 bottomRight, const ofColor color)
{
	cubeFieldMesh.addVertex(topLeft);
	cubeFieldMesh.addVertex(topRight);
	cubeFieldMesh.addVertex(bottomLeft);
	cubeFieldMesh.addVertex(bottomRight);

	cubeFieldMesh.addColor(color);
	cubeFieldMesh.addColor(color);
	cubeFieldMesh.addColor(color);
	cubeFieldMesh.addColor(color);

	const int currentIndex = cubeFieldMesh.getNumVertices();

	cubeFieldMesh.addIndex(currentIndex);
	cubeFieldMesh.addIndex(currentIndex + 2);
	cubeFieldMesh.addIndex(currentIndex + 1);

	cubeFieldMesh.addIndex(currentIndex + 2);
	cubeFieldMesh.addIndex(currentIndex + 3);
	cubeFieldMesh.addIndex(currentIndex + 1);
}

void makeCube(ofMesh & cubeFieldMesh, const glm::vec3 cubeCenter, const int cubeSize)
{
	const float cubeHalfSize = cubeSize / 2.f;
	// top/bottom coordinates of the cube
	const float cubeYMin = cubeCenter.y - cubeHalfSize;
	const float cubeYMax = cubeCenter.y + cubeHalfSize;

	const float cubeXMin = cubeCenter.x - cubeHalfSize;
	const float cubeXMax = cubeCenter.x + cubeHalfSize;

	const float cubeZMin = cubeCenter.z - cubeHalfSize;
	const float cubeZMax = cubeCenter.z + cubeHalfSize;
	
	static bool colorSwitcher = true;

	ofColor color = colorSwitcher  ? ofColor::grey : ofColor::darkGrey;
	colorSwitcher = !colorSwitcher;

	makeQuad(
		cubeFieldMesh, 
		glm::vec3(cubeXMin, cubeYMax, cubeZMin), 
		glm::vec3(cubeXMax, cubeYMax, cubeZMin), 
		glm::vec3(cubeXMin, cubeYMax, cubeZMax), 
		glm::vec3(cubeXMax, cubeYMax, cubeZMax), 
		color);
}

void ofApp2020_09_15::setup()
{
	ofEnableDepthTest();
	ofSeedRandom();
	cubeFieldMesh.setMode(OF_PRIMITIVE_TRIANGLES);
	for (int y = 0; y < cubeFieldDimensions; ++y)
	{
		for (int x = 0; x < cubeFieldDimensions; ++x)
		{
			glm::vec3 cubeCenter;
			cubeCenter.x = x * cubeSize;
			cubeCenter.z = y * cubeSize;
			cubeCenter.y = 0.f;
				
			makeCube(cubeFieldMesh,cubeCenter,cubeSize);
		}
	}
}

void ofApp2020_09_15::update()
{
}


void ofApp2020_09_15::draw()
{
	cam.begin();
	cubeFieldMesh.draw();
	cam.end();
}
