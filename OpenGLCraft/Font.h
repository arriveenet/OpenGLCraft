#pragma once
#ifndef _FONT_H
#define _FONT_H

#include <gl/glew.h>
#include <gl/glut.h>
#include <glm/glm.hpp>

#include <vector>

/* This tag holds information on how the font was generated. */
typedef struct tagFONTINFO {
	short fontSize;
	unsigned char bitField;
	unsigned char charSet;
	unsigned short stretchH;
	unsigned char aa;
	unsigned char paddingUp;
	unsigned char paddingRight;
	unsigned char paddingDown;
	unsigned char paddingLeft;
	unsigned char spacingHoriz;
	unsigned char spasingVert;
	unsigned char outline;
	char fontName[256];
}FONTINFO;

/* This tag holds information common to all characters. */
typedef struct tagFONTCOMMON {
	unsigned short lineHeight;
	unsigned short base;
	unsigned short scaleW;
	unsigned short scaleH;
	unsigned short pages;
	unsigned char bitField;
	unsigned char alphaChnl;
	unsigned char redChnl;
	unsigned char greenChnl;
	unsigned char blueChnl;
}FONTCOMMON;

/* This tag gives the name of a texture file. There is one for each page in the font. */
typedef struct tagFONTPAGE {
	char pageNames[256];
}FONTPAGE;

/* This tag describes on character in the font. There is one for each included character in the font. */
typedef struct tagFONTCHAR {
	unsigned int id;		// The character id
	unsigned short x;		// The left position of the character image in the texture
	unsigned short y;		// The top position of the character image in the texture
	unsigned short width;	// The width of the character image in the texture
	unsigned short height;	// The height of the character image in the texture
	short xoffset;			// How much the current position should be offset when copying the image from the texture to the screen
	short yoffset;			// How much the current position should be offset when copying the image from the texture to the screen
	short xadvance;			// How much the current position should be advanced after drawing the character.
	unsigned char page;		// The texture page where the character image is found
	unsigned char chnl;		// The texture channel where the character image is found (1 = blue, 2 = green, 4 = red, 8 = alpha, 15 = all channels)
}FONTCHAR;

typedef struct tagFONTVERTIX {
	glm::vec3 position;
	glm::vec2 texCoord;
}FONTVERTIX;

class Font
{
	FONTINFO m_info;
	FONTCOMMON m_common;
	FONTPAGE m_page;
	FONTCHAR* m_chars;
	FONTCHAR** m_pChars;
	unsigned int m_charMax;

	GLuint m_arrayBuffer;
	GLuint m_vertexArray;

	glm::mat4 m_projection;
	glm::mat4 m_view;
	glm::mat4 m_modelViewProjection;

	std::vector<FONTVERTIX> m_vertices;

public:
	Font();
	~Font();

	bool init();
	bool loadFntFile(const char* _fileName);
	void setText(float _x, float _y, const char* _format, ...);
	void bind();
	void draw();
};

extern Font g_font;

#endif // !_FONT_H
