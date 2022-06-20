#include "BlockMesh.h"
#include "shader.h"

using namespace glm;

const static vec3 vertices[] =
{
	{0, 0, 0},	// 0
	{1, 0, 0},	// 1
	{1, 1, 0},	// 2
	{0, 1, 0},	// 3

	{0, 0, 1},	// 4
	{1, 0, 1},	// 5
	{1, 1, 1},	// 6
	{0, 1, 1}	// 7
};

static unsigned char indices[] =
{
	2, 1, 0, 2, 0, 3,	// north
	7, 4, 5, 7, 5, 6,	// south
	6, 5, 1, 6, 1, 2,	// east
	3, 0, 4, 3, 4, 7,	// west
	3, 7, 6, 3, 6, 2,	// top
	1, 5, 4, 1, 4, 0	// down
};

static vec2 texCoord[] =
{
	{32.f / 256.f, 0.f / 256.f},	// 0	1, 0
	{16.f / 256.f, 0.f / 256.f},	// 1	0, 0
	{16.f / 256.f, 16.f / 256.f},	// 2	0, 1
	{32.f / 256.f, 16.f / 256.f}	// 3	1, 1
};

static unsigned char texIndices[] =
{
	3, 2, 1, 0, 3, 1,
	0, 1, 2, 0, 2, 3
};

static const GLfloat colorAndVertices[3][5] =
{
	{1.0f, 1.0f , 0.0f, -0.5f, -0.5f},
	{1.0f, 1.0f , 0.0f,  0.5f, -0.5f},
	{1.0f, 1.0f , 0.0f,  0.0f,  0.5f}
};

BlockMesh::BlockMesh()
	: m_arrayBuffer(0)
	, m_vertexArray(0)
{
	/*
	for (int i = 0; i < 8; i++) {
		m_vertices[i] = vertices[i];
	}

	for (int i = 0; i < 12; i++) {
		m_texCoord[i] = texCoord[texIndices[i]];
	}
	*/

}

BlockMesh::~BlockMesh()
{
	if (m_arrayBuffer) {
		glDeleteBuffers(1, &m_arrayBuffer);
		m_arrayBuffer = 0;
	}

	if (m_vertexArray) {
		glDeleteVertexArrays(1, &m_vertexArray);
		m_vertexArray = 0;
	}
}

void BlockMesh::bind()
{
	glGenBuffers(1, &m_arrayBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_arrayBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof colorAndVertices, colorAndVertices, GL_STATIC_DRAW);


	glGenVertexArrays(1, &m_vertexArray);
	glBindVertexArray(m_vertexArray);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
		5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void BlockMesh::draw()
{
	glUseProgram(g_shader);

	glBindVertexArray(m_vertexArray);
	//glEnable(GL_CULL_FACE);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(0);

	glUseProgram(0);
}