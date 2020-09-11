#version 150

// these are for the programmable pipeline system
uniform mat4 modelViewProjectionMatrix;
uniform mat4 textureMatrix;

in vec4 position;
in vec2 texcoord;
in vec4 normal;
in vec4 color;

out vec2 texCoordVarying;
out vec4 vColorOut; 

void main()
{ 

    texCoordVarying = texcoord;
	gl_Position = modelViewProjectionMatrix * position;
	vColorOut = color;
}
