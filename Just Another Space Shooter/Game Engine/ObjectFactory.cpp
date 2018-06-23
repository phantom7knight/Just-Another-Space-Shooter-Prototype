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





#include "ObjectFactory.h"
#include "transform.h"
#include "sprite.h"
#include "controller.h"
#include "updown.h"
#include "Body.h"
#include "Enemy.h"
#include "HomingEnemy.h"
#include "Homingmissile.h"
#include "gameobject.h"
#include "GameObjectManager.h"
#include "Collisionmanager.h"
#include "Physicsmanager.h"
#include <Windows.h>

extern GameObjectManager *pGOM;
extern gameobject* ship;
extern gameobject* bullet;

ObjectFactory::ObjectFactory()
{
	GameObjectManager *pGOM = new GameObjectManager();
}


ObjectFactory::~ObjectFactory()
{
	//delete pGOM;
}



gameobject* ObjectFactory::loadlevel(const char *pFilename)
{
	gameobject *newgameobj = NULL;

	bool cond = false;
	FILE *fp;
	fopen_s(&fp, pFilename, "r");

	if (fp)
	{
		newgameobj = new gameobject();
		while (!feof(fp))
		{
			char componentype[256];
			memset(componentype, 0, 256 * sizeof(char));

			fscanf_s(fp, "%255s", componentype, sizeof(componentype));

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
			else if (0 == strcmp(componentype, "SPRITE"))
			{
				sprite* ptr = new sprite();
				newgameobj->addcomponent(ptr);
				ptr = (sprite *)newgameobj->getcomponent(COMPONENT_TYPES::COMPONENT_SPRITE);
				ptr->serialize(&fp);
				ptr->mpowner = newgameobj;
			}

			//type
			else if (0 == strcmp(componentype, "TYPE"))
			{
				char imagename[256];
				memset(imagename, 0, 256 * sizeof(char));

				fscanf(fp, "%s\n", imagename);
				if (0 == strcmp(imagename, "ship"))
				{
					newgameobj->type = SHIP;
				}
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

			//ENEMY (which moves left to right on the screen)
			else if (0 == strcmp(componentype, "ENEMY"))
			{
				Enemy *ptr = new Enemy();
				newgameobj->addcomponent(ptr);
				ptr = (Enemy *)newgameobj->getcomponent(COMPONENT_TYPES::COMPONENT_ENEMY);
				ptr->serialize(&fp);
				ptr->mpowner = newgameobj;


			}
			

				//HomingENEMY
			else if (0 == strcmp(componentype, "HOMINGENEMY"))
			{
				HomingEnemy *ptr = new HomingEnemy();
				newgameobj->addcomponent(ptr);
				ptr = (HomingEnemy *)newgameobj->getcomponent(COMPONENT_TYPES::COMPONENT_HOMINGENEMY);
				ptr->serialize(&fp);
				ptr->mpowner = newgameobj;

			}
			

			//Homing Missile
			else if (0 == strcmp(componentype, "MISSILEHOMING"))
			{
				 Homingmissile* ptr = new Homingmissile();
				newgameobj->addcomponent(ptr);
				ptr = (Homingmissile *)newgameobj->getcomponent(COMPONENT_TYPES::COMPONENT_HOMINGMISSILE);
				ptr->serialize(&fp);
				ptr->mpowner = newgameobj;


			}


			//ACTIVE
			else if (0 == strcmp(componentype, "active"))
			{
				int active;
				fscanf(fp, "%d\n", &active);
				newgameobj->set_is_active(active == 1);
				
			}

			//BULLETS
			else if ((0 == strcmp(componentype, "Bullets"))) //|| (0 == strcmp(componentype, "Missile")))
			{
				
				delete newgameobj;
				//var set to true
				char filename[256];
				memset(filename, 0, 256 * sizeof(char));

				fscanf_s(fp, "%255s", filename, sizeof(filename));

				int count;
				fscanf(fp, "%d",&count);

				for(int i=0;i<count;i++)
				{
					auto g = loadlevel(filename);
					
					{
						
						pGOM->bullets.push_back(g);

						g->type = BULLET;
					}
				}

				cond = true;

				

				//set var
			}


			//Missiles

			else if ( (0 == strcmp(componentype, "Missiles")))
			{

				delete newgameobj;
				//var set to true
				char filename[256];
				memset(filename, 0, 256 * sizeof(char));

				fscanf_s(fp, "%255s", filename, sizeof(filename));

				int count;
				fscanf(fp, "%d", &count);

				for (int i = 0; i<count; i++)
				{
					auto g = loadlevel(filename);

					{

						pGOM->missile.push_back(g);

						g->type = HOMINGMISSILE;
					}
				}

				cond = true;



				//set var
			}







			//Asteroids
			else if (0 == strcmp(componentype, "Asteroids"))
			{
				
				delete newgameobj;
				//var set to true
				char filename[256];
				memset(filename, 0, 256 * sizeof(char));

				fscanf_s(fp, "%255s", filename, sizeof(filename));

				int count;
				fscanf(fp, "%d", &count);

				for (int i = 0; i<count; i++)
				{
					auto g = loadlevel(filename);

					{
						pGOM->asteroids.push_back(g);

						g->type = ASTEROID;

					}
				}

				cond = true;



				//set var
			}



		}
		if (cond == false){
		
			pGOM->gameobjects.push_back(newgameobj);
		}
		//false
		fclose(fp);

	}
	return newgameobj;
}