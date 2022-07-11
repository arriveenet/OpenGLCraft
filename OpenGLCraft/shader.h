#pragma once

#include <gl/glew.h>
#include <gl/glut.h>

#define SHADER_OK                       0x00
#define SHADER_VERTEX_COMPILE_ERROR     0x01
#define SHADER_FRAGMENT_COMPILE_ERROR   0x02
#define SHADER_LINK_ERROR               0x03

enum SHADER_TYPE {
	SHADER_TYPE_SIMPLE,
	SHADER_TYPE_LIGHTING,
	SHADER_TYPE_MAX
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
	void setProgram(unsigned int _type);
	GLuint getProgram(unsigned int _type);
	int createProgram(GLuint* _program, const char* _vsFileName, const char* _fsFileName);
	const char* getString(unsigned int _name);

private:
	GLuint loadShader(const char* _fileName, GLenum _type);
	bool checkCompileError(GLuint _shader);
	bool checkLinkError(GLuint _program);
};


extern Shader g_shader;

