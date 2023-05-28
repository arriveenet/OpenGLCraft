#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>

#include <gl/glew.h>

#include <gl/freeglut.h>

#include "App.h"
#include "Camera.h"
#include "Shader.h"
#include "Font.h"

#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32


#pragma comment(lib, "glew32.lib")

void display()
{
	g_app.draw();

	glutSwapBuffers();
}

void idle()
{
	g_app.update();

	glutPostRedisplay();
}

void release()
{
	g_shader.~Shader();
	g_font.~Font();
}

void keyboard(unsigned char key, int, int)
{
	g_app.m_keys[key] = true;

	if (key == 0x1b)
		glutLeaveMainLoop();
}

void keybordUp(unsigned char key, int, int)
{
	g_app.m_keys[key] = false;
}

void mouse(int button, int state, int x, int y)
{
}

void passiveMotion(int x, int y)
{
	if (g_app.m_warpPointer) {
		glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
		return;
	}

	g_camera.rotate(x, y);

	// Set mouse cursor window center
	glutWarpPointer(windowWidth / 2, windowHeight / 2);

	glutSetCursor(GLUT_CURSOR_NONE);
}

void reshape(int x, int y)
{
	windowWidth = x;
	windowHeight = y;
}

int main(int argc, char** argv)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	int result = EXIT_SUCCESS;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitWindowSize(windowWidth, windowHeight);

	// Set window position.
#ifdef _WIN32
	int screenX = GetSystemMetrics(SM_CXSCREEN);
	int screenY = GetSystemMetrics(SM_CYSCREEN);
	printf("screen=%dx%d\n", screenX, screenY);
	glutInitWindowPosition((screenX / 2) - (windowWidth / 2), (screenY / 2) - (windowHeight / 2));
#else
	glutInitWindowPosition(400, 200);
#endif // _WIN32
	
	glutCreateWindow("OpenGLCraft");

	GLenum err = glewInit();
	if (err != GLEW_OK)
		fprintf(stderr, "%s", glewGetErrorString(err));

	if (!g_app.init()) {
		result = EXIT_FAILURE;
	}

	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keybordUp);
	glutMouseFunc(mouse);
	glutPassiveMotionFunc(passiveMotion);
	glutReshapeFunc(reshape);

	glutMainLoop();

	release();

	_CrtDumpMemoryLeaks();

	return result;
}