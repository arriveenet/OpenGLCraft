#include "TextureManager.h"
#include "Texture.h"

#include <stdio.h>

TextureManager g_textureManager;

static const char* filePath = "resource\\textures\\";

static const char* fileNames[] =
{
	"block.bmp",
	"terrain.bmp",
	"font_0.bmp"
};

TextureManager::TextureManager()
	: m_textures{ 0 }
{
}

TextureManager::~TextureManager()
{
}

bool TextureManager::init()
{
	glGenTextures(TEXTURE_MAX, m_textures);

	for (int i = 0; i < TEXTURE_MAX; i++) {
		glBindTexture(
			GL_TEXTURE_2D,	// GLenum target
			m_textures[i]);	// GLuint texture

		Texture tex;
		char fileName[256];

		sprintf_s(fileName, "%s%s", filePath, fileNames[i]);

		tex.loadBitmapFile(fileName, 0x00, 0x00, 0x00);
		glTexImage2D(
			GL_TEXTURE_2D,		// GLenum target
			0,					// GLint level
			GL_RGBA,			// GLint internalformat
			tex.getWidth(),		// GLsizei width
			tex.getHeight(),	// GLsizei height
			0,					// GLint border
			GL_RGBA,			// GLenum format
			GL_UNSIGNED_BYTE,	// GLenum type
			tex.getTexImage());	// const GLvoid *pixels
		glTexParameteri(
			GL_TEXTURE_2D,			// GLenum target
			GL_TEXTURE_MAG_FILTER,	// GLenum pname
			GL_NEAREST);			// GLint param
		glTexParameteri(
			GL_TEXTURE_2D,			// GLenum target
			GL_TEXTURE_MIN_FILTER,	// GLenum pname
			GL_NEAREST);			// GLint param
		glEnable(GL_TEXTURE_2D);
		tex.deleteTexImage();

		glBindTexture(
			GL_TEXTURE_2D,	// GLenum target
			0);				// GLuint texture
	}

	return true;
}

void TextureManager::setTexture(enum TEXTURE _tex)
{
	glBindTexture(
		GL_TEXTURE_2D,		// GLenum target
		m_textures[_tex]);	// GLuint texture
}

GLuint TextureManager::getTexture(enum TEXTURE _tex)
{
	return m_textures[_tex];
}

void TextureManager::unbindTexture()
{
	glBindTexture(
		GL_TEXTURE_2D,	// GLenum target
		0);				// GLuint texture
}