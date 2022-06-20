#pragma once
#include <glm/glm.hpp>
#include <gl/glew.h>
#include <gl/glut.h>

class BlockMesh
{
public:
	GLuint m_arrayBuffer;
	GLuint m_vertexArray;

	BlockMesh();
	~BlockMesh();

	void bind();
	void draw();
};

