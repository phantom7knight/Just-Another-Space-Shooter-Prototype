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
#include "Body.h"
#include "GameObjectManager.h"
#include "gameobject.h"
#include <list>

class Contact;

//class Shape;


class Shape
{

public:
	enum class SHAPE_TYPE
	{
		CIRCLE,
		RECTANGLE,

		NUM,
	};

	Shape(SHAPE_TYPE type);
	virtual ~Shape() {}

	Body *mOwnerBody;
	SHAPE_TYPE mshapetype;


};




class shapecircle : public Shape
{
public:
	shapecircle(): Shape(Shape::SHAPE_TYPE::CIRCLE)
	{
		radius = 0.0f; 
	}
	//~shapecircle();

	float radius;

	bool Testpoint(float Pointx, float Pointy);
	
	


};





class ShapeAABB : public Shape
{

public:
	
	ShapeAABB() : Shape(Shape::SHAPE_TYPE::RECTANGLE)
	{
		//mleft = mright = mtop = mbottom = 0.0f; 
		width = height = 0.0f;
	}
	//~ShapeAABB();

	
	//float mleft,mright,mtop,mbottom;
	float width, height;
	bool TestPoint(float pointx, float pointy)
	{
		return false;
	}
	


};



class Collisionmanager
{
public:
	Collisionmanager();
	~Collisionmanager() { }

	bool checkcollisionsandcreatecontacts(Shape* shape1, float xpos1, float ypos1, Shape* shape2, float xpos2, float ypos2);

	std::list<Contact *>mcontacts;

	bool(*mCollisionTable[(int)Shape::SHAPE_TYPE::NUM][(int)Shape::SHAPE_TYPE::NUM])(Shape* shape1, float xpos1, float ypos1, Shape* shape2, float xpos2, float ypos2, std::list<Contact*> &mContacts);

	void Reset();


};

class Contact
{
public:
	
	Body* mBodies[2];
	
	Contact()
	{
		mBodies[0] = NULL;
		mBodies[1] = NULL;
	}

};


