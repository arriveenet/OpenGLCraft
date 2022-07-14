#include "BlockMesh.h"
#include "Shader.h"
#include "Texture.h"
#include "TextureManager.h"

#include <vector>

using namespace glm;

static const vec3 vertices[] =
{
	{0.0f, 0.0f, 0.0f},	// 0
	{1.0f, 0.0f, 0.0f},	// 1
	{1.0f, 1.0f, 0.0f},	// 2
	{0.0f, 1.0f, 0.0f},	// 3

	{0.0f, 0.0f, 1.0f},	// 4
	{1.0f, 0.0f, 1.0f},	// 5
	{1.0f, 1.0f, 1.0f},	// 6
	{0.0f, 1.0f, 1.0f}	// 7
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

static const vec3 normals[] =
{
	{ 0.0f,  0.0f, -1.0f},	// north
	{ 0.0f,  0.0f,  1.0f},	// south
	{ 1.0f,  0.0f,  0.0f},	// east
	{-1.0f,  0.0f,  0.0f},	// west
	{ 0.0f,  1.0f,  0.0f},	// top
	{ 0.0f, -1.0f,  0.0f}	// down
};

static const unsigned char normalIndex[] =
{
	0, 0, 0, 0, 0, 0,
	1, 1, 1, 1, 1, 1,
	2, 2, 2, 2, 2, 2,
	3, 3, 3, 3, 3, 3,
	4, 4, 4, 4, 4, 4,
	5, 5, 5, 5, 5, 5
};

static vec2 texCoord[] =
{
	{1.0f, 0.0f},	// 0	1, 0	right bottom
	{0.0f, 0.0f},	// 1	0, 0	left bottom
	{0.0f, 1.0f},	// 2	0, 1	left top
	{1.0f, 1.0f}	// 3	1, 1	right top
};

static unsigned char texIndices[] =
{
	1, 2, 3, 1, 3, 0,	// north
	1, 2, 3, 1, 3, 0,	// south
	1, 2, 3, 1, 3, 0,	// east
	1, 2, 3, 1, 3, 0,	// west
	1, 2, 3, 1, 3, 0,	// top
	1, 2, 3, 1, 3, 0	// down
};



BlockMesh::BlockMesh()
	: m_arrayBuffer(0)
	, m_vertexArray(0)
	, m_vertices()
{
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
	for (int i = 0; i < 36; i++) {
		m_vertices[i].position = vertices[indices[i]];
		m_vertices[i].normal = normals[normalIndex[i]];
		m_vertices[i].texCoord = texCoord[texIndices[i]];
	}

	glGenBuffers(1, &m_arrayBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_arrayBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);


	glGenVertexArrays(1, &m_vertexArray);
	glBindVertexArray(m_vertexArray);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)0); // inPosition
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat))); // inNormal
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(6 * sizeof(GLfloat))); // inTexCoord

	glEnableVertexAttribArray(0);	// inPosition
	glEnableVertexAttribArray(1);	// inNormal
	glEnableVertexAttribArray(2);	// inTexCoord

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

}

void BlockMesh::draw()
{
	g_shader.setProgram(PROGRAM_TYPE_SIMPLE);
	g_textureManager.setTexture(TEXTURE_BLOCK);

	glBindVertexArray(m_vertexArray);

	glEnable(GL_CULL_FACE);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glDisable(GL_CULL_FACE);

	glBindVertexArray(0);

	g_textureManager.unbindTexture();
	glUseProgram(0);
}