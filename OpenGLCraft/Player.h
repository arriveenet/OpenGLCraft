#ifndef _PLAYER_H
#define _PLAYER_H

#include <glm/glm.hpp>

class Player
{
public:
	glm::vec3 m_position;
	glm::vec2 m_rotation;
	float m_speed;

	Player();
	~Player();

	void update();
	void draw();
};

#endif // !_PLAYER_H
