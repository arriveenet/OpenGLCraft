#include "Chunk.h"
#include "direction.h"
#include "Block.h"
#include "Shader.h"
#include "TextureManager.h"

using namespace glm;

static  const vec3 vertices[] =
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

static const GLushort faceIndices[] =
{
	0, 1, 2, 0, 2, 3
};

static GLushort indices[] =
{
	2, 1, 0, 2, 0, 3,	// north
	7, 4, 5, 7, 5, 6,	// south
	6, 5, 1, 6, 1, 2,	// east
	3, 0, 4, 3, 4, 7,	// west
	3, 7, 6, 3, 6, 2,	// top
	4, 0, 1, 4, 1, 5	// down
};

static const int directionIndices[][4] =
{
	{2, 1, 0, 3},
	{7, 4, 5, 6},
	{6, 5, 1, 2},
	{3, 0, 4, 7},
	{3, 7, 6, 2},
	{4, 0, 1, 5}
};

static const vec2 texCoords[] =
{
	{0, 0},
	{0, 1},
	{1, 1},
	{1, 0}
};

Chunk::Chunk()
	: m_arrayBuffer(0)
	, m_vertexArray(0)
	, m_vertexCount(0)
{
	memset(m_blocks, BLOCK_TYPE_AIR, sizeof m_blocks);

	for (int x = 0; x < CHUNK_WIDTH; x++) {
		for (int y = 0; y < CHUNK_HEIGHT; y++) {
			for (int z = 0; z < CHUNK_DEPTH; z++) {
				if (y > 3)
					continue;

				if (y == 3)
					m_blocks[x][y][z] = BLOCK_TYPE_GRASS;
				else
					m_blocks[x][y][z] = BLOCK_TYPE_DIRT;
			}
		}
	}

	update();

	//glGenBuffers(1, &m_arrayBuffer);
	//glBindBuffer(GL_ARRAY_BUFFER, m_arrayBuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_mesh, GL_STATIC_DRAW);


	//glGenVertexArrays(1, &m_vertexArray);
	//glBindVertexArray(m_vertexArray);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0); // inPosition
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat))); // inNormal
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat))); // inTexCoord

	//glEnableVertexAttribArray(0);	// inPosition
	//glEnableVertexAttribArray(1);	// inNormal 
	//glEnableVertexAttribArray(2);	// inTexCoord

	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	//glBindVertexArray(0);
}

Chunk::~Chunk()
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

bool Chunk::inBounds(glm::ivec3 _position)
{
	return _position.x >= 0 && _position.y >= 0 && _position.z >= 0 &&
		_position.x < CHUNK_WIDTH&& _position.y < CHUNK_HEIGHT&& _position.z < CHUNK_DEPTH;
}

bool Chunk::onBounds(glm::ivec3 _position)
{
	return _position.x == 0 || _position.y == 0 || _position.z == 0 ||
		_position.x == (CHUNK_WIDTH - 1) || _position.y == (CHUNK_HEIGHT - 1) || _position.z == (CHUNK_DEPTH - 1);
}

void Chunk::update()
{
	m_mesh.vertices.clear();
	m_mesh.indices.clear();
	m_mesh.texCoords.clear();
	m_vertexCount = 0;

	for (int x = 0; x < CHUNK_WIDTH; x++) {
		for (int y = 0; y < CHUNK_HEIGHT; y++) {
			for (int z = 0; z < CHUNK_DEPTH; z++) {
				if (m_blocks[x][y][z] == BLOCK_TYPE_AIR)
					continue;

				ivec3 position = { x, y, z };
				//printf("pos  : %d, %d, %d\n", position.x, position.y, position.z);
				//printf("block: %s\n", blockGetString(getBlock)

				if (x == 0)
					addFace(position, DIRECTION_WEST);
				if (z == 0)
					addFace(position, DIRECTION_NORTH);
				if (x == CHUNK_WIDTH - 1)
					addFace(position, DIRECTION_EAST);
				if (z == CHUNK_DEPTH - 1)
					addFace(position, DIRECTION_SOUTH);
				if (y == 0)
					addFace(position, DIRECTION_DOWN);

				for (int d = 0; d < DIRECTION_MAX; d++) {
					ivec3 neighbor = position + DIRECTION_IVEC3[d];

					if (inBounds(neighbor) && m_blocks[neighbor.x][neighbor.y][neighbor.z] == BLOCK_TYPE_AIR) {
						//printf("neighbor=%d, %d, %d\n", neighbor.x, neighbor.y, neighbor.z);
						addFace(position, d);
					}
				}
			}
		}
	}
}

void Chunk::draw()
{
	g_shader.setProgram(PROGRAM_TYPE_SIMPLE);
	g_textureManager.setTexture(TEXTURE_BLOCK);

	glBindVertexArray(m_vertexArray);

	glEnable(GL_CULL_FACE);

	glDrawElements(GL_TRIANGLES, (GLsizei)m_mesh.indices.size(), GL_UNSIGNED_SHORT, m_mesh.indices.data());

	glDisable(GL_CULL_FACE);

	glBindVertexArray(0);

	g_textureManager.unbindTexture();
	glUseProgram(0);
}

void Chunk::addFace(ivec3 _position, int _direction)
{
	vec3 position = (vec3)_position + m_position;
	int block = m_blocks[_position.x][_position.y][_position.z];
	int texture = blockGetTexture(block, _direction);
	//printf("position: %d, %d, %d\n", _position.x, _position.y, _position.z);
	//printf("block=%s\n", blockGetString(block));
	//printf("tex=%d\n", texture);

	// vertecs
	for (int i = 0; i < 4; i++) {
		m_mesh.vertices.push_back(position + vertices[directionIndices[_direction][i]]);
		//m_mesh.texCoords.push_back(texCoords[i]);
		m_mesh.texCoords.push_back(BLOCK_UV[texture][i]);
	}

	// indices
	for (int i = 0; i < 6; i++) {
		m_mesh.indices.push_back(faceIndices[i] + m_vertexCount);

	}

	m_vertexCount += 4;
}
