#include "Player.h"
#include "App.h"
#include "Camera.h"

using namespace glm;

Player::Player()
	: m_position(-3, 1, 1)
	, m_rotation(0)
	, m_speed(0.04f)
{
}

Player::~Player()
{

}

void Player::update()
{
	m_rotation = g_camera.getRotation();

	if (g_app.m_keys['w']) {
		m_position.x += cos(radians(m_rotation.x)) * m_speed;
		m_position.z += sin(radians(m_rotation.x)) * m_speed;;
	}

	if (g_app.m_keys['s']) {
		m_position.x -= cos(radians(m_rotation.x)) * m_speed;
		m_position.z -= sin(radians(m_rotation.x)) * m_speed;
	}

	if (g_app.m_keys['a']) {
		m_position.x += cos(radians(m_rotation.x - 90.f)) * m_speed;
		m_position.z += sin(radians(m_rotation.x - 90.f)) * m_speed;
	}

	if (g_app.m_keys['d']) {
		m_position.x += cos(radians(m_rotation.x + 90.f)) * m_speed;
		m_position.z += sin(radians(m_rotation.x + 90.f)) * m_speed;
	}

	if(g_app.m_keys[' '])
		m_position.y += m_speed;

	if(g_app.m_keys['x'])
		m_position.y -= m_speed;

	g_camera.taranslate(m_position);
	
}

void Player::draw()
{

}