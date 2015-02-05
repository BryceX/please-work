#include <glew.h>
#include "wglew.h"
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <fstream>
#include <SOIL.h>
#include <iostream>
#include <time.h>
#include "Globals.h"
#include "Player.h"
#include "Asteroids.h"
#include "Stars.h"
#include "Text.h"
#include "tinyxml2.h"
int xPos = 450;
int astConstant = 40;

int main()
{
	Globals& myGlobals = Globals::instance();
	srand(time(NULL));
	// init GLFW
	if (!glfwInit())
	{
		return -1;
	}
	myGlobals.window = glfwCreateWindow(600, 600, "Hello World", NULL, NULL);
	myGlobals.orthographicProjection = myGlobals.getOrtho(0, 1024, 0, 720, 0, 100);
	if (!myGlobals.window)
	{
		glfwTerminate();
		return -1;
	}

	//make the window's context current
	glfwMakeContextCurrent(myGlobals.window);

	//ÅEÅEnsert this into the main.cpp example given in the setting up GLFW section ÅE
	//once the glfw window has been created and after 'glfwMakeContextCurrent(window);'
	// start GLEW
	if (glewInit() != GLEW_OK)
	{
		// OpenGL didn't start-up! shutdown GLFW and return an error code
		glfwTerminate();
		return -1;
	}
	//Initialise GLFW
	Player myShip;
	Stars myStars[50];
	Text myText;
	Asteroids myAsteroids[10];
	

	
	//set up the mapping of the screen to pixel co-ordinates. Try changing these values to see what happens.
	myGlobals.orthographicProjection = myGlobals.getOrtho(0, 1024, 0, 720, 0, 100);
	//loop until the user closes the window

	
	while (!glfwWindowShouldClose(myGlobals.window))
	{
		//draw code goes here
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		myShip.Move();
		myShip.Draw();
		myText.Draw();
		for (int i = 0; i < 10; i++)
		/*{
			myText[i].Draw();
			for (int j = 0; j < 6; j++)
			{
				myText[j].fPositions[0]
			}
		}*/
		
		for (int i = 0; i < 10; i++)
		{
			myAsteroids[i].Draw();
		}

		for (int i = 0; i < 50; i++)
		{
		myStars[i].Draw();
		}
		
		
		glfwSwapBuffers(myGlobals.window);

		if (glfwGetKey(myGlobals.window, GLFW_KEY_ESCAPE))
		{
			break;
		}

		//poll for and process events
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}