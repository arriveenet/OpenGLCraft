#pragma once
#ifndef _CHUNK_H
#define _CHUNK_H

#include "OpenGLInclude.h"

#define CHUNK_WIDTH		16
#define CHUNK_HEIGHT	16
#define CHUNK_DEPTH		16


class Chunk
{
	GLuint m_arrayBuffer;
	GLuint m_vertexArray;
};

#endif // !_CHUNK_H
