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
	void Move();
	Vertex* sprite;
	GLuint uiVBOText;
	GLuint uiIBOText;
	GLuint  uiProgramTextured;
	GLuint  uiTextureId;
	void SetSize(float a_ScreenSize);
	float xPos;
	float yPos;
	float frames;
	float width;
	float height;
	
	float FrameHandler;


	Animator();
	~Animator();
};