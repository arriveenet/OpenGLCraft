#pragma once
#ifndef _TEXTUREMANAGER_H
#define _TEXTUREMANAGER_H

#include <gl/glut.h>

enum TEXTURE {
	TEXTURE_BLOCK,
	TEXUTRE_TERRAIN,
	TEXUTRE_FONT,
	TEXTURE_MAX
};

class TextureManager
{
	GLuint m_textures[TEXTURE_MAX];

public:
	TextureManager();
	~TextureManager();

	bool init();
	void setTexture(enum TEXTURE _tex);
	GLuint getTexture(enum TEXTURE _tex);

	void unbindTexture();
};

extern TextureManager g_textureManager;

#endif // !_TEXTUREMANAGER_H
