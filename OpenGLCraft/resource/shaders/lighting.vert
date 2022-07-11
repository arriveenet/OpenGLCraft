#version 460

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;

uniform mat4 modelViewProjection;
uniform mat4 modelViewMatrix;
uniform mat4 viewMatrix;
uniform vec4 lightPosition;

out vec3 position;
out vec3 normal;
out vec3 light;


void main()
{
	normal = normalize(mat3(modelViewMatrix) * inNormal);
	position = (modelViewMatrix * vec4(inPosition, 1.0)).xyz;
	light = (viewMatrix * lightPosition).xyz;

	gl_Position = modelViewProjection * vec4(inPosition, 1.0);
}