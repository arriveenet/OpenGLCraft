#ifndef _APP_H
#define _APP_H

#include <glm/glm.hpp>

class App {
public:
	glm::mat4 m_projection;
	glm::mat4 m_view;
	glm::mat4 m_modelViewProjection;
	bool m_keys[256];
	bool m_warpPointer;
	bool m_isWireflame;
	App();
	~App();

	bool init();
	void update();
	void draw();
};

extern App g_app;
extern int windowWidth;
extern int windowHeight;

#endif // !_APP_H


