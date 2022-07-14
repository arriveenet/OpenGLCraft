#version 460

in vec4 color;

layout (location = 0) out vec4 FragColor;

void main()
{

	FragColor = vec4(1.f, 0.f, 0.f, 1.f) * color;
}