#include "Text.h"



Text::Text()
{
	//want to be able to input letters somewhere, have that convert to the corresponding
	//column and row, and all in a for loop somewhere or another
	//
	//
	//
	//
	Globals& myGlobals = Globals::instance();
	//put vertex info first
	text = new Vertex[6];
	text[0].fPositions[0] = 0;
	//y position of the top corner
	text[0].fPositions[1] = 0;
	//x position of the left corner 
	text[1].fPositions[0] = 0;
	//y position of the left corner
	text[1].fPositions[1] = 0;
	//x position of the right corner
	text[2].fPositions[0] = 0;
	//y pos right corner
	text[2].fPositions[1] = 0;

	//opposite corner of the letter
	
	for (int i = 0; i < 6; i++)
	{
		text[i].fPositions[2] = 0.0f;
		text[i].fPositions[3] = 1.0f;
		text[i].fColours[0] = 1.0f;
		text[i].fColours[1] = 1.0f;
		text[i].fColours[2] = 1.0f;
		text[i].fColours[3] = 1.0f;
	}
	//set up the UVs

	text[0].fUVs[0] = 0; //topright of the triangle
	text[0].fUVs[1] = 0;

	text[2].fUVs[0] = 0; //bottom right
	text[2].fUVs[1] = 0;

	text[3].fUVs[0] = 0; //upper right
	text[3].fUVs[1] = 0;


	text[1].fUVs[0] = 0; //bottom left
	text[1].fUVs[1] = 0;

	text[4].fUVs[0] = 0; // bottom left corner
	text[4].fUVs[1] = 0;

	text[5].fUVs[0] = 0; // upper left corner
	text[5].fUVs[1] = 0;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (text[i].fUVs[j] < 0)
			{
				text[i].fUVs[j] = 0;
			}
			if (text[i].fUVs[j] > 1)
			{
				text[i].fUVs[j] = 1;
			}
		}
	}
	
	

	
	
	//making buffers
	glGenBuffers(1, &uiVBOText);	// VBO
	glGenBuffers(1, &uiIBOText);	// IBO

	// make the shaders
	uiProgramTextured = myGlobals.CreateProgram("VertexShader.glsl", "TexturedFragmentShader.glsl");

	// load the texture
	int width = 50, height = 50, bpp = 4;
	uiTextureId = myGlobals.loadTexture("arial_0.png", width, height, bpp);

	tinyxml2::XMLDocument arialFont;
	arialFont.LoadFile("arial.fnt");
	tinyxml2::XMLElement *rootNode = arialFont.FirstChildElement("font");
	tinyxml2::XMLElement *currentNode = rootNode->FirstChildElement("chars");
	tinyxml2::XMLElement *charNode = currentNode->FirstChildElement("char");

	int idHolder = charNode->IntAttribute("id");

	FontLetter tempLetter = FontLetter();
	//for (int i = 0; i < 191; i++)

	while (charNode != nullptr)
	{
		tempLetter.id = charNode->IntAttribute("id");
		tempLetter.startX = charNode->IntAttribute("x");
		tempLetter.startY = 256 - charNode->IntAttribute("y");
		tempLetter.endX = tempLetter.startX + charNode->IntAttribute("width");
		tempLetter.endY = tempLetter.startY - charNode->IntAttribute("height");
		tempLetter.width = tempLetter.endX - tempLetter.startX;
		tempLetter.height = tempLetter.endY - tempLetter.startY;
		tempLetter.xOffset = charNode->IntAttribute("xoffset");
		tempLetter.yOffset = charNode->IntAttribute("yoffset");

		characterMap[tempLetter.id] = tempLetter;

		charNode = charNode->NextSiblingElement("char");
	}
}

void Text::Draw(float xPos, float yPos, char theLetter)
{
	//must call GetLetterInfo before Drawing!!
	this->xPosi = xPos;
	this->yPosi = yPos;
	Globals& myGlobals = Globals::instance();

	FontLetter letter = characterMap[theLetter];


	text[0].fUVs[0] = letter.endX / 256; //topright of the triangle
	text[0].fUVs[1] = letter.endY / 256;

	text[2].fUVs[0] = letter.endX / 256; //bottom right
	text[2].fUVs[1] = letter.startY / 256;

	text[3].fUVs[0] = letter.endX / 256; //upper right
	text[3].fUVs[1] = letter.endY / 256;

	text[1].fUVs[0] = letter.startX / 256; //bottom left
	text[1].fUVs[1] = letter.startY / 256;

	text[4].fUVs[0] = letter.startX / 256; // bottom left corner
	text[4].fUVs[1] = letter.startY / 256;

	text[5].fUVs[0] = letter.startX / 256; // upper left corner
	text[5].fUVs[1] = letter.endY / 256;

	
	text[0].fPositions[0] = xPos + letter.width/2;
	//y position of the top right corner
	text[0].fPositions[1] = yPos+letter.height/2;
	//x position of the left corner 
	text[1].fPositions[0] = xPos-letter.width/2;
	//y position of the left corner
	text[1].fPositions[1] = yPos-letter.height/2;
	//x position of the right corner
	text[2].fPositions[0] = xPos+letter.width/2;
	//y pos right corner
	text[2].fPositions[1] = yPos-letter.height/2;

	
	//sets other half of triangle according to the first position
	text[3].fPositions[0] = text[0].fPositions[0];
	text[3].fPositions[1] = text[0].fPositions[1];
	text[4].fPositions[0] = text[1].fPositions[0];
	text[4].fPositions[1] = text[1].fPositions[1];
	text[5].fPositions[0] = text[1].fPositions[0];
	text[5].fPositions[1] = text[0].fPositions[1];

	// specify the shader program to be used for rendering
	glUseProgram(uiProgramTextured);
	// get the location of the MVP variable
	GLuint MatrixIDFlat = glGetUniformLocation(uiProgramTextured, "MVP");
	glBindTexture(GL_TEXTURE_2D, uiTextureId);				// sets up the texture that we gon use
	glBindBuffer(GL_ARRAY_BUFFER, uiVBOText);			// sets up the VBO we gon use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiIBOText);	// sets up the IBO we gon use
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//send the ortho to the shader
	glUniformMatrix4fv(MatrixIDFlat, 1, GL_FALSE, myGlobals.orthographicProjection);
	//enable the vertex array state, since we're sending in an array of vertices
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	//specify where our vertex array is, how many components each vertex has, 
	//the data type of each component and whether the data is normalised or not
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 4));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 8));
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
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 6, NULL, GL_STATIC_DRAW);
		//get pointer to allocated space on the graphics card
		GLvoid* vBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		//copy data to graphics card
		memcpy(vBuffer, text, sizeof(Vertex)* 6);
		//unmap and unbind buffer
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}




}

void Text::Draw(float xPos, float yPos, std::string sentence)
{
	for (int i = 0; i < sentence.length(); i++)
	{
		Draw(xPos, yPos - (characterMap[sentence[i]].yOffset)*.5 , sentence[i]);
		if (i < sentence.length())
		{
			xPos += (characterMap[sentence[i]].width/2);
			xPos += (characterMap[sentence[i + 1]].width / 2);
			
			
		}

		
	}
}

void Text::DrawNoOffSets(float xPos, float yPos, std::string sentence)
{
	for (int i = 0; i < sentence.length(); i++)
	{
		Draw(xPos, yPos, sentence[i]);
		if (i < sentence.length())
		{
			xPos += (characterMap[sentence[i]].width / 2);
			xPos += (characterMap[sentence[i + 1]].width / 2);
		}
	}
}


Text::~Text()
{
	delete text;
}