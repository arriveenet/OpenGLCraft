#pragma once
#ifndef _SHADER_H
#define _SHADER_H

#include <gl/glew.h>
#include <gl/glut.h>
#include <glm/glm.hpp>

#define SHADER_OK                       0x00
#define SHADER_VERTEX_COMPILE_ERROR     0x01
#define SHADER_FRAGMENT_COMPILE_ERROR   0x02
#define SHADER_LINK_ERROR               0x03


enum PROGRAM_TYPE {
	PROGRAM_TYPE_SIMPLE,
	PROGRAM_TYPE_LIGHTING,
	PROGRAM_TYPE_FONT,
	PROGRAM_TYPE_MAX
};

typedef struct _PROGRAM {
	const char* vsFileName;
	const char* fsFileName;
	GLuint program;
} PROGRAM;

class Shader {
	PROGRAM *m_programs;

public:
	Shader();
	~Shader();

	bool init();
	void setProgram(unsigned int _program);
	GLuint getProgram(unsigned int _program);
	int createProgram(GLuint* _program, const char* _vsFileName, const char* _fsFileName);
	const char* getString(unsigned int _name);

private:
	GLuint loadShader(const char* _fileName, GLenum _type);
	bool checkCompileError(GLuint _shader);
	bool checkLinkError(GLuint _program);
};

extern Shader g_shader;

#endif // !_SHADER_H
