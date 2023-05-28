#include "Block.h"

using namespace glm;

vec2 BLOCK_UV[BLOCK_TYPE_MAX][4];

int blockGetTexture(int _type, int _direction)
{
	switch (_type)
	{
	case BLOCK_TYPE_GRASS:
		if (_direction == DIRECTION_UP)
			return BLOCK_TEXTURE_GRASS_TOP;
		else if (_direction == DIRECTION_DOWN)
			return BLOCK_TEXTURE_DIRT;
		else
			return BLOCK_TEXTURE_GRASS_SIDE;
		break;
	case BLOCK_TYPE_STONE:
		return BLOCK_TEXTURE_STONE;
		break;
	case BLOCK_TYPE_DIRT:
		return BLOCK_TEXTURE_DIRT;
		break;
	case BLOCK_TYPE_PLANKS:
		return BLOCK_TEXTURE_PLANKS;
		break;
	case BLOCK_TYPE_COOBLESTONE:
		return BLOCK_TEXTURE_COBBLESTONE;
		break;
	case BLOCK_TYPE_WOOD:
		if ((_direction == DIRECTION_UP) || (_direction == DIRECTION_DOWN))
			return BLOCK_TEXTURE_WOOD_TOP;
		else
			return BLOCK_TEXTURE_WOOD_SIDE;
	}

	return 0;
}

void blockTextureUVInit()
{
	for (int i = 0; i < BLOCK_TYPE_MAX; i++) {

		int x = i % 16;
		int y = i / 16;

		vec2 position = { x * 16,y * 16 };
		vec2 size = position + 15.f;

		/*
		printf("position=%f,%f\n", position.x, position.y);
		printf("size    =%f,%f\n", size.x, size.y);
		*/

		vec2 upperLeft = position / 256.f;
		vec2 lowerRight = size / 256.f;

		BLOCK_UV[i][0] = upperLeft;
		BLOCK_UV[i][1] = { upperLeft.x, lowerRight.y };
		BLOCK_UV[i][2] = { lowerRight.x, lowerRight.y };
		BLOCK_UV[i][3] = { lowerRight.x, upperLeft.y };
	}
}