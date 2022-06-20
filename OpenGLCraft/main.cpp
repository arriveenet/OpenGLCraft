#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <stdio.h>

#include <gl/glew.h>
#include <gl/freeglut.h>

#include "app.h"
#include "shader.h"

#pragma comment(lib, "glew32.lib")


bool keys[256];

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	//appDraw();
	glUseProgram(g_shader);
	glutWireTeapot(1);

	glutSwapBuffers();
}

void idle()
{
	appUpdate();

	glutPostRedisplay();
}

void keyboard(unsigned char key, int, int)
{
	keys[key] = true;

	if (key == 0x1b)
		glutLeaveMainLoop();
}

void keybordUp(unsigned char key, int, int)
{
	keys[key] = false;
}

int main(int argc, char** argv)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitWindowSize(854, 480);
	glutCreateWindow("OpenGLCraft");

	GLenum err = glewInit();
	if (err != GLEW_OK)
		fprintf(stderr, "%s", glewGetErrorString(err));

	appInit();

	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keybordUp);

	glutMainLoop();

	appRelease();

	_CrtDumpMemoryLeaks();
}