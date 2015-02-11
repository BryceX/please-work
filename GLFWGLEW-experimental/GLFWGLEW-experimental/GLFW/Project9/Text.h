#pragma once
#include <glew.h>
#include "wglew.h"
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include "Globals.h"
#include <string>
class Text
{
public:
	void Draw();
	Vertex* text;
	GLuint uiVBOText;
	GLuint uiIBOText;
	GLuint  uiProgramTextured;
	GLuint  uiTextureId;
	void SetSize(float a_ScreenSize);
	void SetLetter(float a_ascii);
	float screenSize;
	float offSet;
	float uvOffSet;
	float trueOffSet;
	int column;
	int row;
	void GetLetterInfo(int id, int x, int y, int width, int height);

	int id;
	int x;
	int y;
	int width;
	int height;



	Text();
	~Text();
};