#ifndef _BLOCKMESH_H
#define _BLOCKMESH_H

#include <glm/glm.hpp>
#include <gl/glew.h>
#include <gl/glut.h>

typedef struct _VERTEX {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
} VERTEX;

class BlockMesh
{
public:
	GLuint m_arrayBuffer;
	GLuint m_vertexArray;
	VERTEX m_vertices[36];

	BlockMesh();
	~BlockMesh();

	void bind();
	void draw();
};

#endif	// _BLOCKMESH_H