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



#include "Eventmanager.h"
#include <algorithm>


extern GameObjectManager *pGOM;
extern frameratecontroller *pfrc;
extern inputmanager *pinputmanager;
Event::Event(EventType type)
{
	mtype = type;
	mTimer = 0.0f;
	//Event *pevent = new Event(EventType::COLLIDE);

	//unsigned int test = (unsigned int)EventType::COLLIDE;
}


Event::~Event()
{
}




EventManager::EventManager()
{

}


EventManager::~EventManager()
{
	for (auto go : mEvents)
		delete go;
	mEvents.clear();
}



void EventManager::BroadcastEvent(Event *pEvent)
{
	for (auto pGO : pGOM->gameobjects)
		pGO->HandleEvent(pEvent);
}


void EventManager::BroadcastEventtosubscribe(Event *pEvent)
{
	std::list<gameobject *>&listofsubscribers = msubscriptions[pEvent->mtype];

	for (auto go : listofsubscribers)
		go->HandleEvent(pEvent);

}




void EventManager::AddTimedevent(Event *pEvent)
{
	mEvents.push_back(pEvent);
}


void EventManager::Update(float frametime)
{
	std::list<Event *>::iterator it, itEnd, itTemp;

	it = mEvents.begin();
	itEnd = mEvents.end();

	while (it != itEnd)
	{
		Event *pEvent = *it;

		pEvent->mTimer -= frametime;
		
		if (pEvent->mTimer < 0.0f)
		{
			BroadcastEvent(pEvent);
			//BroadcastEventtosubscribe(pEvent);
			delete pEvent;
			itTemp = it;
			++itTemp;
			mEvents.erase(it);
			it = itTemp;

		}
		else
			++it;

	}

}



void EventManager::Subscribe(EventType et, gameobject* pGO)
{
	std::list<gameobject *>&listofsubscribers = msubscriptions[et];

	if (std::find(listofsubscribers.begin(), listofsubscribers.end(), pGO) == listofsubscribers.end())
		listofsubscribers.push_back(pGO);
}



