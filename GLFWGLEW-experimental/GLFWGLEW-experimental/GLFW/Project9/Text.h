#pragma once
#include <glew.h>
#include "wglew.h"
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include "Globals.h"
class Text
{
public:
	void Move();
	void Draw();
	Vertex* playerShip;
	GLuint uiVBOplayerShip;
	GLuint uiIBOplayerShip;
	GLuint  uiProgramTextured;
	GLuint  uiTextureId;
	Text();
	~Text();
};