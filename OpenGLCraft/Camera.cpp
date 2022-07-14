#include "Camera.h"
#include "App.h"
#include "shader.h"

#include <gl/glew.h>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

Camera g_camera;

Camera::Camera()
	: m_rotation(0)
	, m_eye(2, 1, 2)
	, m_center(0)
	, m_up(0, 1, 0)
	, m_direction(0)
	, m_projection(1.0f)
	, m_view(1.0f)
	, m_modelViewProjection(1.0f)
	, m_fovy(90.f)
{
}

vec3 Camera::getEye()
{
	return m_eye;
}

vec3 Camera::getCenter()
{
	return m_center;
}

glm::vec2& Camera::getRotation()
{
	return m_rotation;
}

void Camera::setEye(vec3& _eye)
{
	m_eye = _eye;
}

void Camera::setCenter(vec3& _center)
{
	m_center = _center;
}

void Camera::taranslate(vec3& _position)
{
	m_eye = _position;
}

void Camera::rotate(int _x, int _y)
{
	int changeX = _x - windowWidth / 2;
	int changeY = _y - windowHeight / 2;

	m_rotation.x += (float)changeX * 0.05f;
	m_rotation.y += (float)changeY * 0.05f;

	if (m_rotation.x > 360)
		m_rotation.x = 0;
	if (m_rotation.x < 0)
		m_rotation.x = 360;

	if (m_rotation.y > 90.f)
		m_rotation.y = 90.f;
	if (m_rotation.y < -90.f)
		m_rotation.y = -90.f;

	vec3 direction = {
		cosf(radians(m_rotation.x)) * cosf(radians(m_rotation.y)),	// x
		sinf(radians(-m_rotation.y)),								// y
		sinf(radians(m_rotation.x)) * cosf(radians(m_rotation.y))	// z
	};

	//printf("rotate: %f, %f\n", m_rotation.x, m_rotation.y);
	m_direction = normalize(direction);
	m_center = m_eye + m_direction;
}

void Camera::update()
{
	m_projection = perspective(radians(90.f), (float)windowWidth / (float)windowHeight, 0.1f, 100.f);
	m_view = lookAt(m_eye, m_center, m_up);
	m_modelViewProjection = m_projection * m_view;
}

void Camera::loadMatrix()
{
	g_shader.setProgram(PROGRAM_TYPE_SIMPLE);
	GLuint program = g_shader.getProgram(PROGRAM_TYPE_SIMPLE);
	glUniformMatrix4fv(
		glGetUniformLocation(program,
			"modelViewProjection"),
		1, GL_FALSE, (GLfloat*)&m_modelViewProjection);
}