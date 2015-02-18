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
	float xOffset;
	float yOffset;
};

class Text
{
public:

	void Draw(float xPos, float yPos, char theLetter);
	void Draw(float xPos, float yPos, std::string sentence);
	void DrawNoOffSets(float xPos, float yPos, std::string sentence);
	float xPosi;
	float yPosi;
	Vertex* text;
	GLuint uiVBOText;
	GLuint uiIBOText;
	GLuint  uiProgramTextured;
	GLuint  uiTextureId;

	std::map<int, FontLetter> characterMap;

	Text();
	~Text();
};