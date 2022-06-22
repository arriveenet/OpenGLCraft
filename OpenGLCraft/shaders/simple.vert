#version 460

layout (location = 0) in vec3 inPosition;

uniform mat4 modelViewProjection;

void main()
{
	gl_Position = modelViewProjection * vec4(inPosition, 1.0);
}