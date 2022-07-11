#version 460

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTexCoord;

uniform mat4 modelViewProjection;

out vec2 texCoord;

void main()
{
	texCoord = inTexCoord;

	gl_Position = modelViewProjection * vec4(inPosition, 1.0);
}