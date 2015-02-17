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
	void Draw(float xPos, float yPos);
	float xPos;
	float yPos;
	Vertex* text;
	GLuint uiVBOText;
	GLuint uiIBOText;
	GLuint  uiProgramTextured;
	GLuint  uiTextureId;
	void GetLetterInfo(int id, float x1, float y1,float x2, float y2, float width, float height);

	int id;
	float x1;
	float y1;
	float x2;
	float y2;
	float width;
	float height;



	Text();
	~Text();
};