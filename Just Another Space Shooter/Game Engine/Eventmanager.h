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




#pragma once

#include "GameObjectManager.h"
#include "gameobject.h"
#include "frc.h"
#include "inputmanager.h"
#include "SDL.h"
#include <unordered_map>
#include <list>
#include <algorithm>


enum EventType
{
	COLLIDE,
	PLAYER_HIT,
	BULLET_HIT,
	MISSILE_HIT,
	PAUSE,

	
};

//NUM,


class Event
{
public:
	Event(EventType type);
	virtual ~Event();

	EventType mtype;
	float mTimer;
};



class EventManager
{
public:
	EventManager();
	~EventManager();

	void BroadcastEvent(Event *pEvent);
	void BroadcastEventtosubscribe(Event *pEvent);
	void AddTimedevent(Event *pEvent);
	void Subscribe(EventType et, gameobject* pGO);
	void Update(float frametime);

	std::list<Event *> mEvents;
	std::unordered_map<EventType, std::list<gameobject *> > msubscriptions;

};
