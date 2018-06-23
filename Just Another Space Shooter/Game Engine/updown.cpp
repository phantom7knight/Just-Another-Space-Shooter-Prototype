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




#include "updown.h"
#include "gameobject.h"
#include "component.h"

#include "Eventmanager.h"
#include "controller.h"
#include "Body.h"

class gameobject;
extern EventManager *pEM;


updown::updown() :component(COMPONENT_TYPES::COMPONENT_UPDOWN)
{
	mposx = 0;
	mposy = 0;
	isup = false;
}


updown::~updown()
{
}


void updown::update(void)
{
	
	int count;
	transform *ptrans = static_cast<transform*>(mpowner->getcomponent(COMPONENT_TYPES::COMPONENT_TRANSFORM));
	Body *pbody = static_cast<Body*>(mpowner->getcomponent(COMPONENT_TYPES::COMPONENT_BODY));
	//if (result == false)
	if(!isup)
	{
		if(ptrans->mposy <= 0.5 )
		{
			pbody->mposy += 0.008;
			
		}
		else {
			isup = true;
		}
		//result = true;
	}

	if(isup){

		if (ptrans->mposy > -0.3)
		{
		

			pbody->mposy -= 0.008;
		}
		else {
			isup = false;
		}


	}

	
}


void updown::serialize(FILE **fp)
{
	int sub;


	fscanf(*fp, "%d\n",&sub);

	if(1==sub)
		pEM->Subscribe(EventType::PLAYER_HIT, this->mpowner);


	//msurface = rscmgr->loadsurface((char*)imagename);
}



void updown::HandleEvent(Event *pEvent)
{
	if (EventType::PLAYER_HIT == pEvent->mtype)
	{
		PlayerHitEvent *pREvent = (PlayerHitEvent *)pEvent;
		
		transform *ptr = (transform *)mpowner->getcomponent(COMPONENT_TYPES::COMPONENT_TRANSFORM);

		/*if (ptr)
			ptr->mposx += 0.1;*/
		printf("ENEMY HIT THE SHIP IN UPDOWN \n");

		//	here ptr is for up down funvtion





	}
	

	
} 