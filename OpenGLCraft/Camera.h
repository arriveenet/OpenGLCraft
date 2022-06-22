#ifndef _CAMERA_H

#include <glm/glm.hpp>

class Camera
{
	glm::vec2 m_rotation;
	glm::vec3 m_eye;
	glm::vec3 m_center;
	glm::vec3 m_up;
	glm::vec3 m_direction;
	glm::mat4 m_projection;
	glm::mat4 m_view;
	float m_fovy;

public:
	Camera();

	glm::vec3 getEye();
	glm::vec3 getCenter();
	glm::vec2& getRotation();
	void setEye(glm::vec3& _eye);
	void setCenter(glm::vec3& _center);

	void taranslate(glm::vec3& _position);
	void rotate(int _x, int _y);
	void update();
};

extern Camera g_camera;

#endif // !_CAMERA_H
