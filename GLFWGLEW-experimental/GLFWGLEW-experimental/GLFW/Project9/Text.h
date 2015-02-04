#pragma once
#include <glew.h>
#include "wglew.h"
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include "Globals.h"
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
	float screenSize;
	float offSet;
	float uvOffSet;
	float trueOffSet;
	int letter;
	int column;
	int row;

	Text();
	~Text();
};