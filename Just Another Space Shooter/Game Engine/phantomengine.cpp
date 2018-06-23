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


#include <iostream>
#include "phantomengine.h"
#include "inputmanager.h"
#include "frc.h"
#include "GameObjectManager.h"
#include "gameobject.h"
#include "transform.h"
#include "sprite.h" 
#include "controller.h"
#include "component.h"
#include "updown.h"
#include "Body.h"
#include "ObjectFactory.h"
#include "Physicsmanager.h"
#include "Eventmanager.h"
#include "GL\glew.h"
#include "..\Dependencies\GLFW\glfw3.h"
//#include "gdiplus.h"
//#include "stb_image.h"
#include "Shader.h"
//#include "..\Dependencies\glut\glut\include\GL\glut.h"

#include <Windows.h>
#include <cstdio>

//#pragma comment(lib,"gdiplus.lib")

FILE _iob[] = { *stdin, *stdout, *stderr };

extern "C" FILE * __cdecl __iob_func(void)
{
	return _iob;
}

//Global Objects creation 

 rscmanager  *rscmgr = new rscmanager();
 inputmanager* pinputmanager = new inputmanager();
 frameratecontroller *pfrc = new frameratecontroller(60);
 GameObjectManager *pGOM = new GameObjectManager();
 gameobject *gameobj = new gameobject();
 ObjectFactory *objfactory = new ObjectFactory();
 Physicsmanager *phymgr = new Physicsmanager();
 EventManager *pEM = new EventManager();
 transform *ptrans = new transform();
 //opengl stuff
 //GLuint bufferIDs[3];

 int vertexnum = 3;
 int cordinatesPerPosition = 3;
 int cordinatesPerColor = 4;
 int cordinatesPertexturescordinates = 2;

 int positionstride = cordinatesPerPosition * sizeof(float);
 int colorstride = cordinatesPerColor * sizeof(float);
 int texturecoordinatestride = cordinatesPertexturescordinates * sizeof(float);
 gameobject* ship;
 gameobject* bullet;


 //window limits
 float  winMaxX = 1.0;
 float  winMaxY = 1.0;
 float  winMinX = -1.0;
 float  winMinY = -1.0f;


 bool gameactive = false;
 bool controlleractive = false;
 bool win = false;
 bool lose_scene = false;

 int playerlives = 4;
 int asteroid_count = 6;


 unsigned int VBO[2];
 unsigned int VAO[2];
 unsigned int texture;
 //float bullet[] = {

	// -0.42f,-0.42f,0.0f, //left
	// 0.42f,-0.42f,0.0f, //right
	// 0.0f,0.42f,0.0f,  //top

 //};
 //Shader S1("shipshader.vs", "shipshader.fs");

 //OpenGL implementation
 GLint gProgramID;


 SDL_Surface* pWindowSurface = NULL;

 //forward decleration
 //void wrap(gameobject* pinst);

 void LoadShaders(void)
 {
	 gProgramID = glCreateProgram();

	 //vertex shader
	 
	 const char *VertexShaderCode = "#version 400\n												\
									layout(location = 0) in vec3 in_Position;					\
									layout(location = 1) in vec4 in_Color;						\
									layout(location = 2) in vec2 in_TexCoord;					\
									uniform mat4 ml_matrix;										\
									out vec4 ex_Color;											\
									out vec2 ex_TexCoord;										\
									void main()													\
									{															\
										 gl_Position = ml_matrix*vec4(in_Position,1.0);			\
										 ex_Color = in_Color;									\
										 ex_TexCoord = in_TexCoord;								\
									}";



	 GLuint vertexshaderID = glCreateShader(GL_VERTEX_SHADER);
	 glShaderSource(vertexshaderID, 1,&VertexShaderCode, NULL);

	 glCompileShader(vertexshaderID);
	 GLint status;
	 glGetShaderiv(vertexshaderID,GL_COMPILE_STATUS , &status);


	 if (status == GL_TRUE)
		 glAttachShader(gProgramID, vertexshaderID);
	 else
	 {
		 printf("Couldn't compile vertex shader : %i\n", status);

		 GLsizei returnedlength = 0;
		 const unsigned int	logsize = 1000;
		 char log[logsize];
		 memset(log, 0, logsize * sizeof(char));
		 glGetShaderInfoLog(vertexshaderID, logsize, &returnedlength, log);
		 printf("%s \n", log);
	 }
	 

	 //fragment shader
	 {
		 const char *fragmentShaderCode = "#version 400\n												\
									out	vec4 out_Color;													\
									in vec4 ex_Color;													\
									in vec2 ex_TexCoord;												\
									uniform sampler2D uTexture;											\
									uniform int debug_mode;												\
									void main()															\
									{																	\
											out_Color	= texture(uTexture,ex_TexCoord);				\
											if(debug_mode == 1){											\
											out_Color = vec4(1.0,1.0,1.0,1.0);	}						\
									}";
		 //	out_Color	= texture(1.0f,1.0f,1.0f,1.0f);	



		 //texture2D(uTexture,ex_TexCoord);

	 //vec4(1.0,0.0,0.0,1.0);
	 // out_Color	=	ex_Color;
		 GLuint fragmentshaderID = glCreateShader(GL_FRAGMENT_SHADER);
		 glShaderSource(fragmentshaderID, 1, &fragmentShaderCode, NULL);

		 glCompileShader(fragmentshaderID);
		 GLint status;
		 glGetShaderiv(fragmentshaderID, GL_COMPILE_STATUS, &status);
	 
		 if (status == GL_TRUE)
			 glAttachShader(gProgramID, fragmentshaderID);
		 else
		 {
			 printf("Couldn't compile fragment shader : %i\n", status);

			 GLsizei returnedlength = 0;
			 const unsigned int	logsize = 1000;
			 char log[logsize];
			 memset(log,0, logsize*sizeof(char));
			 glGetShaderInfoLog(fragmentshaderID, logsize, &returnedlength, log);
			 printf("%s \n", log);
		 }
	
	 }

	 glLinkProgram(gProgramID);

	 GLsizei returnedlength = 0;
	 const unsigned int	logsize = 1000;
	 char log[logsize];
	 memset(log, 0, logsize * sizeof(char));
	 glGetShaderInfoLog(gProgramID, logsize, &returnedlength, log);
	 printf("%s \n", log);

	 glUseProgram(gProgramID);


 }








 /*gameobject *loadobject(const char* pFilename)
 {
	 gameobject *newgameobj = NULL;

	 FILE *fp;
	 fopen_s(&fp,pFilename,"r");

	 if (fp)
	 {
		 newgameobj = new gameobject();
		 while (!feof(fp))
		 {
			 char componentype[256];
			 memset(componentype, 0, 256 * sizeof(char));

			 fscanf_s(fp,"%255s",componentype,sizeof(componentype));

			 //TRANSFORM 
			 if (0 == strcmp(componentype, "TRANSFORM"))
			 {
				 transform* ptr = new transform();
				 newgameobj->addcomponent(ptr);
				 ptr = (transform *)newgameobj->getcomponent(COMPONENT_TYPES::COMPONENT_TRANSFORM);
				 
				 ptr->serialize(&fp);
				 ptr->mpowner = newgameobj;

			 }
			 //SPRITE
			 else if(0 == strcmp(componentype, "SPRITE"))
			 {
				 sprite* ptr = new sprite();
				 newgameobj->addcomponent(ptr);
				 ptr = (sprite *)newgameobj->getcomponent(COMPONENT_TYPES::COMPONENT_SPRITE);
				 ptr->serialize(&fp);
				 ptr->mpowner = newgameobj;
				
			 }
			//CONTROLLER
			 else if (0 == strcmp(componentype, "CONTROLLER"))
			 {
				 controller* ptr = new controller();
				 newgameobj->addcomponent(ptr);
				 ptr = (controller *)newgameobj->getcomponent(COMPONENT_TYPES::COMPONENT_CONTROLLER);
				 ptr->serialize(&fp);
				 ptr->mpowner = newgameobj;

			 }
			 //UPDOWN
			 else if (0 == strcmp(componentype, "UPDOWN"))
			 {
				 updown *ptr = new updown();
				 newgameobj->addcomponent(ptr);
				 ptr = (updown *)newgameobj->getcomponent(COMPONENT_TYPES::COMPONENT_UPDOWN);
				 ptr->serialize(&fp);
				 ptr->mpowner = newgameobj;

			 }
			 //BODY
			 else if (0 == strcmp(componentype, "BODY"))
			 {
				 Body *ptr = new Body();
				 newgameobj->addcomponent(ptr);
				 ptr = (Body *)newgameobj->getcomponent(COMPONENT_TYPES::COMPONENT_BODY);
				 ptr->serialize(&fp);
				 ptr->mpowner = newgameobj;

			 }


		 }
		 pGOM->gameobjects.push_back(newgameobj);
		 fclose(fp);

	 }
	 return newgameobj;

 }*/
 //gameobject *loadobject(const char* pFilename)

 //---------------------------------------------------------------------------------------------

