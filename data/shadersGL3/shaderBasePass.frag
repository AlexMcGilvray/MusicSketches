#version 150

uniform sampler2DRect tex0;
uniform float blurAmnt;
uniform float yLine;

in vec2 texCoordVarying;
in vec4 vColorOut;
out vec4 outputColor;

// Gaussian weights from http://dev.theomader.com/gaussian-kernel-calculator/

void main()
{
    vec4 color = vColorOut;
	if (gl_FragCoord.x > yLine)
	{
		color = vec4(1);
	}
	
    outputColor = color;
}
