#include "direction.h"

const glm::ivec3 DIRECTION_IVEC3[DIRECTION_MAX] =
{
	{ 0,  0, -1},// DIRECTION_NORTH
	{ 0,  0,  1},// DIRECTION_SOUTH
	{ 1,  0,  0},// DIRECTION_EAST
	{-1,  0,  0},// DIRECTION_WEST
	{ 0,  1,  0},// DIRECTION_UP
	{ 0, -1,  0},// DIRECTION_DOWN
};

const glm::vec3 DIRECTION_VEC3[DIRECTION_MAX] =
{
	{ 0,  0, -1},// DIRECTION_NORTH
	{ 0,  0,  1},// DIRECTION_SOUTH
	{ 1,  0,  0},// DIRECTION_EAST
	{-1,  0,  0},// DIRECTION_WEST
	{ 0,  1,  0},// DIRECTION_UP
	{ 0, -1,  0},// DIRECTION_DOWN
};