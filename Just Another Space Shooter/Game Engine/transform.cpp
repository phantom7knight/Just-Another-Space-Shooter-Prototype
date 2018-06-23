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




#include <stdio.h>
#include "transform.h"





class gameobject;

transform::transform() :component (COMPONENT_TYPES::COMPONENT_TRANSFORM)
{
	mposx = 0;
	mposy = 0;
	//mpowner = NULL;

	position.x = mposx;
	position.y = mposy;

	scale = glm::vec3(0.0f);


}


transform::~transform()
{
}


void transform::update(void)
{
	
//	glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	

	//transformmat = glm::translate(transformmat, glm::vec3(mposx, mposy, 0.0f));
//	vec = transformmat * vec;
	//transformmat = glm::rotate(transformmat, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	//transformmat = glm::scale(transformmat, glm::vec3(0.1f, 0.1f, 1.0f));

	transformmat = glm::mat4(1.0);
	transformmat = glm::translate(transformmat, glm::vec3(mposx, mposy, 0.0f));
	transformmat = glm::rotate(transformmat, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));


	
}


void transform::serialize(FILE **fp)
{
	fscanf_s(*fp,"%f %f\n",&mposx,&mposy,&angle);
	//printf("%d %d\n", &mposx, &mposy);
}

void transform::HandleEvent(Event * pEvent)
{
	if (EventType::PAUSE == pEvent->mtype)
	{
		printf("EVENT OCCURED \n");
	}
}
