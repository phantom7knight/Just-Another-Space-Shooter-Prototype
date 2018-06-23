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




#include "Body.h"
#include "gameobject.h"
#include "transform.h"
#include "Collisionmanager.h"
#include "Physicsmanager.h"


extern int playerlives;
extern int asteroid_count;


Body::Body():component(COMPONENT_TYPES::COMPONENT_BODY)
{
	 mposx = mposy = angle = 0.0f;
	 mprevposx = mprevposy = 0.0f;
	 mvelx = mvely = 0.0f;
	 maccx = maccy = 0.0f;
	 mtotalforcex = mtotalforcey = 0.0f;	
	 mMass = mInvMass = 0.0f;
	 mshape = NULL;
	 mvelocity.x = mvelx;
	 mvelocity.y = mvely;
	 macceleration.x = maccx;
	 macceleration.y = maccy;
	 //playerlives = 5;


}


Body::~Body()
{
}



void Body::update()
{

}



void Body::serialize(FILE **fp)
{
	fscanf(*fp, "%f\n", &mMass);

	if (mMass)
		mInvMass = 1.0f / mMass;
	else
		mMass = 0.0f;

	char shapetype[256];
	memset(shapetype, 0, sizeof(shapetype));
	fscanf(*fp, "%s\n", shapetype, sizeof(shapetype));

	if (0 == strcmp(shapetype, "CIRCLE"))
	{
		mshape = new shapecircle;
		mshape->mOwnerBody = this;
		shapecircle *pcircle = static_cast<shapecircle *>(mshape);
		fscanf(*fp, "%f\n", &pcircle->radius);

	}

	else
	if (0 == strcmp(shapetype, "RECTANGLE"))
	{
		mshape = new ShapeAABB;
		mshape->mOwnerBody = this;
		ShapeAABB *prect = static_cast<ShapeAABB *>(mshape);
		fscanf(*fp, "%f %f\n", &prect->width, &prect->height);
	}




	initialize();
}


void Body::integrate(float gravity, float Deltatime)
{

	mprevposx = mposx;
	mprevposy = mposy;

	//compute acceleration
	//mtotalforcey -= gravity;
/*	maccx = mtotalforcex * mInvMass;
	maccy = mtotalforcey * mInvMass;*/
	maccx *= 0.8f;
	maccy *= 0.8f;
	
	//integrate velocity
	mvelx = maccx * Deltatime + mvelx;
	mvely = maccy * Deltatime + mvely;

	mvelx *= 0.99f;
	mvely *= 0.99f;

	//position
	mposx = mvelx * Deltatime + mposx;
	mposy = mvely * Deltatime + mposy;

	if (mposx > 1.0f || mposx < -1.0f)
		mposx = -mposx;

	if (mposy > 1.0f || mposy < -1.0f)
		mposy = -mposy;

	//remove bullets existence
	{
		gameobject* gamobj = mpowner;
		if (gamobj->type == BULLET && ((mposx > 1.0f || mposx < -1.0f) || (mposy > 1.0f || mposy < -1.0f)))
			gamobj->isactive_ = false;
		if (gamobj->type == HOMINGMISSILE && ((mposx > 1.0f || mposx < -1.0f) || (mposy > 1.0f || mposy < -1.0f)))
			gamobj->isactive_ = false;
	}




	mtotalforcex = mtotalforcey = 0.0f;


	transform *ptr = static_cast<transform *>(mpowner->getcomponent(COMPONENT_TYPES::COMPONENT_TRANSFORM));

	if (NULL != ptr)
	{
		ptr->mposx = mposx;
		ptr->mposy = mposy;
		ptr->angle = angle;
	}
}




void Body::initialize()
{
	transform *ptr = static_cast<transform *>(mpowner->getcomponent(COMPONENT_TYPES::COMPONENT_TRANSFORM));

	if (NULL != ptr)
	{
		mposx = mprevposx = ptr->mposx;
		mposy = mprevposy = ptr->mposy;
		angle = ptr->angle;
	}
}






void Body::HandleEvent(Event *pEvent)
{
	if (EventType::COLLIDE == pEvent->mtype)
	{
		CollideEvent *pCollide = (CollideEvent *)pEvent;
		
		Body* pBody;
		if (pCollide->pgameobject1->type == SHIP && pCollide->pgameobject2->type == ASTEROID)
		{
			pBody = static_cast<Body *>(pCollide->pgameobject1->getcomponent(COMPONENT_TYPES::COMPONENT_BODY));

			if (pBody)
			{
				playerlives--;

				pBody->mposx = 0.08f;
				pBody->mposy = 0.0f;

				printf("Remaining lives = %d \n", playerlives);

			}
			
		}

		if (pCollide->pgameobject1->type == BULLET && pCollide->pgameobject2->type == ASTEROID)
		{
			pBody = static_cast<Body *>(pCollide->pgameobject1->getcomponent(COMPONENT_TYPES::COMPONENT_BODY));

			
				pCollide->pgameobject2->isactive_ = false;
			//	pCollide->pgameobject1->isactive_ = false;
				
							
		}


		if (pCollide->pgameobject1->type == HOMINGMISSILE && pCollide->pgameobject2->type == ASTEROID)
		{
			pBody = static_cast<Body *>(pCollide->pgameobject1->getcomponent(COMPONENT_TYPES::COMPONENT_BODY));

		
			pCollide->pgameobject2->isactive_ = false;
			pCollide->pgameobject1->isactive_ = false;

			

		}



	}
}
