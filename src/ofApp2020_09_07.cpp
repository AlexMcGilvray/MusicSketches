#include "ofApp2020_09_07.h"

//--------------------------------------------------------------
void ofApp2020_09_07::setup() {
	ofSetFrameRate(60);
	ofSetWindowTitle("2020-09-07 - Cubes rising");
	ofSeedRandom();

	shaderBlurX.load("ofApp2020_09_07/shaderBlurX");
	shaderBlurY.load("ofApp2020_09_07/shaderBlurY");
	shaderBase.load("ofApp2020_09_07/shaderBasePass");
	fboBlurOnePass.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
	fboBlurTwoPass.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
	fboBlurBasePass.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);

	yLine = ofGetWidth() / 2;

	foregroundColor = ofColor::orange;
	backgroundColor = ofColor::black;

	ofBackground(backgroundColor);

	generateLines();

	triangleMesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
	lineMesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}


void ofApp2020_09_07::generateInsetTriangle(const glm::vec3 first, const  glm::vec3 second, const  glm::vec3 third, const float lengthThreshold)
{
	if (
		glm::length(first - second) < lengthThreshold || 
		glm::length(second - third) < lengthThreshold ||
		glm::length(first - third) < lengthThreshold )
	{
		return;
	}

	const int CurrentIndex = triangleMesh.getNumVertices();

	triangleMesh.addVertex(first);
	triangleMesh.addVertex(second);
	triangleMesh.addVertex(third);

	// the more depth we have the more we darken
	ofColor modifiedForegroundColor = foregroundColor;

	const float foregroundBrightness = foregroundColor.getBrightness();
	const float modifiedBrightness = ofClamp(foregroundBrightness - currentRecursionDepth * 10, 25.f, foregroundBrightness);
	modifiedForegroundColor.setBrightness(modifiedBrightness);

	triangleMesh.addColor(foregroundColor);
	triangleMesh.addColor(foregroundColor);
	triangleMesh.addColor(foregroundColor);

	triangleMesh.addIndex(CurrentIndex + 0);
	triangleMesh.addIndex(CurrentIndex + 1);

	triangleMesh.addIndex(CurrentIndex + 1);
	triangleMesh.addIndex(CurrentIndex + 2);

	triangleMesh.addIndex(CurrentIndex + 2);
	triangleMesh.addIndex(CurrentIndex + 0);

	const glm::vec3 nextFirst = glm::mix(first, second, 0.5f + triangleEdgeMidPointOffset);
	const glm::vec3 nextSecond = glm::mix(second, third, 0.5f + triangleEdgeMidPointOffset);
	const glm::vec3 nextThird = glm::mix(third, first, 0.5f + triangleEdgeMidPointOffset);

	currentRecursionDepth++;
	generateInsetTriangle(nextFirst, nextSecond, nextThird, lengthThreshold);
	currentRecursionDepth--;
}

//--------------------------------------------------------------
void ofApp2020_09_07::update() {

	triangleMesh.clear();
	auto curTime = ofGetCurrentTime();
	triangleEdgeMidPointOffset = sin(curTime.getAsSeconds() / 3.f)  / 2.25f;

	const float Size = 350.f;

	glm::vec3 firstVertex(-Size, -Size, 0.f);
	glm::vec3 secondVertex(0.f, glm::length(firstVertex), 0.f);
	glm::vec3 thirdVertex(Size, -Size, 0.f);

	const float lengthThreshhold = 10.f;

	generateInsetTriangle(firstVertex, secondVertex, thirdVertex, lengthThreshhold);
	updateLines();
}

void ofApp2020_09_07::updateLines()
{
	lineMesh.clear();
	const float viewportWidth = ofGetWidth();
	for (auto & line : lines)
	{
		const float direction = line.isMovingRight ? 1.f : -1.f;
		const float velocity = direction * line.speed;
		line.xPos = ofClamp(line.xPos + velocity, 0.f, viewportWidth);
		const float epsilon = 0.25f;
		if (line.xPos < epsilon)
		{
			line.isMovingRight = true;
		}
		else if (line.xPos > viewportWidth - epsilon)
		{
			line.isMovingRight = false;
		}

	}
	for (auto & line : lines)
	{
		glm::vec3 lineTop, lineBottom;
		lineTop.x = line.xPos;
		lineTop.y = 0;
		lineBottom.x = line.xPos;
		lineBottom.y = ofGetHeight();
		const int currentIndex = lineMesh.getNumVertices();

		lineMesh.addVertex(lineTop);
		lineMesh.addVertex(lineBottom);

		const float normalizedXCoord = line.xPos / viewportWidth;
		const float lineAlpha = sin(normalizedXCoord * PI);
		ofColor lineColorBottom = line.color;
		lineColorBottom.a = ofClamp(255.f - ((lineAlpha * lineAlpha) * 255.f), 0.15f * 255.f, 0.35f * 255.f);
		lineColorBottom.a += ofRandomf() * 10.f;

		ofColor lineColorTop = lineColorBottom;
		lineColorTop.a = ofClamp(lineColorTop.a - 150, 0, 255);

		lineMesh.addColor(lineColorTop);
		lineMesh.addColor(lineColorBottom);

		lineMesh.addIndex(currentIndex);
		lineMesh.addIndex(currentIndex + 1);
	}
}


//--------------------------------------------------------------
void ofApp2020_09_07::draw() {
	auto curTime = ofGetCurrentTime();
	const float blur = ((sin(curTime.getAsSeconds()) + 1.f)) ;
	
	// base pass
	fboBlurBasePass.begin();
	shaderBase.begin();
	shaderBase.setUniform1f("yLine", yLine);
	ofClear(backgroundColor);
	lineMesh.draw();

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
	triangleMesh.draw();
	shaderBase.end();
	fboBlurBasePass.end();

	// horizontal blur pass
	fboBlurOnePass.begin();
	shaderBlurX.begin();
	shaderBlurX.setUniform1f("blurAmnt", blur);
	ofClear(backgroundColor);
	fboBlurBasePass.draw(0, 0);
	shaderBlurX.end();
	fboBlurOnePass.end();

	// vertical blur pass
	fboBlurTwoPass.begin();
	shaderBlurY.begin();
	shaderBlurY.setUniform1f("blurAmnt", blur);
	ofClear(backgroundColor);
	fboBlurOnePass.draw(0, 0);
	shaderBlurY.end();
	fboBlurTwoPass.end();

	fboBlurTwoPass.draw(0, 0);


}


void ofApp2020_09_07::generateLines()
{
	bool shouldMoveRight = true;
	for (int i = 0; i < NumLines; ++i)
	{
		verticalLine line;
		line.xPos = ofGetWidth() * ofRandom(0.f, 1.f);
		line.speed = ofMap(ofRandom(0.f, 1.f), 0.f, 1.f, MaxSpeed / 15.f, MaxSpeed,true);
		line.color = ofColor::blue;
		line.isMovingRight = shouldMoveRight;
		shouldMoveRight = !shouldMoveRight;
		lines.push_back(line);
	}
}
