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

	cameraTranslation.x = -1175.f;
	cameraTranslation.y = -481.f;
	cameraTranslation.z = -3734.f;
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

	const float startingCoordinate = (cubeFieldDimensions * cubeSize) / 2.f;

	for (int y = 0; y < cubeFieldDimensions; ++y)
	{
		for (int x = 0; x < cubeFieldDimensions; ++x)
		{
			const float planeHeight = getPeakFalloff(x, y) * (peakHeight * peakHeightOsc.getValue());

			if (planeHeight <= 25.0f)
			{
				continue;
			}

			glm::vec3 cubeCenter;
			cubeCenter.x = x * cubeSize - startingCoordinate;
			cubeCenter.z = y * cubeSize - startingCoordinate;
			cubeCenter.y = planeHeight;

			makeCube(cubeFieldMesh, cubeCenter, cubeSize);
		}
	}

	for (int y = 0; y < cubeFieldDimensions; ++y)
	{
		for (int x = 0; x < cubeFieldDimensions; ++x)
		{
			const float planeHeight = getPeakFalloff(x, y) * (peakHeight * peakHeightOsc.getValue());

			if (planeHeight <= 25.0f)
			{
				continue;
			}

			glm::vec3 cubeCenter;
			cubeCenter.x = x * cubeSize - startingCoordinate;
			cubeCenter.z = y * cubeSize - startingCoordinate;
			cubeCenter.y = -planeHeight;

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
	if (isQDown)
	{
		cameraTranslation.y -= timeAdjustedCameraSpeed;
	}
	if (isEDown)
	{
		cameraTranslation.y += timeAdjustedCameraSpeed;
	}
}

void ofApp2020_09_15::draw()
{
	//cam.begin();
	ofPushMatrix();
	ofRotateDeg(180);
	ofPushMatrix();
	ofTranslate(cameraTranslation);
	ofRotateXDeg(cameraRotation.x);
	ofRotateYDeg(cameraRotation.y);
	//ofRotateZDeg(cameraRotation.z);

	cubeFieldMesh.draw();
	ofPopMatrix();
	ofPopMatrix();
	//cam.end();

	std::stringstream translationDebugText;
	translationDebugText << "Translation X : " << cameraTranslation.x << " Y : " << cameraTranslation.y << " Z : " << cameraTranslation.z;
	ofDrawBitmapString(translationDebugText.str(), 10, 10);

	std::stringstream rotationDebugText;
	rotationDebugText << "Rotation X : " << cameraRotation.x << " Y : " << cameraRotation.y << " Z : " << cameraRotation.z;
	ofDrawBitmapString(rotationDebugText.str(), 10, 30);

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
	if (key.key == 'q')
	{
		isQDown = true;
	}
	if (key.key == 'e')
	{
		isEDown = true;
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
	if (key.key == 'q')
	{
		isQDown = false;
	}
	if (key.key == 'e')
	{
		isEDown = false;
	}
}

void ofApp2020_09_15::mouseDragged(int x, int y, int button)
{
	cameraRotation.x = -y / 2;
	cameraRotation.y = -x / 2;
}
