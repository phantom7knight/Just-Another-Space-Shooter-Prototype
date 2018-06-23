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



#include "Physicsmanager.h"
#include "GameObjectManager.h"
#include "Collisionmanager.h"
#include "gameobject.h"
#include "Body.h"
#include "frc.h"
#include "Eventmanager.h"
#include "transform.h"
#include <iostream>

extern frameratecontroller *pfrc;
extern GameObjectManager *pGOM;
extern int asteroid_count;

//Collide Event Functions

CollideEvent::CollideEvent() :Event(EventType::COLLIDE)
{
	pgameobject1 = pgameobject2 = NULL;
}

CollideEvent::~CollideEvent()
{

}




//Physics Manager Functions

Physicsmanager::Physicsmanager()
{
	 pCollisionManager = new Collisionmanager();

}


Physicsmanager::~Physicsmanager()
{
	delete pCollisionManager;
}



void Physicsmanager::update(float dt)
{
	//Integrate the body
	for (auto gameobj : pGOM->gameobjects)
	{
		Body *pbody = (Body *)gameobj->getcomponent(COMPONENT_TYPES::COMPONENT_BODY);
		float dt = ((float)pfrc->GetFrameTime()) / 1000;
		if (pbody == NULL) continue;
		pbody->integrate(.1f, dt);//(gravity,frametime)

	}

	//remove prev contacts by reseting  
	pCollisionManager->Reset();

	
	unsigned int pGOMnum1, pGOMnum2, pGOMnum = pGOM->gameobjects.size();
	for (pGOMnum1 = 0; pGOMnum1<pGOMnum ;++pGOMnum1)
	{
		Body *pbody1= static_cast<Body *>(pGOM->gameobjects[pGOMnum1]->getcomponent(COMPONENT_TYPES::COMPONENT_BODY));
		if (NULL==pbody1)
		{
			continue;
		}

		for (pGOMnum2 = pGOMnum1 + 1; pGOMnum2 < pGOMnum; ++pGOMnum2)
		{
			Body *pbody2 = static_cast<Body *>(pGOM->gameobjects[pGOMnum2]->getcomponent(COMPONENT_TYPES::COMPONENT_BODY));
			if (NULL == pbody2)
			{
				continue;
			}
			//check if the object is active


			bool active_check = false;

			if (pGOM->gameobjects[pGOMnum1]->isactive_ == true && pGOM->gameobjects[pGOMnum2]->isactive_ == true)
			{
				active_check = true;
			}

			else if (pGOM->gameobjects[pGOMnum2]->isactive_ == true && pGOM->gameobjects[pGOMnum1]->isactive_ == true)
			{
				active_check = true;
			}



			/*if (pGOM->gameobjects[pGOMnum2]->type == HOMINGMISSILE && pGOM->gameobjects[pGOMnum1]->type == ASTEROID)
			{
				if (pGOM->gameobjects[pGOMnum1]->isactive_ == true && pGOM->gameobjects[pGOMnum2]->isactive_ == true)
				{
					std::cout << "homing" << std::endl;
				}
			}*/


			//check for the collision between bullet and ship
			if (active_check == true && (pGOM->gameobjects[pGOMnum1]->type == SHIP && pGOM->gameobjects[pGOMnum2]->type == ASTEROID) || (pGOM->gameobjects[pGOMnum1]->type == BULLET && pGOM->gameobjects[pGOMnum2]->type == ASTEROID) || (pGOM->gameobjects[pGOMnum2]->type == HOMINGMISSILE && pGOM->gameobjects[pGOMnum1]->type == ASTEROID))
			{
				pCollisionManager->checkcollisionsandcreatecontacts(pbody1->mshape, pbody1->mposx, pbody1->mposy, pbody2->mshape, pbody2->mposx, pbody2->mposy);
				
			}
				
			if (active_check == true && (pGOM->gameobjects[pGOMnum2]->type == HOMINGMISSILE && pGOM->gameobjects[pGOMnum1]->type == ASTEROID))
			{
				pCollisionManager->checkcollisionsandcreatecontacts(pbody2->mshape, pbody2->mposx, pbody2->mposy, pbody1->mshape, pbody1->mposx, pbody1->mposy);
				//asteroid_count--;
			}
			else if( (pGOM->gameobjects[pGOMnum1]->type == SHIP && pGOM->gameobjects[pGOMnum2]->type == BULLET) || (pGOM->gameobjects[pGOMnum1]->type == ASTEROID && pGOM->gameobjects[pGOMnum2]->type == ASTEROID))
				continue;
		}
		

	}

	//resolve contacts
	for (auto go : pCollisionManager->mcontacts)
	{
		CollideEvent pcollide;

		pcollide.pgameobject1 = go->mBodies[0]->mpowner;
		pcollide.pgameobject2 = go->mBodies[1]->mpowner;

		go->mBodies[0]->mpowner->HandleEvent(&pcollide);
		
		pcollide.pgameobject1 = go->mBodies[1]->mpowner;
		pcollide.pgameobject2 = go->mBodies[0]->mpowner;

		go->mBodies[1]->mpowner->HandleEvent(&pcollide);
	}


	//printf("The number of contacts is %d \n", pCollisionManager->mcontacts.size());
	/*for (gameobject* pobj : pGOM->gameobjects)
	{
		Body *pBody = (Body *)pobj->getcomponent(COMPONENT_TYPES::COMPONENT_BODY);
		transform *ptrans = (transform, *)pobj->getcomponent(COMPONENT_TYPES::COMPONENT_TRANSFORM);
	}*/



}