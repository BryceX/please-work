#include "Animator.h"



Animator::Animator()
{
	//want to be able to input letters somewhere, have that convert to the corresponding
	//column and row, and all in a for loop somewhere or another
	//
	//
	//
	//
	Globals& myGlobals = Globals::instance();
	
	FrameHandler = 0;
	
	//put vertex info first
	sprite = new Vertex[6];
	//x pos of top right corner
	sprite[0].fPositions[0] = 0;
	//y position of the top corner
	sprite[0].fPositions[1] = 0;
	//x position of the left corner 
	sprite[1].fPositions[0] = 0;
	//y position of the left corner
	sprite[1].fPositions[1] = 0;
	//x position of the right corner
	sprite[2].fPositions[0] = 0;
	//y pos right corner
	sprite[2].fPositions[1] = 0;



	//opposite corner of the letter
	sprite[3].fPositions[0] = sprite[0].fPositions[0];
	sprite[3].fPositions[1] = sprite[0].fPositions[1];

	sprite[4].fPositions[0] = sprite[1].fPositions[0];
	sprite[4].fPositions[1] = sprite[1].fPositions[1];

	sprite[5].fPositions[0] = sprite[1].fPositions[0];
	sprite[5].fPositions[1] = sprite[0].fPositions[1];
	for (int i = 0; i < 6; i++)
	{
		sprite[i].fPositions[2] = 0.0f;
		sprite[i].fPositions[3] = 1.0f;
		sprite[i].fColours[0] = 1.0f;
		sprite[i].fColours[1] = 1.0f;
		sprite[i].fColours[2] = 1.0f;
		sprite[i].fColours[3] = 1.0f;
	}
	

	


	

/*for (int i = 0; i < 6; i++)
	{
	text[i].fUVs[0] += (0.077f*glfwGetTime());
	}*/

	//making buffers
	glGenBuffers(1, &uiVBOText);	// VBO
	glGenBuffers(1, &uiIBOText);	// IBO

	// make the shaders
	uiProgramTextured = myGlobals.CreateProgram("VertexShader.glsl", "TexturedFragmentShader.glsl");

	// load the texture
	int width = 50, height = 50, bpp = 4;
	uiTextureId = myGlobals.loadTexture("mario.png", width, height, bpp);


}
void Animator::Draw()
{
	Globals& myGlobals = Globals::instance();
	
	
		sprite[0].fUVs[0] = 0.08f;
		sprite[0].fUVs[1] = 1.0f;

		sprite[2].fUVs[0] = 0.08f;//bottom right
		sprite[2].fUVs[1] = 0.00f;

		sprite[3].fUVs[0] = 0.08f; //upper right
		sprite[3].fUVs[1] = 1.0f;

		sprite[1].fUVs[0] = 0.0f; //bottom left
		sprite[1].fUVs[1] = 0.0f;

		sprite[4].fUVs[0] = 0.0f; // bottom left corner
		sprite[4].fUVs[1] = 0.0f;

		sprite[5].fUVs[0] = 0.0f; // upper left corner
		sprite[5].fUVs[1] = 1.0f;
		if (FrameHandler > 0.1)
		{
			FrameHandler = 0;
		}
	
		/*
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
		break;*/
	
	
	

	// specify the shader program to be used for rendering
	glUseProgram(uiProgramTextured);
	// get the location of the MVP variable
	GLuint MatrixIDFlat = glGetUniformLocation(uiProgramTextured, "MVP");
	glBindTexture(GL_TEXTURE_2D, uiTextureId);				// sets up the texture that we gon use
	glBindBuffer(GL_ARRAY_BUFFER, uiVBOText);			// sets up the VBO we gon use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiIBOText);	// sets up the IBO we gon use
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// send the ortho to the shader
	glUniformMatrix4fv(MatrixIDFlat, 1, GL_FALSE, myGlobals.orthographicProjection);
	//enable the vertex array state, since we're sending in an array of vertices
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	//specify where our vertex array is, how many components each vertex has, 
	//the data type of each component and whether the data is normalised or not
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float)* 4));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float)* 8));
	//draw to the screen

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);				// clear the currently bound buffer for VBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);		// clear the currently bound buffer for IBO
	//swap front and back buffers
	glBindTexture(GL_TEXTURE_2D, 0);				// clear the currently bound buffer for texture
	//x position of the top corner



	// send data to the IBO
	if (uiIBOText != 0)
	{
		//bind IBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiIBOText);
		//allocate space for index info on the graphics card
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(char), NULL, GL_STATIC_DRAW);
		//get pointer to newly allocated space on the graphics card
		GLvoid* iBuffer = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
		//specify the order we'd like to draw our vertices.
		//In this case they are in sequential order
		for (int i = 0; i < 6; i++)
		{
			((char*)iBuffer)[i] = i;
		}
		//unmap and unbind
		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	// send data to the VBO
	if (uiVBOText != 0)
	{
		//bind VBO
		glBindBuffer(GL_ARRAY_BUFFER, uiVBOText);
		//allocate space for vertices on the graphics card
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* 6, NULL, GL_STATIC_DRAW);
		//get pointer to allocated space on the graphics card
		GLvoid* vBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		//copy data to graphics card
		memcpy(vBuffer, text, sizeof(Vertex)* 6);
		//unmap and unbind buffer
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}




}

void Animator::Move()

{
	Globals& myGlobals = Globals::instance();
	if (glfwGetKey(myGlobals.window, GLFW_KEY_W) == GLFW_PRESS)
	{
		//move forward
		for (int i = 0; i < 6; i++)
		{
			text[i].fPositions[1] += myGlobals.screenSize*.01f;
		}
		glBindBuffer(GL_ARRAY_BUFFER, uiVBOText);
		GLvoid* vBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		//copy data to graphics card
		memcpy(vBuffer, text, sizeof(Vertex) * 6);
		//unmap and unbind buffer
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	if (glfwGetKey(myGlobals.window, GLFW_KEY_S) == GLFW_PRESS)
	{
		//move forward
		for (int i = 0; i < 6; i++)
		{
			text[i].fPositions[1] -= myGlobals.screenSize*.01f;
		}
		glBindBuffer(GL_ARRAY_BUFFER, uiVBOText);
		GLvoid* vBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		//copy data to graphics card
		memcpy(vBuffer, text, sizeof(Vertex) * 6);
		//unmap and unbind buffer
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	if (glfwGetKey(myGlobals.window, GLFW_KEY_D) == GLFW_PRESS)
	{
		//move forward
		for (int i = 0; i < 6; i++)
		{
			text[i].fPositions[0] += myGlobals.screenSize*.01f;
		}
		glBindBuffer(GL_ARRAY_BUFFER, uiVBOText);
		GLvoid* vBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		//copy data to graphics card
		memcpy(vBuffer, text, sizeof(Vertex) * 6);
		//unmap and unbind buffer
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	if (glfwGetKey(myGlobals.window, GLFW_KEY_A) == GLFW_PRESS)
	{
		//move forward
		for (int i = 0; i < 6; i++)
		{
			text[i].fPositions[0] -= myGlobals.screenSize*.01f;
		}
		glBindBuffer(GL_ARRAY_BUFFER, uiVBOText);
		GLvoid* vBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		//copy data to graphics card
		memcpy(vBuffer, text, sizeof(Vertex) * 6);
		//unmap and unbind buffer
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}



Animator::~Animator()
{
	delete text;
}