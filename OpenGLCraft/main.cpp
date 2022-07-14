#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>

#include <gl/glew.h>
#include <gl/freeglut.h>

#include "App.h"
#include "Camera.h"
#include "shader.h"

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
	if (g_app.m_warpPointer)
		return;

	g_camera.rotate(x, y);

	// Set mouse cursor window center
	glutWarpPointer(windowWidth / 2, windowHeight / 2);

	//glutSetCursor(GLUT_CURSOR_NONE);
}

void reshape(int x, int y)
{
	windowWidth = x;
	windowHeight = y;
}

int main(int argc, char** argv)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(400, 200);
	glutCreateWindow("OpenGLCraft");

	GLenum err = glewInit();
	if (err != GLEW_OK)
		fprintf(stderr, "%s", glewGetErrorString(err));

	g_app.init();

	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keybordUp);
	glutMouseFunc(mouse);
	glutPassiveMotionFunc(passiveMotion);
	glutReshapeFunc(reshape);

	glutMainLoop();

	_CrtDumpMemoryLeaks();
}