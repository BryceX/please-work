#include <glew.h>
#include "wglew.h"
#include <GLFW/glfw3.h>
#include <vector>
#include <map>
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
#include "Animator.h"
#include <fstream>

int astConstant = 40;
float deltaTime = 0;
float timeSinceLastFrame = 0;



float currentTime = glfwGetTime();
float lastFrame = currentTime;



void GetDeltaTime()
{
	deltaTime + glfwGetTime();
	glfwSetTime(0);
}

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
	myGlobals.orthographicProjection = myGlobals.getOrtho(0, 600, 0, 600, 0, 100);
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
	Player myShip("sample.jpg");
	Stars myStars[50];
	Text myText[10];
	
	Asteroids myAsteroids[10];
	Animator test("mario.jpg"); 

	
	

	//set up the mapping of the screen to pixel co-ordinates. Try changing these values to see what happens.
	//loop until the user closes the window

	

	Text bbyPlz;

	while (!glfwWindowShouldClose(myGlobals.window))
	{
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		GetDeltaTime();
	

		currentTime = glfwGetTime();
		deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;

		
		test.Draw(300, 300, 50, 50, 12, deltaTime);
		//myShip.Move();
		myShip.Draw();
		

		bbyPlz.Draw(250.f, 300.f, std::string("Ayy lmao"));
		
		
	//	animatedSprite.Draw();
		//animatedSprite.Move();
		
		

			
		

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