#include "ofApp2020_09_15.h"

void makeQuad(
	ofMesh & cubeFieldMesh, 
	const glm::vec3 topLeft, 
	const glm::vec3 topRight, 
	const glm::vec3 bottomLeft, 
	const glm::vec3 bottomRight, 
	const ofColor color)
{
	const int currentIndex = cubeFieldMesh.getNumVertices();

	cubeFieldMesh.addVertex(topLeft);
	cubeFieldMesh.addVertex(topRight);
	cubeFieldMesh.addVertex(bottomLeft);
	cubeFieldMesh.addVertex(bottomRight);

	cubeFieldMesh.addColor(color);
	cubeFieldMesh.addColor(color);
	cubeFieldMesh.addColor(color);
	cubeFieldMesh.addColor(color);

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
 
	ofColor color = ofColor::grey;

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


}

void ofApp2020_09_15::update()
{
	peakHeightOsc.update();

	auto getPeakFalloff = [this](int x, int y) -> float
	{
		const int distanceX = std::abs(peakX - x);
		const int distanceY = std::abs(peakY - y);
		const int furthestDistance = std::max(distanceX, distanceY);
		if (furthestDistance > peakFalloff)
		{
			return 0.f;
		}
		else
		{
			const float normalizedDistance = 1.f - furthestDistance / (float)peakFalloff;
			return normalizedDistance;
		}
	};

	peakX = ofRandom(0,cubeFieldDimensions);
	peakY = ofRandom(0, cubeFieldDimensions);

	cubeFieldMesh.clear();

	for (int y = 0; y < cubeFieldDimensions; ++y)
	{
		for (int x = 0; x < cubeFieldDimensions; ++x)
		{
			const float tempHeightModifer = getPeakFalloff(x, y) * (peakHeight * peakHeightOsc.getValue());

			glm::vec3 cubeCenter;
			cubeCenter.x = x * cubeSize;
			cubeCenter.z = y * cubeSize;
			cubeCenter.y = tempHeightModifer;

			makeCube(cubeFieldMesh, cubeCenter, cubeSize);
		}
	}

	const float timeAdjustedCameraSpeed = cameraSpeed * ofGetElapsedTimef();
	if (isWDown)
	{
		cameraTranslation.z += timeAdjustedCameraSpeed;
	}
	if (isADown)
	{
		cameraTranslation.x -= timeAdjustedCameraSpeed;
	}
	if (isSDown)
	{
		cameraTranslation.z -= timeAdjustedCameraSpeed;
	}
	if (isDDown)
	{
		cameraTranslation.x += timeAdjustedCameraSpeed;
	}

}

void ofApp2020_09_15::draw()
{
	//cam.begin();
	ofPushMatrix();
	ofRotateDeg(180);
	ofTranslate(cameraTranslation);
	cubeFieldMesh.draw();
	ofPopMatrix();
	//cam.end();

	std::stringstream translationDebugText;
	translationDebugText << "Translation X : " << cameraTranslation.x << " Y : " << cameraTranslation.y << " Z : " << cameraTranslation.z;
	ofDrawBitmapString(translationDebugText.str(), 10, 10);

}

void ofApp2020_09_15::keyPressed(ofKeyEventArgs & key)
{
	if (key.key == 'w')
	{
		isWDown = true;
	}
	if (key.key == 'a')
	{
		isADown = true;
	}
	if (key.key == 's')
	{
		isSDown = true;
	}
	if (key.key == 'd')
	{
		isDDown = true;
	}
}

void ofApp2020_09_15::keyReleased(ofKeyEventArgs & key)
{
	if (key.key == 'w')
	{
		isWDown = false;
	}
	if (key.key == 'a')
	{
		isADown = false;
	}
	if (key.key == 's')
	{
		isSDown = false;
	}
	if (key.key == 'd')
	{
		isDDown = false;
	}
}
