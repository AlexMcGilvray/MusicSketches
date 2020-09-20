#include "ofApp2020_09_15.h"

void makeQuad(
	ofMesh & mesh,
	const glm::vec3 topLeft,
	const glm::vec3 topRight,
	const glm::vec3 bottomLeft,
	const glm::vec3 bottomRight,
	const ofColor color)
{
	const int currentIndex = mesh.getNumVertices();

	mesh.addVertex(topLeft);
	mesh.addVertex(topRight);
	mesh.addVertex(bottomLeft);
	mesh.addVertex(bottomRight);

	mesh.addColor(color);
	mesh.addColor(color);
	mesh.addColor(color);
	mesh.addColor(color);

	mesh.addIndex(currentIndex);
	mesh.addIndex(currentIndex + 2);
	mesh.addIndex(currentIndex + 1);

	mesh.addIndex(currentIndex + 2);
	mesh.addIndex(currentIndex + 3);
	mesh.addIndex(currentIndex + 1);
}

void makeCube(ofMesh & mesh, const glm::vec3 cubeCenter, const int cubeSize, ofColor color)
{
	const float cubeHalfSize = cubeSize / 2.f;
	// top/bottom coordinates of the cube
	const float cubeYMin = cubeCenter.y - cubeHalfSize;
	const float cubeYMax = cubeCenter.y + cubeHalfSize;

	const float cubeXMin = cubeCenter.x - cubeHalfSize;
	const float cubeXMax = cubeCenter.x + cubeHalfSize;

	const float cubeZMin = cubeCenter.z - cubeHalfSize;
	const float cubeZMax = cubeCenter.z + cubeHalfSize;

	makeQuad(
		mesh,
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
	planeFieldMesh.setMode(OF_PRIMITIVE_TRIANGLES);

	cameraTranslation.x = -1175.f;
	cameraTranslation.y = -509.f;
	cameraTranslation.z = -3734.f;

	backgroundColor = ofColor::darkGrey;
	foregroundColor = ofColor::grey;

	ofBackground(backgroundColor);

	peakX = ofRandom(0, planeFieldDimensions);
	peakY = ofRandom(0, planeFieldDimensions);
}

void ofApp2020_09_15::updatePeakCoorindates()
{
	const int lastPeakX = peakX;
	const int lastPeakY = peakY;
	bool foundAppropriateNewCoordinate = false;

	while (!foundAppropriateNewCoordinate)
	{
		const float shouldMoveVertically = ofRandom(0.f, 1.f);
		if (shouldMoveVertically > 0.5f)
		{
			const float upDown = ofRandom(0.f, 1.f);
			if (upDown > .5f)
			{
				peakY++;
			}
			else
			{
				peakY--;
			}
		}
		else
		{
			const float leftRight = ofRandom(0.f, 1.f);
			if (leftRight > .5f)
			{
				peakX++;
			}
			else
			{
				peakX--;
			}
		}
		if (peakX >= 0 && peakX < planeFieldDimensions && peakY > 0 && peakY < planeFieldDimensions)
		{
			foundAppropriateNewCoordinate = true;
		}
	}
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

	updatePeakCoorindates();

	planeFieldMesh.clear();

	const float startingCoordinate = (planeFieldDimensions * planeSize) / 2.f;

	// top pyramids
	for (int y = 0; y < planeFieldDimensions; ++y)
	{
		for (int x = 0; x < planeFieldDimensions; ++x)
		{
			const float planeHeight = getPeakFalloff(x, y) * (peakHeight * getOscValue());

			if (planeHeight <= renderingHeightThreshold)
			{
				continue;
			}

			glm::vec3 cubeCenter;
			cubeCenter.x = x * planeSize - startingCoordinate;
			cubeCenter.z = y * planeSize - startingCoordinate;
			cubeCenter.y = planeHeight;

			makeCube(planeFieldMesh, cubeCenter, planeSize, foregroundColor);
		}
	}

	// bottom pyramids
	for (int y = 0; y < planeFieldDimensions; ++y)
	{
		for (int x = 0; x < planeFieldDimensions; ++x)
		{
			const float planeHeight = getPeakFalloff(x, y) * (peakHeight * getOscValue());

			if (planeHeight <= renderingHeightThreshold)
			{
				continue;
			}

			glm::vec3 cubeCenter;
			cubeCenter.x = x * planeSize - startingCoordinate;
			cubeCenter.z = y * planeSize - startingCoordinate;
			cubeCenter.y = -planeHeight;

			makeCube(planeFieldMesh, cubeCenter, planeSize, foregroundColor);
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

	planeFieldMesh.draw();
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
	cameraRotation.x = -y / 2; // todo pull out scaling variables
	cameraRotation.y = -x / 2; // todo pull out scaling variables
}
