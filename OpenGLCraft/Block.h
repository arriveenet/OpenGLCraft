#pragma once
#ifndef _BLOCK_H
#define _BLOCK_H

#include <glm/glm.hpp>
#include "direction.h"

#define BLOCK_TEXTURE_GRASS_TOP		0x00
#define BLOCK_TEXTURE_STONE			0x01
#define BLOCK_TEXTURE_DIRT			0x02
#define BLOCK_TEXTURE_GRASS_SIDE	0x03
#define BLOCK_TEXTURE_PLANKS		0x04
#define BLOCK_TEXTURE_COBBLESTONE	0x10
#define BLOCK_TEXTURE_WOOD_SIDE		0x14
#define BLOCK_TEXTURE_WOOD_TOP		0x15

enum BLOCK_TYPE {
	BLOCK_TYPE_AIR,
	BLOCK_TYPE_GRASS,
	BLOCK_TYPE_STONE,
	BLOCK_TYPE_DIRT,
	BLOCK_TYPE_PLANKS,
	BLOCK_TYPE_COOBLESTONE,
	BLOCK_TYPE_WOOD,
	BLOCK_TYPE_MAX
};

class Block
{
};
int blockGetTexture(int _type, int _direction = DIRECTION_MAX);
void blockTextureUVInit();

extern glm::vec2 BLOCK_UV[BLOCK_TYPE_MAX][4];

#endif // !_BLOCK_H
