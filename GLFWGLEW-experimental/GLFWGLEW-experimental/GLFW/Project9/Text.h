#pragma once
#include <glew.h>
#include "wglew.h"
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include "Globals.h"
#include <string>
#include <map>
#include "tinyxml2.h"

struct FontLetter
{
	int id;
	float startX;
	float startY;
	float endX;
	float endY;
	float width;
	float height;
};

class Text
{
public:

	void Draw(float xPos, float yPos, char theLetter);
	void Draw(float xPos, float yPos, std::string sentence);
	float xPos;
	float yPos;
	Vertex* text;
	GLuint uiVBOText;
	GLuint uiIBOText;
	GLuint  uiProgramTextured;
	GLuint  uiTextureId;

	std::map<int, FontLetter> characterMap;

	Text();
	~Text();
};