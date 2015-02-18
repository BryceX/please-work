#include "Animator.h"



Animator::Animator(const char * texturePath)
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
	
	sprite[0].fPositions[1] = 0;// top position
	sprite[3].fPositions[1] = sprite[0].fPositions[1];
	sprite[5].fPositions[1] = sprite[0].fPositions[1];

	sprite[1].fPositions[1] = 0; //bottom position
	sprite[2].fPositions[1] = sprite[1].fPositions[1];
	sprite[4].fPositions[1] = sprite[1].fPositions[1];


	sprite[1].fPositions[0] = 0; // left side
	sprite[4].fPositions[0] = sprite[1].fPositions[0];
	sprite[5].fPositions[0] = sprite[1].fPositions[0];

	sprite[0].fPositions[0] = 0;//right side
	sprite[2].fPositions[0] = sprite[0].fPositions[0];
	sprite[3].fPositions[0] = sprite[0].fPositions[0];


	for (int i = 0; i < 6; i++)
	{
		sprite[i].fPositions[2] = 0.0f;
		sprite[i].fPositions[3] = 1.0f;
		sprite[i].fColours[0] = 1.0f;
		sprite[i].fColours[1] = 1.0f;
		sprite[i].fColours[2] = 1.0f;
		sprite[i].fColours[3] = 1.0f;
	}
	



	//making buffers
	glGenBuffers(1, &uiVBOText);	// VBO
	glGenBuffers(1, &uiIBOText);	// IBO

	// make the shaders
	uiProgramTextured = myGlobals.CreateProgram("VertexShader.glsl", "TexturedFragmentShader.glsl");

	// load the texture
	int width = 50, height = 50, bpp = 4;
	uiTextureId = myGlobals.loadTexture(texturePath, width, height, bpp);


}
void Animator::Draw(float x, float y, float width, float height, int frames, float deltaTime)
{
	//will only read sprite sheets left to right
	Globals& myGlobals = Globals::instance();
	
	//each side should be the same as the other parts of it or it will look derp

		

		sprite[0].fUVs[1] = 1.0f;// top
		sprite[3].fUVs[1] = sprite[0].fUVs[1]; 
		sprite[5].fUVs[1] = sprite[0].fUVs[1];

		sprite[1].fUVs[1] = 0.0f; //bottom
		sprite[2].fUVs[1] = sprite[1].fUVs[1];
		sprite[4].fUVs[1] = sprite[1].fUVs[1];

		sprite[1].fUVs[0] = 0.0f; // left side
		sprite[4].fUVs[0] = sprite[1].fUVs[0];
		sprite[5].fUVs[0] = sprite[1].fUVs[0];

		sprite[0].fUVs[0] = 1 / frames;//right side
		sprite[2].fUVs[0] = sprite[0].fUVs[0];
		sprite[3].fUVs[0] = sprite[0].fUVs[0];
		
		sprite[0].fPositions[1] = y + height / 2;// top position
		sprite[3].fPositions[1] = sprite[0].fPositions[1];
		sprite[5].fPositions[1] = sprite[0].fPositions[1];

		sprite[1].fPositions[1] = y - height / 2; //bottom position
		sprite[2].fPositions[1] = sprite[1].fPositions[1];
		sprite[4].fPositions[1] = sprite[1].fPositions[1];


		sprite[1].fPositions[0] = x - width / 2; // left side
		sprite[4].fPositions[0] = sprite[1].fPositions[0];
		sprite[5].fPositions[0] = sprite[1].fPositions[0];

		sprite[0].fPositions[0] = x + width / 2;//right side
		sprite[2].fPositions[0] = sprite[0].fPositions[0];
		sprite[3].fPositions[0] = sprite[0].fPositions[0];
		FrameHandler += deltaTime;

		if (FrameHandler > 0.2)
		{
		sprite[1].fUVs[0] += 1 / frames; // left side
		sprite[0].fUVs[0] += 1 / frames;//right side
		FrameHandler = 0;

		if (sprite[1].fUVs[0] > 1)
		{
			sprite[0].fUVs[0] = 1 / frames;
			sprite[1].fUVs[0] = 0.0f;
		}
		}
		

		
		
		

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
		memcpy(vBuffer, sprite, sizeof(Vertex)* 6);
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
			sprite[i].fPositions[1] += myGlobals.screenSize*.01f;
		}
		glBindBuffer(GL_ARRAY_BUFFER, uiVBOText);
		GLvoid* vBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		//copy data to graphics card
		memcpy(vBuffer, sprite, sizeof(Vertex)* 6);
		//unmap and unbind buffer
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	if (glfwGetKey(myGlobals.window, GLFW_KEY_S) == GLFW_PRESS)
	{
		//move forward
		for (int i = 0; i < 6; i++)
		{
			sprite[i].fPositions[1] -= myGlobals.screenSize*.01f;
		}
		glBindBuffer(GL_ARRAY_BUFFER, uiVBOText);
		GLvoid* vBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		//copy data to graphics card
		memcpy(vBuffer, sprite, sizeof(Vertex)* 6);
		//unmap and unbind buffer
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	if (glfwGetKey(myGlobals.window, GLFW_KEY_D) == GLFW_PRESS)
	{
		//move forward
		for (int i = 0; i < 6; i++)
		{
			sprite[i].fPositions[0] += myGlobals.screenSize*.01f;
		}
		glBindBuffer(GL_ARRAY_BUFFER, uiVBOText);
		GLvoid* vBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		//copy data to graphics card
		memcpy(vBuffer, sprite, sizeof(Vertex)* 6);
		//unmap and unbind buffer
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	if (glfwGetKey(myGlobals.window, GLFW_KEY_A) == GLFW_PRESS)
	{
		//move forward
		for (int i = 0; i < 6; i++)
		{
			sprite[i].fPositions[0] -= myGlobals.screenSize*.01f;
		}
		glBindBuffer(GL_ARRAY_BUFFER, uiVBOText);
		GLvoid* vBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		//copy data to graphics card
		memcpy(vBuffer, sprite, sizeof(Vertex)* 6);
		//unmap and unbind buffer
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}



Animator::~Animator()
{
	delete sprite;
}