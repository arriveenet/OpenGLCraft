#pragma once
#ifndef _CHUNK_H
#define _CHUNK_H

#include "OpenGLInclude.h"

#define CHUNK_WIDTH		16
#define CHUNK_HEIGHT	16
#define CHUNK_DEPTH		16


class Chunk
{
public:
	unsigned char m_blocks[CHUNK_WIDTH][CHUNK_HEIGHT][CHUNK_DEPTH];
	GLuint m_arrayBuffer;
	GLuint m_vertexArray;

	Chunk();
	~Chunk();

	void update();
	void draw();
};

#endif // !_CHUNK_H
