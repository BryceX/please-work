#pragma once
#include <glew.h>
#include "wglew.h"
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include "Globals.h"
#include <string>
class Animator
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
	float FrameHandler;
	

	Animator();
	~Animator();
};