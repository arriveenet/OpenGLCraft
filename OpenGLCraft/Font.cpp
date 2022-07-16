#include "Font.h"
#include "App.h"
#include "Shader.h"
#include "TextureManager.h"

#include <stdio.h>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

Font g_font;

Font::Font()
	: m_info{}
	, m_common{}
	, m_page{}
	, m_chars(NULL)
	, m_pChars(NULL)
	, m_charMax(0)
	, m_arrayBuffer(0)
	, m_vertexArray(0)
	, m_projection(1.0f)
	, m_view(1.0f)
{
}

Font::~Font()
{
	if (m_chars) {
		delete[] m_chars;
		m_chars = NULL;
	}

	if (m_pChars) {
		free(m_pChars);
		m_pChars = NULL;
	}

	if (m_arrayBuffer) {
		glDeleteBuffers(1, &m_arrayBuffer);
		m_arrayBuffer = 0;
	}

	if (m_vertexArray) {
		glDeleteVertexArrays(1, &m_vertexArray);
		m_vertexArray = 0;
	}
}

bool Font::loadFntFile(const char* _fileName)
{

	FILE* pFile;
	errno_t err;
	bool result = true;
	unsigned char header[4];
	char blockType;
	int blockSize;

	err = fopen_s(&pFile, _fileName, "rb");

	if (err != 0) {
		printf("The file was %s open failed!\n", _fileName);
		return false;
	}
	printf("The file was %s opened!\n", _fileName);
	fpos_t fsize = 0;

	fseek(pFile, 0, SEEK_END);
	fgetpos(pFile, &fsize);

	fseek(pFile, 0, SEEK_SET);
	fread(header, 4, 1, pFile);
	if ((header[0] == 'B')
		&& (header[1] == 'M')
		&& (header[2] == 'F')
		) {

		// Read FONTINFO
		fread(&blockType, 1, 1, pFile);
		fread(&blockSize, 4, 1, pFile);
		if (blockSize > sizeof FONTINFO)
			result = false;
		else
		{
			fread(&m_info, blockSize, 1, pFile);
			/*puts("\n--FONTINFO--");
			printf("fontSize: %d\n", m_info.fontSize);
			printf("bitField: %d\n", m_info.bitField);
			printf("charSet: %d\n", m_info.charSet);
			printf("stretchH: %d\n", m_info.stretchH);
			printf("aa: %d\n", m_info.aa);
			printf("paddingUp: %d\n", m_info.paddingUp);
			printf("paddingRight: %d\n", m_info.paddingRight);
			printf("paddingDown: %d\n", m_info.paddingDown);
			printf("paddingLeft: %d\n", m_info.paddingLeft);
			printf("spacingHoriz: %d\n", m_info.spacingHoriz);
			printf("spacingVert: %d\n", m_info.spasingVert);
			printf("outline: %d\n", m_info.outline);
			printf("fontName: %s\n", m_info.fontName);*/
		}

		// Read FONTCOMMON
		fread(&blockType, 1, 1, pFile);
		fread(&blockSize, 4, 1, pFile);
		if (blockSize > sizeof FONTCOMMON)
			result = false;
		else
		{
			fread(&m_common, blockSize, 1, pFile);
			/*puts("\n--FONTCOMMON--");
			printf("lineHeight: %d\n", m_common.lineHeight);
			printf("base: %d\n", m_common.base);
			printf("scaleW: %d\n", m_common.scaleW);
			printf("scaleH: %d\n", m_common.scaleH);
			printf("pages: %d\n", m_common.pages);
			printf("bitField: %d\n", m_common.bitField);
			printf("alphaChnl: %d\n", m_common.alphaChnl);
			printf("redChnl: %d\n", m_common.redChnl);
			printf("greenChnl: %d\n", m_common.greenChnl);
			printf("blueChnl: %d\n", m_common.blueChnl);*/
		}

		// Read FONTPAGE
		fread(&blockType, 1, 1, pFile);
		fread(&blockSize, 4, 1, pFile);
		if (blockSize > sizeof FONTPAGE)
			result = false;
		else
		{
			fread(&m_page, blockSize, 1, pFile);
			/*puts("\n--FONTPAGE--");
			printf("pageNames: %s\n", m_page.pageNames);*/
		}

		// Read FONTCHAR
		fread(&blockType, 1, 1, pFile);
		fread(&blockSize, 4, 1, pFile);
		int numChars = blockSize / sizeof FONTCHAR;
		puts("\n--FONTCHAR--");
		printf("numChars: %d\n", numChars);
		m_chars = new FONTCHAR[numChars];
		if (m_chars != NULL)
			fread(m_chars, sizeof FONTCHAR, numChars, pFile);
		else
			result = false;

		for (int i = 0; i < numChars; i++) {
			m_charMax = __max(m_chars[i].id, m_charMax);
			//printf("\nchars[%d]\n", i);
			//printf("id: %d\n", m_chars[i].id);
			//printf("x: %d\n", m_chars[i].x);
			//printf("y: %d\n", m_chars[i].y);
			//printf("width: %d\n", m_chars[i].width);
			//printf("height: %d\n", m_chars[i].height);
		}
		m_charMax++;
		printf("m_charMax:%d\n", m_charMax);
		m_pChars = (FONTCHAR **)calloc(m_charMax, sizeof(FONTCHAR*));

		for (int i = 0; i < numChars; i++)
			m_pChars[m_chars[i].id] = &m_chars[i];
		
		//int count = 0;
		//for (unsigned i = 0; i < m_charMax; i++) {
		//	if (!m_pChars[i])
		//		continue;

		//	printf("%d: id:%u\n", ++count, m_pChars[i]->id);
		//}
	} else {
		result = false;
	}

	fclose(pFile);

	return result;
}

void Font::draw()
{
	m_projection = ortho(0, windowWidth, windowHeight, 0);
	mat4 modelViewProjection = m_projection * m_view;
	
	g_shader.setProgram(PROGRAM_TYPE_FONT);
	g_textureManager.setTexture(TEXTURE_FONT);

	GLuint program = g_shader.getProgram(PROGRAM_TYPE_FONT);
	glUniformMatrix4fv(
		glGetUniformLocation(program,
			"modelViewProjection"),
		1, GL_FALSE, (GLfloat*)&modelViewProjection);


	g_textureManager.unbindTexture();
	glUseProgram(0);
}