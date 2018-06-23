// ---------------------------------------------------------------------------
// Project Name		:	Cage Implementation
// File Name		:	Math2D.c
// Author			:	Antoine Abi Chacra
// Creation Date	:	2008/01/31
// Purpose			:	implementation of the Math Functions
// History			:
// - 2015/12/10		:	Implemented C style component based architecture 
// ---------------------------------------------------------------------------

/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology.
File Name: phantomengine.cpp
Purpose: Game Engine  Project Implementation for game engine
Language: C++ Visual Studio Enterprise 2015
Platform: Microsoft <R> C/C++ Optimizing Compiler Version 19.00.24210 Windows7
Project: CS529_rohit.tolety_5
Author: Rohit Tolety rohit.tolety 60000917
Creation date: 17th Dec 2017
- End Header --------------------------------------------------------*/




#include "sprite.h"
//#include "component.h"
#include "stdio.h"
#include <cstring>
#include <string>
#include "phantomengine.h"
#include "stb_image.h"
#include <iostream>


class gameobject;

int texturecoordinatestrid = 2 * sizeof(float);
GLuint bufferIDs[3];

extern gameobject* ship;


sprite::sprite() : component(COMPONENT_TYPES :: COMPONENT_SPRITE)
{
	
}


sprite::~sprite()
{
	//delete msurface;
}

void sprite::update(void)
{
	

}

void sprite::draw() {

	if (mpowner->get_is_active())
	{
		glBindVertexArray(VAO);
		glBindTexture(GL_TEXTURE_2D, texture);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);		
	}
}


void sprite::Buffer()
{
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
}