#pragma comment(lib, "legacy_stdio_definitions.lib")
phantomengine::phantomengine()
{
	appIsRunning = true;
	error = 0;
	counter_ = 60;

	
	posX = 0;
	posY = 0;
	// pImages[5] = { NULL };
	 gsurface = NULL;
	 currentsurface = NULL;
	 currentkeystate = SDL_GetKeyboardState(NULL);

}

//phantomengine:~phantomengine()
//{
//
//}
			


bool phantomengine::init()
{
	
	if (AllocConsole())
	{
		FILE* file;

		freopen_s(&file, "CONOUT$", "wt", stdout);
		freopen_s(&file, "CONOUT$", "wt", stdin);
		freopen_s(&file, "CONOUT$", "wt", stderr);

		SetConsoleTitle(L"PhantomEngine");
	}

	 pinputmanager = new inputmanager();


	 //SDL
	if ((error = SDL_Init(SDL_INIT_VIDEO)) < 0)
	{
		printf("Couldn't initialize SDL, error %i\n", error);
		return 1;
	}

	else
	{

		//OpenGL
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);


		pWindow = SDL_CreateWindow("SDL2 window",		// window title
			SDL_WINDOWPOS_UNDEFINED,					// initial x position
			SDL_WINDOWPOS_UNDEFINED,					// initial y position
			800,										// width, in pixels
			600,										// height, in pixels
			SDL_WINDOW_SHOWN| SDL_WINDOW_OPENGL);



		// Check that the window was successfully made
		if (NULL == pWindow)
		{
			// In the event that the window could not be made...
			printf("Could not create window: %s\n", SDL_GetError());
			return 1;
		}
		//create context
		SDL_GLContext openGL_Context = SDL_GL_CreateContext(pWindow);	//check
		
		

		rscmgr->Getsurface();
		
		pWindowSurface = SDL_GetWindowSurface(pWindow);
		

		if (glewInit() != GLEW_OK)
			printf("Couldn't initialize GLEW \n");



		LoadShaders();
	/*
		float tri1[] = {
			-0.082f,-0.082f,0.0f, //left
			0.082f,-0.082f,0.0f, //right
			0.0f,0.082f,0.0f,  //top
		};

		float tri2[]
		{
			//second Triangle		//Colors			//texture co-ordinates
			-0.2f, -0.2f, 0.0f,		1.0f,0.0f,0.0f,		1.0f,1.0f,				//left
			0.2f, -0.2f, 0.0f,		0.0f,0.0f,0.0f,		1.0f,0.0f,				// right
			0.0f, 0.2f, 0.0f,		0.0f,0.0f,1.0f,		0.0f,1.0f,				// top
		};

		 

		float texCoords[] = {
			0.0f,0.0f,		//lower left corner
			1.0f,0.0f,		//lower right corner
			0.5f,1.0f,		//top center corner
		};
		*/

		


	//	glGenVertexArrays(2, VAO);
	//	glGenBuffers(2, VBO);


		/*glBindVertexArray(VAO[0]);

		glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
		glBufferData(GL_ARRAY_BUFFER,sizeof(tri1), tri1, GL_STATIC_DRAW);
		glVertexAttribPointer(0,3, GL_FLOAT, false, 3*sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
*/
		/*
		//2nd triangle
		glBindVertexArray(VAO[1]);

		glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(tri2), tri2, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, false, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		/*glVertexAttribPointer(1, 3, GL_FLOAT, false, 8 * sizeof(float), (void*)(3* sizeof(float)));
		glEnableVertexAttribArray(1);
		//enable textures
		glVertexAttribPointer(2, 2, GL_FLOAT, false, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		//shape creation

		//------------------------------------------

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//load and generate the texture
		int width, height, nrchannels;
		unsigned  char* data = stbi_load("spaceship.jpg", &width, &height, &nrchannels, 0);

		

		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load textures" << std::endl;
		}
		stbi_image_free(data);

		glClearColor(0.0f, 1.0f, 1.0f, 1.0f);

		*/

		//create mesh
	
		
		/*
		glGenBuffers(2, bufferIDs);
		/*int vertexnum = 3;
		int cordinatesPerPosition = 3;
		int cordinatesPerColor = 4;


		int positionstride = cordinatesPerPosition * sizeof(float);
		int colorstride = cordinatesPerColor * sizeof(float);

		GLfloat *pPosition = new GLfloat[vertexnum * cordinatesPerPosition];
		GLfloat *pColors = new GLfloat[vertexnum * cordinatesPerColor];//4

		//vertex 1

		pPosition[0] = -0.1f;	pColors[0] = 1.0f;
		pPosition[1] = -0.1f;	pColors[1] = 0.0f;
		pPosition[2] = 0.0f;	pColors[2] = 0.0f;
								pColors[3] = 1.0f;
			

		//vertex 2

		pPosition[3] = 0.1f;	pColors[4] = 1.0f;
		pPosition[4] = -0.1f;	pColors[5] = 1.0f;
		pPosition[5] = 0.0f;	pColors[6] = 0.0f;
								pColors[7] = 1.0f;


		//vertex 3

		pPosition[6] = 0.0f;	pColors[8] = 0.0f;
		pPosition[7] = 0.1f;	pColors[9] = 0.0f;
		pPosition[8] = 0.0f;	pColors[10] = 1.0f;
								pColors[11] = 1.0f;

		glBindBuffer(GL_ARRAY_BUFFER, bufferIDs[0]);
		glBufferData(GL_ARRAY_BUFFER, vertexnum * positionstride, pPosition, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);


		glBindBuffer(GL_ARRAY_BUFFER, bufferIDs[1]);
		glBufferData(GL_ARRAY_BUFFER, vertexnum * colorstride, pColors, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ARRAY_BUFFER, bufferIDs[2]);
		glBufferData(GL_ARRAY_BUFFER, vertexnum * texturecoordinatestride, pColors, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		*/

	//	glFinish();

	/*	delete[] pPosition;
		delete[] pColors;
		*/
		/*else
		{
			gsurface = SDL_GetWindowSurface(pWindow);
		}*/

	}

	

	loadmedia();
	//return gsurface;
}
//
//void print(int x, int y, int z, char *string)
//{
//
//	//set the position of the text in the window using the x and y coordinates
//	glRasterPos2f(x, y);
//	//get the length of the string to display
//	int len = (int)strlen(string);
//
//	//loop to display character by character
//	for (int i = 0; i < len; i++)
//	{
//		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
//	}
//};


