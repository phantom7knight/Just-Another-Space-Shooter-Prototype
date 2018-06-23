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

#include <vector>
#include "stdio.h"
//#include "Eventmanager.h"
//#include "transform.h"
//#include "sprite.h"
//#include "controller.h"

//class transform;
//class sprite;	
//class controller;
class component;
class Event;

enum TypeObject
{
	SHIP,
	BULLET,
	ASTEROID,
	HOMINGMISSILE,
};



class gameobject
{
public:
	gameobject();
	~gameobject();
	void addcomponent(component *mcomponent);
	void update(void);
	component* getcomponent(unsigned int type);

	bool get_is_active() { return isactive_; }
	void set_is_active(bool is_active) { isactive_ = is_active; }
	/*transform *mtrans;
	sprite *mspr;
	controller *mcontroller;*/
	void HandleEvent(Event *pevent);
	bool isactive_;
	TypeObject type;
	std::vector <component*>mcomponents;

};