void sprite::serialize(FILE **fp)
{
	

	//------------------------------------------------------------------------------------------------------------

	// generate buffers and store data make a matrix as well which stores S*R*T values
	//gen vbo and vao by using genvbo
	float x = 0.0f;



	//New coordinates


	float ship[] =
	{ 0.15f, 0.15f, 0.0f,   1.0f, 0.0f, 0.0f,  1.0f, 1.0f,   // top right
		0.15f, -0.15f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,   // bottom right
	 -0.15f, -0.15f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,   // bottom left
	 -0.15f, 0.15f, 0.0f,   1.0f, 1.0f, 0.0f,  0.0f, 1.0f    // top left 
	};

	float bullet[] =
	{   0.08f, 0.08f, 0.0f,   1.0f, 0.0f, 0.0f,  1.0f, 1.0f,   // top right
		0.1f, -0.1f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,   // bottom right
		-0.1f, -0.1f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,   // bottom left
		-0.1f, 0.1f, 0.0f,   1.0f, 1.0f, 0.0f,  0.0f, 1.0f    // top left 
	};


	float asteroid[] =
	{ 0.11f, 0.11f, 0.0f,   1.0f, 0.0f, 0.0f,  1.0f, 1.0f,   // top right
		0.11f, -0.11f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,   // bottom right
		-0.11f, -0.11f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,   // bottom left
		-0.11f, 0.11f, 0.0f,   1.0f, 1.0f, 0.0f,  0.0f, 1.0f    // top left 
	};

	float missile[] =
	{   0.08f, 0.08f, 0.0f,   1.0f, 0.0f, 0.0f,  1.0f, 1.0f,   // top right
		0.08f, -0.08f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,   // bottom right
		-0.08f, -0.08f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,   // bottom left
		-0.08f, 0.08f, 0.0f,   1.0f, 1.0f, 0.0f,  0.0f, 1.0f    // top left 
	};

/*	float start_screen[] =
	{ 1.0f,1.0f, 0.0f,   1.0f, 0.0f, 0.0f,  1.0f, 1.0f,   // top right
		1.0f, -1.0f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,   // bottom right
		-1.0f, -1.0f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,   // bottom left
		-1.0f, 1.0f, 0.0f,   1.0f, 1.0f, 0.0f,  0.0f, 1.0f    // top left 
	};



	float end_screen[] =
	{ 1.0f,1.0f, 0.0f,   1.0f, 0.0f, 0.0f,  1.0f, 1.0f,   // top right
		1.0f, -1.0f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,   // bottom right
		-1.0f, -1.0f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,   // bottom left
		-1.0f, 1.0f, 0.0f,   1.0f, 1.0f, 0.0f,  0.0f, 1.0f    // top left 
	};
	*/



	unsigned int indeces[] = {

		0,1,3,
		1,2,3
	};


	
	char imagename[256];
	memset(imagename, 0, 256 * sizeof(char));


		


	fscanf(*fp, "%s\n", imagename);
	if (0==strcmp(imagename, "Triangle"))
	{
		
		this->Buffer();

		glBufferData(GL_ARRAY_BUFFER, sizeof(ship), ship, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indeces),indeces, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, false, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, false, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		//enable textures
		glVertexAttribPointer(2, 2, GL_FLOAT, false, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);


		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);


		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//load and generate the texture
		int width, height, nrchannels;
		unsigned  char* data = stbi_load("spaceship_purple_black.png", &width, &height, &nrchannels, 0);


		glPixelStorei(GL_UNPACK_ALIGNMENT, nrchannels);

		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load ship" << std::endl;
		}
		stbi_image_free(data);


	
	}
	
	else if (0 == strcmp(imagename, "Bullet"))
	{
		
		this->Buffer();

		glBufferData(GL_ARRAY_BUFFER, sizeof(bullet), bullet, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeces), indeces, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, false, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, false, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		//enable textures
		glVertexAttribPointer(2, 2, GL_FLOAT, false, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);


		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);


		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//load and generate the texture
		int width, height, nrchannels;
		unsigned  char* data = stbi_load("bulletfinal.png", &width, &height, &nrchannels, 0);


		glPixelStorei(GL_UNPACK_ALIGNMENT, nrchannels);

		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load Bullet" << std::endl;
		}
		stbi_image_free(data);

		




	}
		
	else if (0 == strcmp(imagename, "Asteroid"))
	{
		

		this->Buffer();

		glBufferData(GL_ARRAY_BUFFER, sizeof(asteroid), asteroid, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeces), indeces, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, false, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, false, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		//enable textures
		glVertexAttribPointer(2, 2, GL_FLOAT, false, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);


		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);


		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//load and generate the texture
		int width, height, nrchannels;
		unsigned  char* data = stbi_load("asteroid_black.png", &width, &height, &nrchannels, 0);


		glPixelStorei(GL_UNPACK_ALIGNMENT, nrchannels);

		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load asteroid" << std::endl;
		}
		stbi_image_free(data);


	}
	
	else if (0 == strcmp(imagename, "Missile1"))
	{
		this->Buffer();

		glBufferData(GL_ARRAY_BUFFER, sizeof(missile), missile, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeces), indeces, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, false, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, false, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		//enable textures
		glVertexAttribPointer(2, 2, GL_FLOAT, false, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);


		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);


		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//load and generate the texture
		int width, height, nrchannels;
		unsigned  char* data = stbi_load("missile_black3.png", &width, &height, &nrchannels, 0);


		glPixelStorei(GL_UNPACK_ALIGNMENT, nrchannels);

		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load missile" << std::endl;
		}
		stbi_image_free(data);





		
	}
	
}




//no need

void sprite::End_screen()
{
	float end_screen[] =
	{ 1.0f,1.0f, 0.0f,   1.0f, 0.0f, 0.0f,  1.0f, 1.0f,   // top right
		1.0f, -1.0f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,   // bottom right
		-1.0f, -1.0f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,   // bottom left
		-1.0f, 1.0f, 0.0f,   1.0f, 1.0f, 0.0f,  0.0f, 1.0f    // top left 
	};


	unsigned int indeces[] = {

		0,1,3,
		1,2,3
	};



}