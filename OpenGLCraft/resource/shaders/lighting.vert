#version 460

layout (location = 0) in vec3 inNormal;
layout (location = 1) in vec3 inPosition;

uniform mat4 modelViewProjection;
uniform mat4 modelViewMatrix;
uniform mat4 viewMatrix;
uniform vec4 lightPosition;
uniform vec4 Ld;
uniform vec4 Ls;
uniform vec4 La;
uniform vec4 Kd;
uniform vec4 Ks;
uniform vec4 Ka;
uniform float shininess;

out vec4 color;
out vec2 texCoord;

void main()
{
	vec4 ambient = Ka * La;

	vec3 N = normalize(mat3(modelViewMatrix) * inNormal);
	vec3 L = normalize(mat3(viewMatrix) * lightPosition.xyz);
	float diffuseLighting = max(dot(L, N), 0);
	vec4 diffuse = Kd * diffuseLighting * Ld;

	vec3 P = (modelViewMatrix * vec4(inPosition, 1.0)).xyz;
	vec3 V = normalize(-P);
	vec3 H = normalize(L + V);
	float specularLighting = pow(max(dot(H, N), 0), shininess);
	if (diffuseLighting <= 0.0) {
		specularLighting = 0.0;
	}
	vec4 specular = Ks * specularLighting * Ls;

	gl_FrontColor = ambient + diffuse + specular;
	gl_Position = modelViewProjection * vec4(inPosition, 1.0);
}