#include "App.h"
#include "Shader.h"
#include "Block.h"
#include "BlockMesh.h"
#include "Camera.h"
#include "Player.h"
#include "TextureManager.h"
#include "Font.h"
#include "FrameCounter.h"

#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

BlockMesh blockMesh(vec3(1,0,0));
Player player;

int windowWidth = 854;
int windowHeight = 480;

App g_app;

App::App()
	: m_projection(1.0f)
	, m_view(1.0f)
	, m_modelViewProjection(1.0f)
	, m_keys{}
	, m_warpPointer(false)
	, m_isWireflame(false)
{
}

App::~App()
{
}

bool App::init()
{
	if (!g_shader.init())
		return false;

	if (!g_textureManager.init())
		return false;

	if (!g_font.init())
		return false;

	blockMesh.bind();
	blockTextureUVInit();

	glClearColor(129 / 255.f, 173 / 255.f, 255 / 255.f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	return true;
}

void App::update()
{
	g_frameCounter.update();

	if (m_keys['e'])
		m_warpPointer = m_warpPointer ? false : true;
	if (m_keys['f'])
		m_isWireflame = m_isWireflame ? false : true;
	
	g_font.setText(0, 0, "fps: %u", g_frameCounter.getFrameCount());
	g_font.setText(0, 30,"XYZ: %.3f / %f / %.3f",
		player.m_position.x, player.m_position.y, player.m_position.z);
	g_font.setText(((float)windowWidth / 2.f)-7.f, ((float)windowHeight / 2.f) - 19.f, "+");

	player.update();

	g_camera.update();
	//printf("x=%d, y=%d\n", m_mousePosition.x, m_mousePosition.y);
}

void App::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	g_camera.loadMatrix();

	for (int i = -10; i <= 10; i++) {
		glBegin(GL_LINES);
		glVertex3i(i, 0, -10);
		glVertex3i(i, 0, 10);
		glVertex3i(-10, 0, i);
		glVertex3i(10, 0, i);
		glEnd();
	}

	blockMesh.draw();

	g_font.draw();

	glPolygonMode(GL_FRONT_AND_BACK, m_isWireflame ? GL_LINE : GL_FILL);
}