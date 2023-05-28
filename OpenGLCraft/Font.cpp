#include "Font.h"
#include "App.h"
#include "Shader.h"
#include "TextureManager.h"

#include <stdio.h>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <stdarg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

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
	, m_modelViewProjection(1.0f)
	, m_vertices()
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

bool Font::init()
{
	loadFntFile("resource\\font\\font.fnt");

	setText(0, 0, "Font init");

	glGenBuffers(1, &m_arrayBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_arrayBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(FONTVERTIX) * m_vertices.size(), m_vertices.data(), GL_DYNAMIC_DRAW);

	glGenVertexArrays(1, &m_vertexArray);
	glBindVertexArray(m_vertexArray);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	m_projection = glm::ortho(0.f, (float)windowWidth, (float)windowHeight, 0.f);
	m_modelViewProjection = m_projection * m_view;

	return true;
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
		/*puts("\n--FONTCHAR--");
		printf("numChars: %d\n", numChars);*/
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
		//printf("m_charMax:%d\n", m_charMax);
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

void Font::setText(float _x, float _y, const char* _format, ...)
{
	va_list ap;
	char str[256];
	char* p;

	va_start(ap, _format);
	vsprintf_s(str, _format, ap);
	va_end(ap);

	vec3 drawPosition = { _x, _y, 0 };

	for (p = str; (*p != '\0') && (*p != '\n'); p++) {
		FONTCHAR* fntChar = m_pChars[*p];

		FONTVERTIX vertix[4];
		vertix[0].position = drawPosition + vec3(fntChar->xoffset, fntChar->yoffset, 0);
		vertix[0].texCoord = vec2((float)fntChar->x / 256.0f, (float)fntChar->y / 256.0f);
		vertix[1].position = drawPosition + vec3(fntChar->xoffset, fntChar->height + fntChar->yoffset, 0);
		vertix[1].texCoord = vec2((float)fntChar->x / 256.0f, (float)(fntChar->y + fntChar->height) / 256.0f);
		vertix[2].position = drawPosition + vec3(fntChar->width + fntChar->xoffset, fntChar->height + fntChar->yoffset, 0);
		vertix[2].texCoord = vec2((float)(fntChar->x + fntChar->width) / 256.0f, (float)(fntChar->y + fntChar->height) / 256.0f);
		vertix[3].position = drawPosition + vec3(fntChar->width + fntChar->xoffset, fntChar->yoffset, 0);
		vertix[3].texCoord = vec2((float)(fntChar->x + fntChar->width) / 256.0f, (float)fntChar->y / 256.0f);

		int index[] = { 0,1,2,0,2,3 };
		for (int i = 0; i < 6; i++) {
			m_vertices.push_back(vertix[index[i]]);
		}

		drawPosition.x += fntChar->xadvance;
	}
}

void Font::bind()
{

}

void Font::draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_arrayBuffer);
	//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(FONTVERTIX) * m_vertices.size(), m_vertices.data());
	glBufferData(GL_ARRAY_BUFFER, sizeof(FONTVERTIX) * m_vertices.size(), m_vertices.data(), GL_DYNAMIC_DRAW);

	/*std::cout << "m_vertices data:" << m_vertices.data() << "\n";
	std::cout << "m_vertices size:" << m_vertices.size() << "\n";*/
	
	g_textureManager.setTexture(TEXTURE_FONT);
	g_shader.setProgram(PROGRAM_TYPE_FONT);
	GLuint program = g_shader.getProgram(PROGRAM_TYPE_FONT);

	glUniformMatrix4fv(
		glGetUniformLocation(program,
			"modelViewProjection"),
		1, GL_FALSE, (GLfloat*)&m_modelViewProjection);

	glBindVertexArray(m_vertexArray);

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);// GLenum cap

	glBlendFunc(
		GL_SRC_ALPHA,			// GLenum sfactor
		GL_ONE_MINUS_SRC_ALPHA);// GLenum dfactor

	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)m_vertices.size());

	glDisable(GL_CULL_FACE);

	glBindVertexArray(0);

	glUseProgram(0);
	g_textureManager.unbindTexture();

	m_vertices.clear();
}