int temp = 0;
bool phantomengine::loadmedia()
{
	

	//Milestone 2

	
	{

        // objfactory->loadlevel("Game_start.txt");

		 ship = objfactory->loadlevel("Test1.txt");
		
	}
	{
		 objfactory->loadlevel("Bullets.txt");
		 objfactory->loadlevel("Asteroids.txt");
		 objfactory->loadlevel("Asteroids2.txt");
		 objfactory->loadlevel("Asteroids3.txt");
		 objfactory->loadlevel("Asteroids4.txt");
		 objfactory->loadlevel("Asteroids5.txt");
		 objfactory->loadlevel("Missile.txt");

	 //objfactory->loadlevel("Test3.txt");
		
	}

	/*can write the below feature in another function called s8tart or run or render because its not related to load media**/


	//all the rendering is done here

	



	float transformmatrix[16];
	float angle = 0.0f;
	float xvalue = 0.0f;
	float yvalue = 0.0f;

	//Game Loop
	while (true == appIsRunning)
	{
		//pfrc->framestart();
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				appIsRunning = false;
			}
		}

		pinputmanager->update();


		//Inputs for the running of the game


		if (pinputmanager->iskeypressed(SDL_SCANCODE_S))
		{
			controlleractive = true;
		}
		if (pinputmanager->iskeypressed(SDL_SCANCODE_ESCAPE))
		{
			appIsRunning = false;
		}
		if (pinputmanager->iskeypressed(SDL_SCANCODE_D))
		{
			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

			glUniform1i(glGetUniformLocation(gProgramID, "debug_mode"),1);
			glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_INT, NULL);
			

		}
		if (pinputmanager->iskeypressed(SDL_SCANCODE_D))
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		}


		if (gameactive && !lose_scene)
		{

			pfrc->framestart();

			SDL_Event e;
			while (SDL_PollEvent(&e) != 0)
			{
				//User requests quit
				if (e.type == SDL_QUIT)
				{
					appIsRunning = false;
				}
			}
			if (pinputmanager->iskeypressed(SDL_SCANCODE_ESCAPE))
			{
				gameactive = false;
				appIsRunning = false;

			}

			//pinputmanager->update();

			//OpenGL ka implementation
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			glEnable(GL_BLEND);
			glBlendFunc(GL_ONE, GL_SRC_ALPHA);

			/*float cosine = cosf(angle);
			float sine = sinf(angle);

			memset(transformmatrix, 0.0f, sizeof(transformmatrix));

			transformmatrix[0] = transformmatrix[5] = transformmatrix[10] = transformmatrix[15] = 1.0f;

			transformmatrix[0] = cosine;
			transformmatrix[4] = -sine;
			transformmatrix[1] = sine;
			transformmatrix[5] = cosine;


			if (pinputmanager->iskeyreleased(SDL_SCANCODE_Q))
			{
				angle -= 0.01f;
				printf("Q is pressed \n");
			}
			else  if (pinputmanager->iskeyreleased(SDL_SCANCODE_E))
			{	angle += 0.01f;
				printf("E is pressed \n");
			}
			else if (pinputmanager->iskeyreleased(SDL_SCANCODE_W))
			{
				yvalue += 0.05f;
				printf("W is pressed \n");
			}
			else if (pinputmanager->iskeyreleased(SDL_SCANCODE_S))
			{
				yvalue -= 0.05f;
				printf("S is pressed \n");
			}

			else if (pinputmanager->iskeyreleased(SDL_SCANCODE_A))
			{
				xvalue -= 0.05f;
				printf("A is pressed \n");
			}
			else if (pinputmanager->iskeyreleased(SDL_SCANCODE_D))
			{
				xvalue += 0.05f;
				printf("D is pressed \n");
			}*/
			//else if (pinputmanager->iskeypressed(SDL_SCANCODE_SPACE))
			//{
			//	{
			//		glBindVertexArray(VAO[0]);

			//		glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
			//		glBufferData(GL_ARRAY_BUFFER, sizeof(bullet), bullet, GL_STATIC_DRAW);
			//		//glBufferData(GL_ARRAY_BUFFER, sizeof(bullet), bullet, GL_STATIC_DRAW);
			//		glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), (void*)0);
			//		glEnableVertexAttribArray(0);


			//		glVertexAttribPointer(1, 3, GL_FLOAT, false, 8 * sizeof(float), (void*)(3 * sizeof(float)));
			//		glEnableVertexAttribArray(1);
			//	}
			//}



			/*transformmatrix[3] = xvalue;
			transformmatrix[7] = yvalue;*/

			//S1.use();
			//angle += 0.005f;

			int transformHandle = 2;
			//glEnableVertexAttribArray(transformHandle);
			//glUniformMatrix4fv(transformHandle,1,GL_FALSE,transformmatrix);


			/*glBindVertexArray(VAO[0]);
			glDrawArrays(GL_TRIANGLES, 0, 3);*/
/*
			//glActiveTexture(GL_TEXTURE0);
			//glBindTexture(GL_TEXTURE_2D, texture);
			//	glBindVertexArray(VAO[1]);
			//glDrawArrays(GL_TRIANGLES, 0, 3);

			/*glDisableVertexAttribArray(positionhandle);
			glDisableVertexAttribArray(colorhandle);
			//	glDisableVertexAttribArray(transformHandle);*/




			phymgr->update(pfrc->GetFrameTime() / 1000.0f);
			//check again
			pEM->Update(pfrc->GetFrameTime() / 1000.0f);


			for (auto game_object : pGOM->gameobjects)
			{
				game_object->update();
			}

			for (auto game_object : pGOM->gameobjects)
			{
				transform *pTrans = static_cast<transform*>(game_object->getcomponent(COMPONENT_TYPES::COMPONENT_TRANSFORM));
				glUniformMatrix4fv(glGetUniformLocation(gProgramID, "ml_matrix"), 1, GL_FALSE, glm::value_ptr(pTrans->transformmat));
				sprite *pSprite = static_cast<sprite*>(game_object->getcomponent(COMPONENT_TYPES::COMPONENT_SPRITE));
				if (pTrans != NULL && pSprite != NULL)
				{
					//	SDL_Rect destRect;
						//destRect.x = pTrans->mposx;
						///destRect.y = pTrans->mposy;
						//wrap(game_object);
					if (game_object->get_is_active()) {

						pSprite->draw();
					}
					//SDL_BlitSurface(pSprite->msurface, NULL, gsurface, &destRect);
				}
				

			}
			
			if (playerlives < 0)
			{
				lose_scene = true;
				
			}
			
			if (asteroid_count <= 0)
			{
				win = true;
			}

			SDL_GL_SwapWindow(pWindow);

/*
			//	SDL_UpdateWindowSurface(pWindow);

				//Moved to Controller.h


				/////THIS IS TO CALL THE SHIP TO BE VISIBLE AFTER 2 SECONDS
				*/

				/*if (++temp % 120 == 0)
				{

					ship->set_is_active(true);
				}*/


			if (++counter_ % 120 == 0)
				printf("Frame Time: %u \n", pfrc->GetFrameTime());



			pfrc->frameend();
		}

	

		rscmgr->UpdateScreen(pWindow, pWindowSurface);
				
	}
	
	close();

	
	return 0;

}





void phantomengine::close()
{
	delete rscmgr;
	delete pfrc;
	delete pinputmanager;
	delete pEM;
	/*delete phymgr;
	delete objfactory;
	delete pGOM;
	delete gameobj;*/
	//delete pGOM;

	/*for (int i = 0; i <= 4; ++i)
		SDL_free(pImages[i]);*/
	//delete pinputmanager;

	//free the image surface
	SDL_FreeSurface(gsurface);

	// Close and destroy the window
	SDL_DestroyWindow(pWindow);

	// Quit SDL subsystems
	SDL_Quit();

	return;
}

int main(int argc, char* args[])
{
//	inputmanager* pinputmanager = new inputmanager;
	phantomengine game;
	game.init();
		
	return 0;
}

