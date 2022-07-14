#include "shader.h"
#include <stdio.h>

Shader g_shader;

PROGRAM programs[PROGRAM_TYPE_MAX] = {
	{"simple.vert", "simple.frag", 0},
	{"lighting.vert", "lighting.frag", 0}
};

Shader::Shader()
	: m_programs(programs)
{
}

Shader::~Shader()
{
	for (int i = 0; i < PROGRAM_TYPE_MAX; i++) {
		glDeleteProgram(m_programs[i].program);
	}
}

bool Shader::init()
{
	bool result = true;
	const char* filePath = "resource\\shaders\\";

	for (int i = 0; i < PROGRAM_TYPE_MAX; i++) {
		char vsFileName[256];
		char fsFileName[256];
		sprintf_s(vsFileName, "%s%s", filePath, m_programs[i].vsFileName);
		sprintf_s(fsFileName, "%s%s", filePath, m_programs[i].fsFileName);

		if (createProgram(&m_programs[i].program, vsFileName, fsFileName) != SHADER_OK) {
			//glDeleteProgram(g_shader);
			fprintf(stderr, "%s", getString(result));
			result = false;
		}
	}

	return result;
}

void Shader::setProgram(unsigned int _type)
{
	glUseProgram(m_programs[_type].program);
}

GLuint Shader::getProgram(unsigned int _type)
{
	return m_programs[_type].program;
}

int Shader::createProgram(GLuint* _program, const char* _vsFileName, const char* _fsFileName)
{
	GLuint program = 0;
	int status = SHADER_OK;

	GLuint vertexShader = loadShader(_vsFileName, GL_VERTEX_SHADER);
	GLuint fragmentShader = loadShader(_fsFileName, GL_FRAGMENT_SHADER);

	glCompileShader(vertexShader);
	if (!checkCompileError(vertexShader))
		status = SHADER_VERTEX_COMPILE_ERROR;

	glCompileShader(fragmentShader);
	checkCompileError(fragmentShader);
	if (!checkCompileError(fragmentShader))
		status = SHADER_FRAGMENT_COMPILE_ERROR;

	program = glCreateProgram();

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glLinkProgram(program);
	if (!checkLinkError(program))
		status = SHADER_LINK_ERROR;

	*_program = program;

	return status;
}

const char* Shader::getString(unsigned int _name)
{
	const char* str;
	//printf("_name=%d\n", _name);

	switch (_name) {
	case SHADER_OK:
		str = "SHADER_OK";
		break;
	case SHADER_VERTEX_COMPILE_ERROR:
		str = "SHADER_VERTEX_COMPILE_ERROR";
		break;
	case SHADER_FRAGMENT_COMPILE_ERROR:
		str = "SHADER_FRAGMENT_COMPILE_ERROR";
		break;
	case SHADER_LINK_ERROR:
		str = "SHADER_LINK_ERROR";
		break;
	default:
		str = "Invalid name";
		break;
	}

	return str;
}

GLuint Shader::loadShader(const char* _fileName, GLenum _type)
{
	FILE* pFile;
	int size;
	char* buf;
	GLuint shader = 0;

	fopen_s(&pFile, _fileName, "rb");
	if (!pFile) {
		printf("%s open feiled!\n", _fileName);
		return 0;
	}
	printf("%s open succeeded.\n", _fileName);
	fseek(pFile, 0, SEEK_END);
	size = ftell(pFile);

	buf = (char*)malloc(size);
	fseek(pFile, 0, SEEK_SET);

	if (buf != 0) {
		fread(buf, 1, size, pFile);
		//printf("%s", buf);

		shader = glCreateShader(_type);
		glShaderSource(shader, 1, (const GLchar**)&buf, &size);
	}
	free(buf);
	fclose(pFile);

	return shader;
}

bool Shader::checkCompileError(GLuint _shader)
{
	GLint compiled;
	int size;
	int length;
	char* str;
	bool result = true;

	glGetShaderiv(_shader, GL_COMPILE_STATUS, &compiled);
	if (compiled == GL_FALSE) {
		glGetShaderiv(_shader, GL_INFO_LOG_LENGTH, &size);
		if (size > 0) {
			str = (char*)malloc(size);
			glGetShaderInfoLog(_shader, size, &length, str);
			printf("Compile error: %s!\n", str);
			free(str);
			result = false;
		}
	}

	return result;
}

bool Shader::checkLinkError(GLuint _program)
{
	GLint linked;
	int size;
	int length;
	char* str;
	bool result = true;

	glGetShaderiv(_program, GL_LINK_STATUS, &linked);
	if (linked == GL_FALSE) {
		glGetShaderiv(_program, GL_INFO_LOG_LENGTH, &size);
		if (size > 0) {
			str = (char*)malloc(size);
			glGetShaderInfoLog(_program, size, &length, str);
			printf("Link error: %s!\n", str);
			free(str);
			result = false;
		}
	}

	return result;
}
