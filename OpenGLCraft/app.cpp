#include "app.h"
#include "shader.h"
#include "BlockMesh.h"

BlockMesh blockMesh;

bool appInit()
{
	blockMesh.bind();
	return shaderInit();
}

void appRelease()
{
	shaderRelease();
}

void appUpdate()
{

}

void appDraw()
{
	blockMesh.draw();
}