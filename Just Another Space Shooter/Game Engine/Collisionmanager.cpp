
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




#include "Collisionmanager.h"
#include "Math2D.h"


GameObjectManager *gameobjectmanager;


//forward declerations
bool checkCollisionCircleCircle(Shape* shape1, float xpos1, float ypos1, Shape* shape2, float xpos2, float ypos2, std::list<Contact*> &mContacts);
bool checkCollisionCircleRectangle(Shape* shape1, float xpos1, float ypos1, Shape* shape2, float xpos2, float ypos2, std::list<Contact*> &mContacts);
bool checkCollisionRectangleCircle(Shape* shape1, float xpos1, float ypos1, Shape* shape2, float xpos2, float ypos2, std::list<Contact*> &mContacts);
bool checkCollisionRectangleRectangle(Shape* shape1, float xpos1, float ypos1, Shape* shape2, float xpos2, float ypos2, std::list<Contact*> &mContacts);


Collisionmanager::Collisionmanager():mcontacts()
{
	mCollisionTable[(int)Shape::SHAPE_TYPE::CIRCLE][(int)Shape::SHAPE_TYPE::CIRCLE] = checkCollisionCircleCircle;
	mCollisionTable[(int)Shape::SHAPE_TYPE::CIRCLE][(int)Shape::SHAPE_TYPE::RECTANGLE] = checkCollisionCircleRectangle;
	mCollisionTable[(int)Shape::SHAPE_TYPE::RECTANGLE][(int)Shape::SHAPE_TYPE::CIRCLE] = checkCollisionRectangleCircle;
	mCollisionTable[(int)Shape::SHAPE_TYPE::RECTANGLE][(int)Shape::SHAPE_TYPE::RECTANGLE] = checkCollisionRectangleRectangle;
}




//Shape Constructor
Shape::Shape(SHAPE_TYPE type)
{
	mshapetype = type;
	mOwnerBody = NULL;
}

//ShapeCircle Test
bool shapecircle::Testpoint(float Pointx, float Pointy)
{
	float sqDist = (Pointx - mOwnerBody->mposx)*(Pointx - mOwnerBody->mposx) + (Pointy - mOwnerBody->mposy)*(Pointy - mOwnerBody->mposy);

	if (sqDist > (radius*radius))
		return false;
	return true;

}
/*
//ShapeAABB Test
bool ShapeAABB::TestPoint(float Pointx, float Pointy)
{
	float right, left, top, bottom;
	left = mOwnerBody->mposx - mleft;
	right = mOwnerBody->mposx - mright;
	top = mOwnerBody->mposy - mtop;
	bottom = mOwnerBody->mposy - mbottom;

	if ((Pointx<left)||
		(Pointx>right) ||
		(Pointy<bottom) ||
		(Pointy>top))

		return false;

	return true;
}

*/


//collision Manager

bool Collisionmanager::checkcollisionsandcreatecontacts(Shape* shape1, float xpos1, float ypos1, Shape* shape2, float xpos2, float ypos2)
{
	return mCollisionTable[(int)shape1->mshapetype][(int)shape2->mshapetype](shape1,xpos1,ypos1,shape2,xpos2,ypos2,mcontacts);
}




//Collision check for circle and circle
bool checkCollisionCircleCircle(Shape* shape1, float xpos1, float ypos1, Shape* shape2, float xpos2, float ypos2, std::list<Contact*> &mContacts)
{
	//if (result)
	{
		Contact *pcon = new Contact();

		pcon->mBodies[0] = shape1->mOwnerBody;
		pcon->mBodies[1] = shape2->mOwnerBody;

		mContacts.push_back(pcon);


	}


	return false;
}


//collision check for circle and rectangle
bool checkCollisionCircleRectangle(Shape* shape1, float xpos1, float ypos1, Shape* shape2, float xpos2, float ypos2, std::list<Contact*> &mContacts)
{
	{
		Contact *pcon = new Contact();

		pcon->mBodies[0] = shape1->mOwnerBody;
		pcon->mBodies[1] = shape2->mOwnerBody;

		mContacts.push_back(pcon);


	}


	return false;
}


//collision check for rectangle and circle
bool checkCollisionRectangleCircle(Shape* shape1, float xpos1, float ypos1, Shape* shape2, float xpos2, float ypos2, std::list<Contact*> &mContacts)
{
	{
		Contact *pcon = new Contact();

		pcon->mBodies[0] = shape1->mOwnerBody;
		pcon->mBodies[1] = shape2->mOwnerBody;

		mContacts.push_back(pcon);


	}


	return false;
}




//Collision check for rectangle and rectangle

bool checkCollisionRectangleRectangle(Shape* shape1, float xpos1, float ypos1, Shape* shape2, float xpos2, float ypos2, std::list<Contact*> &mContacts)
{

	ShapeAABB* prect1 = (ShapeAABB *)shape1;
	ShapeAABB* prect2 = (ShapeAABB *)shape2;

	bool result;
	
	float left1 = (xpos1 -prect1->width / 2);
	float left2 = (xpos2 -prect2->width / 2);

	float right1 = (xpos1)+prect1->width;// / 2;
	float right2 = (xpos2)+prect2->width;// / 2;

	float top1 = ypos1 + prect1->height / 2;
	float top2 = ypos2 + prect2->height / 2;

	float bottom1 = ypos1 - prect1->height;// / 2;
	float bottom2 = ypos2 - prect2->height;// / 2;

	if (left1 >right2  || (left2>right1) || (top1<bottom2) || (top2<bottom1))
		result = false;
	else
		result = true;


	if (result)
	{
		Contact *pcon = new Contact();

		pcon->mBodies[0] = shape1->mOwnerBody;
		pcon->mBodies[1] = shape2->mOwnerBody;

		mContacts.push_back(pcon);


	}       


	return result;
}



//Collision manager Reset function
void Collisionmanager::Reset()
{

	for (auto a : mcontacts)
		delete a;
	mcontacts.clear();


}


