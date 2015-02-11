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
#include "tinyxml2.h"
#include "Animator.h"
#include <fstream>

int astConstant = 40;
float deltaTime = 0;
float timeSinceLastFrame = 0;



float currentTime = glfwGetTime();
float lastFrame = currentTime;

struct FontLetter
{
	int id;
	int startX;
	int startY;
	int endX;
	int endY;
};

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
	Player myShip("zeroprofile.jpg");
	Stars myStars[50];
	Text myText[10];
	
	Asteroids myAsteroids[10];
	Animator animatedSprite;

	enum Frames
	{
		Frame0,
		Frame1,
		Frame2,
		Frame3,
		Frame4,
		Frame5,
		Frame6,
		Frame7,
		Frame8,
		Frame9,
		Frame10,
		Frame11
	};
	int currentFrame = Frame0;

	//set up the mapping of the screen to pixel co-ordinates. Try changing these values to see what happens.
	//loop until the user closes the window

	std::map<int, FontLetter> characterMap;

	tinyxml2::XMLDocument arialFont;
	arialFont.LoadFile("arial.fnt");
	tinyxml2::XMLElement *rootNode = arialFont.FirstChildElement("font");
	tinyxml2::XMLElement *currentNode = rootNode->FirstChildElement("chars");
	tinyxml2::XMLElement *charNode = currentNode->FirstChildElement("char");

	int idHolder = charNode->IntAttribute("id");

	FontLetter tempLetter = FontLetter();
	//for (int i = 0; i < 191; i++)
	

	

	

	idHolder = charNode->IntAttribute("id");


	


	while (charNode != nullptr)
	{
		tempLetter.id = charNode->IntAttribute("id");
		tempLetter.startX = charNode->IntAttribute("x");
		tempLetter.startY = charNode->IntAttribute("y");
		tempLetter.endX = tempLetter.startX + charNode->IntAttribute("width");
		tempLetter.endY = tempLetter.startY + charNode->IntAttribute("height");
		std::cout << tempLetter.id << std::endl;
		
		characterMap[tempLetter.id] = tempLetter;

		charNode = charNode->NextSiblingElement("char");
	}

	FontLetter letterA = characterMap['A'];


	while (!glfwWindowShouldClose(myGlobals.window))
	{
		//GetDeltaTime();
		animatedSprite.FrameHandler += deltaTime;

		currentTime = glfwGetTime();
		deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;



		std::cout << idHolder << std::endl;

		//draw code goes here
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		myShip.Move();
		myShip.Draw();

		float textCursor[2] = { 310, 310 };

		
		for (int i = 0; i < 10; i++)
		{

			myText[i].text[0].fPositions[0] = 310 + 10*i;// = 310;// + 10.0f * i;
			myText[i].text[1].fPositions[0] = myText[i].text[0].fPositions[0] - 10;// = 310;// + 10.0f * i;
			myText[i].text[2].fPositions[0] = myText[i].text[0].fPositions[0];// = 310;// + 10.0f * i;
			myText[i].Draw();
		}
		animatedSprite.Draw();
		myText[0].SetLetter(6);
		switch (currentFrame)
		{

		case Frame0:
			animatedSprite.text[0].fUVs[0] = 0.08f; //topright of the triangle
			animatedSprite.text[0].fUVs[1] = 1.0f;

			animatedSprite.text[2].fUVs[0] = 0.08f;//bottom right
			animatedSprite.text[2].fUVs[1] = 0.00f;

			animatedSprite.text[3].fUVs[0] = 0.08f; //upper right
			animatedSprite.text[3].fUVs[1] = 1.0f;

			animatedSprite.text[1].fUVs[0] = 0.0f; //bottom left
			animatedSprite.text[1].fUVs[1] = 0.0f;

			animatedSprite.text[4].fUVs[0] = 0.0f; // bottom left corner
			animatedSprite.text[4].fUVs[1] = 0.0f;

			animatedSprite.text[5].fUVs[0] = 0.0f; // upper left corner
			animatedSprite.text[5].fUVs[1] = 1.0f;
			if (animatedSprite.FrameHandler > 0.1)
			{
				currentFrame = Frame1;
				animatedSprite.FrameHandler = 0;
			}
			break;
		case Frame1:

			animatedSprite.text[0].fUVs[0] = 0.16f; //topright of the triangle
			animatedSprite.text[0].fUVs[1] = 1.0f;

			animatedSprite.text[2].fUVs[0] = 0.16f; //bottom right
			animatedSprite.text[2].fUVs[1] = 0.00f;

			animatedSprite.text[3].fUVs[0] = 0.16f; //upper right
			animatedSprite.text[3].fUVs[1] = 1.0f;

			animatedSprite.text[1].fUVs[0] = 0.08f; //bottom left
			animatedSprite.text[1].fUVs[1] = 0.0f;

			animatedSprite.text[4].fUVs[0] = 0.08f; // bottom left corner
			animatedSprite.text[4].fUVs[1] = 0.0f;

			animatedSprite.text[5].fUVs[0] = 0.08f; // upper left corner
			animatedSprite.text[5].fUVs[1] = 1.0f;
			if (animatedSprite.FrameHandler > 0.1)
			{
				currentFrame = Frame2;
				animatedSprite.FrameHandler = 0;
			}
			break;

		case Frame2:

			animatedSprite.text[0].fUVs[0] = 0.24f; //topright of the triangle
			animatedSprite.text[0].fUVs[1] = 1.0f;

			animatedSprite.text[2].fUVs[0] = 0.24f; //bottom right
			animatedSprite.text[2].fUVs[1] = 0.00f;

			animatedSprite.text[3].fUVs[0] = 0.24f; //upper right
			animatedSprite.text[3].fUVs[1] = 1.0f;

			animatedSprite.text[1].fUVs[0] = 0.16f; //bottom left
			animatedSprite.text[1].fUVs[1] = 0.0f;

			animatedSprite.text[4].fUVs[0] = 0.16f; // bottom left corner
			animatedSprite.text[4].fUVs[1] = 0.0f;

			animatedSprite.text[5].fUVs[0] = 0.16f; // upper left corner
			animatedSprite.text[5].fUVs[1] = 1.0f;

			if (animatedSprite.FrameHandler > 0.1)
			{
				currentFrame = Frame3;
				animatedSprite.FrameHandler = 0;

			}
			break;

		case Frame3:

			animatedSprite.text[0].fUVs[0] = 0.33f; //topright of the triangle
			animatedSprite.text[0].fUVs[1] = 1.0f;

			animatedSprite.text[2].fUVs[0] = 0.33f; //bottom right
			animatedSprite.text[2].fUVs[1] = 0.00f;

			animatedSprite.text[3].fUVs[0] = 0.33f; //upper right
			animatedSprite.text[3].fUVs[1] = 1.0f;

			animatedSprite.text[1].fUVs[0] = 0.25f; //bottom left
			animatedSprite.text[1].fUVs[1] = 0.0f;

			animatedSprite.text[4].fUVs[0] = 0.25f; // bottom left corner
			animatedSprite.text[4].fUVs[1] = 0.0f;

			animatedSprite.text[5].fUVs[0] = 0.25f; // upper left corner
			animatedSprite.text[5].fUVs[1] = 1.0f;
			if (animatedSprite.FrameHandler > 0.1)
			{
				currentFrame = Frame4;
				animatedSprite.FrameHandler = 0;

			}
			break;

		case Frame4:
			animatedSprite.text[0].fUVs[0] = 0.42f; //topright of the triangle
			animatedSprite.text[0].fUVs[1] = 1.0f;

			animatedSprite.text[2].fUVs[0] = 0.42f; //bottom right
			animatedSprite.text[2].fUVs[1] = 0.00f;

			animatedSprite.text[3].fUVs[0] = 0.42f; //upper right
			animatedSprite.text[3].fUVs[1] = 1.0f;

			animatedSprite.text[1].fUVs[0] = 0.34f; //bottom left
			animatedSprite.text[1].fUVs[1] = 0.0f;

			animatedSprite.text[4].fUVs[0] = 0.34f; // bottom left corner
			animatedSprite.text[4].fUVs[1] = 0.0f;

			animatedSprite.text[5].fUVs[0] = 0.34f; // upper left corner
			animatedSprite.text[5].fUVs[1] = 1.0f;
			if (animatedSprite.FrameHandler > 0.1)
			{
				currentFrame = Frame5;
				animatedSprite.FrameHandler = 0;

			}
			break;

		case Frame5:

			animatedSprite.text[0].fUVs[0] = 0.5f; //topright of the triangle
			animatedSprite.text[0].fUVs[1] = 1.0f;

			animatedSprite.text[2].fUVs[0] = 0.5f; //bottom right
			animatedSprite.text[2].fUVs[1] = 0.00f;

			animatedSprite.text[3].fUVs[0] = 0.5f; //upper right
			animatedSprite.text[3].fUVs[1] = 1.0f;

			animatedSprite.text[1].fUVs[0] = 0.425f; //bottom left
			animatedSprite.text[1].fUVs[1] = 0.0f;

			animatedSprite.text[4].fUVs[0] = 0.425f; // bottom left corner
			animatedSprite.text[4].fUVs[1] = 0.0f;

			animatedSprite.text[5].fUVs[0] = 0.425f; // upper left corner
			animatedSprite.text[5].fUVs[1] = 1.0f;
			if (animatedSprite.FrameHandler > 0.1)
			{
				currentFrame = Frame6;
				animatedSprite.FrameHandler = 0;

			}
			break;

		case Frame6:

			animatedSprite.text[0].fUVs[0] = 0.58f; //topright of the triangle
			animatedSprite.text[0].fUVs[1] = 1.0f;

			animatedSprite.text[2].fUVs[0] = 0.58f; //bottom right
			animatedSprite.text[2].fUVs[1] = 0.00f;

			animatedSprite.text[3].fUVs[0] = 0.58f; //upper right
			animatedSprite.text[3].fUVs[1] = 1.0f;

			animatedSprite.text[1].fUVs[0] = 0.5f; //bottom left
			animatedSprite.text[1].fUVs[1] = 0.0f;

			animatedSprite.text[4].fUVs[0] = 0.5f; // bottom left corner
			animatedSprite.text[4].fUVs[1] = 0.0f;

			animatedSprite.text[5].fUVs[0] = 0.5f; // upper left corner
			animatedSprite.text[5].fUVs[1] = 1.0f;
			if (animatedSprite.FrameHandler > 0.1)
			{
				currentFrame = Frame7;
				animatedSprite.FrameHandler = 0;

			}
			break;

		case Frame7:

			animatedSprite.text[0].fUVs[0] = 0.66f; //topright of the triangle
			animatedSprite.text[0].fUVs[1] = 1.0f;

			animatedSprite.text[2].fUVs[0] = 0.66f; //bottom right
			animatedSprite.text[2].fUVs[1] = 0.00f;

			animatedSprite.text[3].fUVs[0] = 0.66f; //upper right
			animatedSprite.text[3].fUVs[1] = 1.0f;

			animatedSprite.text[1].fUVs[0] = 0.58f; //bottom left
			animatedSprite.text[1].fUVs[1] = 0.0f;

			animatedSprite.text[4].fUVs[0] = 0.58f; // bottom left corner
			animatedSprite.text[4].fUVs[1] = 0.0f;

			animatedSprite.text[5].fUVs[0] = 0.58f; // upper left corner
			animatedSprite.text[5].fUVs[1] = 1.0f;

			if (animatedSprite.FrameHandler > 0.1)
			{
				currentFrame = Frame8;
				animatedSprite.FrameHandler = 0;

			}
			break;

		case Frame8:

			animatedSprite.text[0].fUVs[0] = 0.74f; //topright of the triangle
			animatedSprite.text[0].fUVs[1] = 1.0f;

			animatedSprite.text[2].fUVs[0] = 0.74f; //bottom right
			animatedSprite.text[2].fUVs[1] = 0.00f;

			animatedSprite.text[3].fUVs[0] = 0.74f; //upper right
			animatedSprite.text[3].fUVs[1] = 1.0f;

			animatedSprite.text[1].fUVs[0] = 0.66f; //bottom left
			animatedSprite.text[1].fUVs[1] = 0.0f;

			animatedSprite.text[4].fUVs[0] = 0.66f; // bottom left corner
			animatedSprite.text[4].fUVs[1] = 0.0f;

			animatedSprite.text[5].fUVs[0] = 0.66f; // upper left corner
			animatedSprite.text[5].fUVs[1] = 1.0f;
			if (animatedSprite.FrameHandler > 0.1)
			{
				currentFrame = Frame9;
				animatedSprite.FrameHandler = 0;

			}
			break;

		case Frame9:
			animatedSprite.text[0].fUVs[0] = 0.83f; //topright of the triangle
			animatedSprite.text[0].fUVs[1] = 1.0f;

			animatedSprite.text[2].fUVs[0] = 0.83f; //bottom right
			animatedSprite.text[2].fUVs[1] = 0.00f;

			animatedSprite.text[3].fUVs[0] = 0.83f; //upper right
			animatedSprite.text[3].fUVs[1] = 1.0f;

			animatedSprite.text[1].fUVs[0] = 0.75f; //bottom left
			animatedSprite.text[1].fUVs[1] = 0.0f;

			animatedSprite.text[4].fUVs[0] = 0.75f; // bottom left corner
			animatedSprite.text[4].fUVs[1] = 0.0f;

			animatedSprite.text[5].fUVs[0] = 0.75f; // upper left corner
			animatedSprite.text[5].fUVs[1] = 1.0f;

			if (animatedSprite.FrameHandler > 0.1)
			{
				currentFrame = Frame10;
				animatedSprite.FrameHandler = 0;

			}
			break;

		case Frame10:
			animatedSprite.text[0].fUVs[0] = 0.92f; //topright of the triangle
			animatedSprite.text[0].fUVs[1] = 1.0f;

			animatedSprite.text[2].fUVs[0] = 0.92f; //bottom right
			animatedSprite.text[2].fUVs[1] = 0.00f;

			animatedSprite.text[3].fUVs[0] = 0.92f; //upper right
			animatedSprite.text[3].fUVs[1] = 1.0f;

			animatedSprite.text[1].fUVs[0] = 0.84f; //bottom left
			animatedSprite.text[1].fUVs[1] = 0.0f;

			animatedSprite.text[4].fUVs[0] = 0.84f; // bottom left corner
			animatedSprite.text[4].fUVs[1] = 0.0f;

			animatedSprite.text[5].fUVs[0] = 0.84f; // upper left corner
			animatedSprite.text[5].fUVs[1] = 1.0f;
			if (animatedSprite.FrameHandler > 0.1)
			{
				currentFrame = Frame11;
				animatedSprite.FrameHandler = 0;

			}
			break;

		case Frame11:
			animatedSprite.text[0].fUVs[0] = 1.0f; //topright of the triangle
			animatedSprite.text[0].fUVs[1] = 1.0f;

			animatedSprite.text[2].fUVs[0] = 1.0f; //bottom right
			animatedSprite.text[2].fUVs[1] = 0.00f;

			animatedSprite.text[3].fUVs[0] = 1.0f; //upper right
			animatedSprite.text[3].fUVs[1] = 1.0f;

			animatedSprite.text[1].fUVs[0] = 0.92f; //bottom left
			animatedSprite.text[1].fUVs[1] = 0.0f;

			animatedSprite.text[4].fUVs[0] = 0.92f; // bottom left corner
			animatedSprite.text[4].fUVs[1] = 0.0f;

			animatedSprite.text[5].fUVs[0] = 0.92f; // upper left corner
			animatedSprite.text[5].fUVs[1] = 1.0f;
			if (animatedSprite.FrameHandler > 0.1)
			{
				currentFrame = Frame0;
				animatedSprite.FrameHandler = 0;

			}
			break;

			/*{
				myText[i].Draw();
				for (int j = 0; j < 6; j++)
				{
				myText[j].fPositions[0]
				}*/
		}

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