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
#include "component.h"
#include "Vector2D.h"
//#include "Physicsmanager.h"
#include "Eventmanager.h"


extern EventManager* pEM;


class gameobject;
class Shape;

class Body:public component
{
public:
	Body();
	~Body();

	void update(void);
	void serialize(FILE **fp);
	void integrate(float gravity,float Deltatime);
	void initialize(void);

	float mposx, mposy;
	float mprevposx, mprevposy;
	float mvelx, mvely;
	float maccx, maccy;
	float mtotalforcex, mtotalforcey;
	float mMass, mInvMass;
	float angle;

	//int playerlives;
	Vector2D mvelocity;
	Vector2D macceleration;

	void HandleEvent(Event *event);
	Shape* mshape;


};

