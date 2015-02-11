#include "Sprite.h"



Sprite::Sprite()
{
	Globals& myGlobals = Globals::instance();
	width = 0;
	height = 0;
	x = 0;
	y = 0;

	//put vertex info first
	spriteID = new Vertex[6];
	//x pos of top right corner
	spriteID[0].fPositions[0] = width/2;
	//y position of the top corner
	spriteID[0].fPositions[1] = height/2;



	//x position of the left corner 
	spriteID[1].fPositions[0] = -(width/2);
	//y position of the left corner
	spriteID[1].fPositions[1] = -(height/2);
	//x position of the right corner
	spriteID[2].fPositions[0] = width/2;
	//y pos right corner
	spriteID[2].fPositions[1] = -(height/2);

	//opposite corner of the letter
	spriteID[3].fPositions[0] = spriteID[0].fPositions[0];
	spriteID[3].fPositions[1] = spriteID[0].fPositions[1];
	spriteID[4].fPositions[0] = spriteID[1].fPositions[0];
	spriteID[4].fPositions[1] = spriteID[1].fPositions[1];
	spriteID[5].fPositions[0] = spriteID[1].fPositions[0];
	spriteID[5].fPositions[1] = spriteID[0].fPositions[1];

	//sets color and other positions for the quad
	for (int i = 0; i < 6; i++)
	{
		spriteID[i].fPositions[2] = 0.0f;
		spriteID[i].fPositions[3] = 1.0f;
		spriteID[i].fColours[0] = 1.0f;
		spriteID[i].fColours[1] = 1.0f;
		spriteID[i].fColours[2] = 1.0f;
		spriteID[i].fColours[3] = 1.0f;
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
void Sprite::Draw()
{
	Globals& myGlobals = Globals::instance();

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
		memcpy(vBuffer, spriteID, sizeof(Vertex)* 6);
		//unmap and unbind buffer
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	


}

void Sprite::GetVar(float width, float height, float X, float Y)
{
	this->width = width;
	this->height = height;
	this->x = X;
	this->y = Y;
	SetXY();
}
void Sprite::Normalize(float sheetWidth, float sheetHeight)
{
	this->sheetWidth = sheetWidth;
	this->sheetHeight = sheetHeight;
	sheetNormWid = 1 / sheetWidth;
	sheetNormHgt = 1 / sheetHeight;
}

void Sprite::SetXY()
{
	//x position of lower right side of quad
	spriteID[0].fPositions[0] = x + width/2;
	spriteID[1].fPositions[0] = x - width/2;
	spriteID[2].fPositions[0] = x + width/2;
	//y pos
	spriteID[0].fPositions[1] = y + height / 2;
	spriteID[1].fPositions[1] = y - height / 2;
	spriteID[2].fPositions[1] = y - height / 2;
	spriteID[3].fPositions[0] = spriteID[0].fPositions[0];
	spriteID[3].fPositions[1] = spriteID[0].fPositions[1];
	spriteID[4].fPositions[0] = spriteID[1].fPositions[0];
	spriteID[4].fPositions[1] = spriteID[1].fPositions[1];
	spriteID[5].fPositions[0] = spriteID[1].fPositions[0];
	spriteID[5].fPositions[1] = spriteID[0].fPositions[1];
}

void Sprite::Animate()
{
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
	switch (currentFrame)
	{
	case Frame0:
		spriteID[0].fUVs[0] = 0.08f; //topright of the triangle
		spriteID[0].fUVs[1] = 1.0f;

		spriteID[2].fUVs[0] = 0.08f;//bottom right
		spriteID[2].fUVs[1] = 0.00f;

		spriteID[3].fUVs[0] = 0.08f; //upper right
		spriteID[3].fUVs[1] = 1.0f;

		spriteID[1].fUVs[0] = 0.0f; //bottom left
		spriteID[1].fUVs[1] = 0.0f;

		spriteID[4].fUVs[0] = 0.0f; // bottom left corner
		spriteID[4].fUVs[1] = 0.0f;

		spriteID[5].fUVs[0] = 0.0f; // upper left corner
		spriteID[5].fUVs[1] = 1.0f;
		if (FrameHandler > 0.1)
		{
			currentFrame = Frame1;
			FrameHandler = 0;
		}
		break;
	case Frame1:

		spriteID[0].fUVs[0] = 0.16f; //topright of the triangle
		spriteID[0].fUVs[1] = 1.0f;

		spriteID[2].fUVs[0] = 0.16f; //bottom right
		spriteID[2].fUVs[1] = 0.00f;

		spriteID[3].fUVs[0] = 0.16f; //upper right
		spriteID[3].fUVs[1] = 1.0f;

		spriteID[1].fUVs[0] = 0.08f; //bottom left
		spriteID[1].fUVs[1] = 0.0f;

		spriteID[4].fUVs[0] = 0.08f; // bottom left corner
		spriteID[4].fUVs[1] = 0.0f;

		spriteID[5].fUVs[0] = 0.08f; // upper left corner
		spriteID[5].fUVs[1] = 1.0f;
		if (FrameHandler > 0.1)
		{
			currentFrame = Frame2;
			FrameHandler = 0;
		}
		break;

	case Frame2:

		spriteID[0].fUVs[0] = 0.24f; //topright of the triangle
		spriteID[0].fUVs[1] = 1.0f;

		spriteID[2].fUVs[0] = 0.24f; //bottom right
		spriteID[2].fUVs[1] = 0.00f;

		spriteID[3].fUVs[0] = 0.24f; //upper right
		spriteID[3].fUVs[1] = 1.0f;

		spriteID[1].fUVs[0] = 0.16f; //bottom left
		spriteID[1].fUVs[1] = 0.0f;

		spriteID[4].fUVs[0] = 0.16f; // bottom left corner
		spriteID[4].fUVs[1] = 0.0f;

		spriteID[5].fUVs[0] = 0.16f; // upper left corner
		spriteID[5].fUVs[1] = 1.0f;

		if (FrameHandler > 0.1)
		{
			currentFrame = Frame3;
			FrameHandler = 0;

		}
		break;

	case Frame3:

		spriteID[0].fUVs[0] = 0.33f; //topright of the triangle
		spriteID[0].fUVs[1] = 1.0f;

		spriteID[2].fUVs[0] = 0.33f; //bottom right
		spriteID[2].fUVs[1] = 0.00f;

		spriteID[3].fUVs[0] = 0.33f; //upper right
		spriteID[3].fUVs[1] = 1.0f;

		spriteID[1].fUVs[0] = 0.25f; //bottom left
		spriteID[1].fUVs[1] = 0.0f;

		spriteID[4].fUVs[0] = 0.25f; // bottom left corner
		spriteID[4].fUVs[1] = 0.0f;

		spriteID[5].fUVs[0] = 0.25f; // upper left corner
		spriteID[5].fUVs[1] = 1.0f;
		if (FrameHandler > 0.1)
		{
			currentFrame = Frame4;
			FrameHandler = 0;

		}
		break;

	case Frame4:
		spriteID[0].fUVs[0] = 0.42f; //topright of the triangle
		spriteID[0].fUVs[1] = 1.0f;

		spriteID[2].fUVs[0] = 0.42f; //bottom right
		spriteID[2].fUVs[1] = 0.00f;

		spriteID[3].fUVs[0] = 0.42f; //upper right
		spriteID[3].fUVs[1] = 1.0f;

		spriteID[1].fUVs[0] = 0.34f; //bottom left
		spriteID[1].fUVs[1] = 0.0f;

		spriteID[4].fUVs[0] = 0.34f; // bottom left corner
		spriteID[4].fUVs[1] = 0.0f;

		spriteID[5].fUVs[0] = 0.34f; // upper left corner
		spriteID[5].fUVs[1] = 1.0f;
		if (FrameHandler > 0.1)
		{
			currentFrame = Frame5;
			FrameHandler = 0;

		}
		break;
	case Frame5:

		spriteID[0].fUVs[0] = 0.5f; //topright of the triangle
		spriteID[0].fUVs[1] = 1.0f;

		spriteID[2].fUVs[0] = 0.5f; //bottom right
		spriteID[2].fUVs[1] = 0.00f;

		spriteID[3].fUVs[0] = 0.5f; //upper right
		spriteID[3].fUVs[1] = 1.0f;

		spriteID[1].fUVs[0] = 0.425f; //bottom left
		spriteID[1].fUVs[1] = 0.0f;

		spriteID[4].fUVs[0] = 0.425f; // bottom left corner
		spriteID[4].fUVs[1] = 0.0f;

		spriteID[5].fUVs[0] = 0.425f; // upper left corner
		spriteID[5].fUVs[1] = 1.0f;
		if (FrameHandler > 0.1)
		{
			currentFrame = Frame6;
			FrameHandler = 0;

		}
		break;

	case Frame6:

		spriteID[0].fUVs[0] = 0.58f;
		spriteID[0].fUVs[1] = 1.0f;

		spriteID[2].fUVs[0] = 0.58f;
		spriteID[2].fUVs[1] = 0.00f;

		spriteID[3].fUVs[0] = 0.58f;
		spriteID[3].fUVs[1] = 1.0f;

		spriteID[1].fUVs[0] = 0.5f;
		spriteID[1].fUVs[1] = 0.0f;

		spriteID[4].fUVs[0] = 0.5f;
		spriteID[4].fUVs[1] = 0.0f;

		spriteID[5].fUVs[0] = 0.5f;
		spriteID[5].fUVs[1] = 1.0f;
		if (FrameHandler > 0.1)
		{
			currentFrame = Frame7;
			FrameHandler = 0;

		}
		break;

	case Frame7:

		spriteID[0].fUVs[0] = 0.66f;
		spriteID[0].fUVs[1] = 1.0f;

		spriteID[2].fUVs[0] = 0.66f;
		spriteID[2].fUVs[1] = 0.00f;

		spriteID[3].fUVs[0] = 0.66f;
		spriteID[3].fUVs[1] = 1.0f;

		spriteID[1].fUVs[0] = 0.58f;
		spriteID[1].fUVs[1] = 0.0f;

		spriteID[4].fUVs[0] = 0.58f;
		spriteID[4].fUVs[1] = 0.0f;

		spriteID[5].fUVs[0] = 0.58f;
		spriteID[5].fUVs[1] = 1.0f;

		if (FrameHandler > 0.1)
		{
			currentFrame = Frame8;
		FrameHandler = 0;

		}
		break;

	case Frame8:

		spriteID[0].fUVs[0] = 0.74f;
		spriteID[0].fUVs[1] = 1.0f;

		spriteID[2].fUVs[0] = 0.74f;
		spriteID[2].fUVs[1] = 0.00f;

		spriteID[3].fUVs[0] = 0.74f;
		spriteID[3].fUVs[1] = 1.0f;

		spriteID[1].fUVs[0] = 0.66f;
		spriteID[1].fUVs[1] = 0.0f;

		spriteID[4].fUVs[0] = 0.66f;
		spriteID[4].fUVs[1] = 0.0f;

		spriteID[5].fUVs[0] = 0.66f;
		spriteID[5].fUVs[1] = 1.0f;
		if (FrameHandler > 0.1)
		{
			currentFrame = Frame9;
			FrameHandler = 0;

		}
		break;

	case Frame9:
		spriteID[0].fUVs[0] = 0.83f;
		spriteID[0].fUVs[1] = 1.0f;

		spriteID[2].fUVs[0] = 0.83f;
		spriteID[2].fUVs[1] = 0.00f;

		spriteID[3].fUVs[0] = 0.83f;
		spriteID[3].fUVs[1] = 1.0f;

		spriteID[1].fUVs[0] = 0.75f;
		spriteID[1].fUVs[1] = 0.0f;

		spriteID[4].fUVs[0] = 0.75f;
		spriteID[4].fUVs[1] = 0.0f;

		spriteID[5].fUVs[0] = 0.75f;
		spriteID[5].fUVs[1] = 1.0f;

		if (FrameHandler > 0.1)
		{
			currentFrame = Frame10;
			FrameHandler = 0;

		}
		break;

	case Frame10:
		spriteID[0].fUVs[0] = 0.92f;
		spriteID[0].fUVs[1] = 1.0f;

		spriteID[2].fUVs[0] = 0.92f;
		spriteID[2].fUVs[1] = 0.00f;

		spriteID[3].fUVs[0] = 0.92f;
		spriteID[3].fUVs[1] = 1.0f;

		spriteID[1].fUVs[0] = 0.84f;
		spriteID[1].fUVs[1] = 0.0f;

		spriteID[4].fUVs[0] = 0.84f;
		spriteID[4].fUVs[1] = 0.0f;

		spriteID[5].fUVs[0] = 0.84f;
		spriteID[5].fUVs[1] = 1.0f;
		if (FrameHandler > 0.1)
		{
			currentFrame = Frame11;
			FrameHandler = 0;

		}
		break;

	case Frame11:
		spriteID[0].fUVs[0] = 1.0f; //topright of the triangle
		spriteID[0].fUVs[1] = 1.0f;

		spriteID[2].fUVs[0] = 1.0f; //bottom right
		spriteID[2].fUVs[1] = 0.00f;

		spriteID[3].fUVs[0] = 1.0f; //upper right
		spriteID[3].fUVs[1] = 1.0f;

		spriteID[1].fUVs[0] = 0.92f; //bottom left
		spriteID[1].fUVs[1] = 0.0f;

		spriteID[4].fUVs[0] = 0.92f; // bottom left corner
		spriteID[4].fUVs[1] = 0.0f;

		spriteID[5].fUVs[0] = 0.92f; // upper left corner
		spriteID[5].fUVs[1] = 1.0f;
		if (FrameHandler > 0.1)
		{
			currentFrame = Frame0;
			FrameHandler = 0;

		}
		break;

		
}
}

Sprite::~Sprite()
{
	delete spriteID;
}