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




#include "gameobject.h"
#include "stdio.h"
#include "transform.h"
#include "sprite.h"
#include "Eventmanager.h"

gameobject::gameobject()
{
	/*mtrans = NULL;
	mspr = NULL;
	mcontroller = NULL;*/
	isactive_ = false;
}


gameobject::~gameobject()
{
	/*if (mtrans!=NULL)
		delete mtrans;
	if (mspr != NULL)
		delete mspr;
	if (mcontroller != NULL)
		delete mcontroller;*/

	for (auto components : mcomponents)
		delete components;

	mcomponents.clear();


}

void gameobject::addcomponent(component *mcomponent)
{
	if(mcomponent!=NULL)
	{
		mcomponent->mpowner = this;
		mcomponents.push_back(mcomponent);
	}


}


void gameobject::update(void)
{
	/*if (mtrans != NULL)
		mtrans->update();
	if (mspr != NULL)
		mspr->update();
	if (mcontroller != NULL)
		mcontroller->update();*/

	if (isactive_) {

		for (auto components : mcomponents)
			components->update();
	}

}


component* gameobject::getcomponent(unsigned int type)
{
	for (auto component : mcomponents)
		if (component->mtype == type)
			return component;

	
	return nullptr;
}




void gameobject::HandleEvent(Event *pevent)
{
	for (auto go : mcomponents)
		go->HandleEvent(pevent);
}