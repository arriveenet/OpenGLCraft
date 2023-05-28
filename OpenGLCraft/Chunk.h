#pragma once
#ifndef _CHUNK_H
#define _CHUNK_H

#include "OpenGLInclude.h"
#include <vector>
#include <glm/glm.hpp>

#define CHUNK_WIDTH		16
#define CHUNK_HEIGHT	16
#define CHUNK_DEPTH		16

struct Mesh {
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> texCoords;
	std::vector<GLushort> indices;
};

class Chunk
{
	Mesh m_mesh;
	glm::vec3 m_position;
	unsigned int m_vertexCount;

public:
	unsigned char m_blocks[CHUNK_WIDTH][CHUNK_HEIGHT][CHUNK_DEPTH];
	GLuint m_arrayBuffer;
	GLuint m_vertexArray;

	Chunk();
	~Chunk();

	bool inBounds(glm::ivec3 _position);
	bool onBounds(glm::ivec3 _position);

	void update();
	void draw();

protected:
	void addFace(glm::ivec3 _position, int _direction);
};

#endif // !_CHUNK_H
