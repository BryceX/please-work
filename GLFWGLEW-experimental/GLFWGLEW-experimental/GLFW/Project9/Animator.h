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
	void Draw(float x, float y, float width, float height, int frames, float deltaTime);
	void Move();
	Vertex* sprite;
	GLuint uiVBOText;
	GLuint uiIBOText;
	GLuint  uiProgramTextured;
	GLuint  uiTextureId;
	
	bool isAnimated = true;
	float FrameHandler;


	Animator();
	Animator(const char * texturePath);
	~Animator();
};