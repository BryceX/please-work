#pragma once
#include <glew.h>
#include "wglew.h"
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include "Globals.h"
#include <string>
class Sprite
{
public:
	void Draw();
	Vertex* spriteID;
	GLuint uiVBOText;
	GLuint uiIBOText;
	GLuint  uiProgramTextured;
	GLuint  uiTextureId;
	
	void GetVar(float width, float height, float X, float Y);
	void SetXY();
	float screenSize;
	float offSet;
	float uvOffSet;
	float trueOffSet;
	float FrameHandler;
	int id;
	int x;
	int y;
	int width;
	int height;


	Sprite();
	~Sprite();
};