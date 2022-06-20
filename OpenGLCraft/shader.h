#pragma once

#include <gl/glew.h>
#include <gl/glut.h>

#define SHADER_OK                       0x00
#define SHADER_VERTEX_COMPILE_ERROR     0x01
#define SHADER_FRAGMENT_COMPILE_ERROR   0x02
#define SHADER_LINK_ERROR               0x03

enum SHADER_TYPE {
	SHADER_TYPE_BASIC,
	SHADER_TYPE_MAX
};

typedef struct _SHADER {
	GLuint shader;
} SHADER;

bool shaderInit();
void shaderRelease();
int shaderCreateProgram(GLuint* _program, const char* _vsFileName, const char* _fsFileName);
const char* shaderGetString(unsigned int _name);


extern GLuint g_shader;

