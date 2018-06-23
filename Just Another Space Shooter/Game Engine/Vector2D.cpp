// ---------------------------------------------------------------------------
// Project Name		:	Cage Implementation
// File Name		:	Vector2D.c
// Author			:	Antoine Abi Chacra
// Creation Date	:	2008/01/31
// Purpose			:	implementation of the Vector2D
// History			:
// - 2015/12/10		:	Implemented C style component based architecture 
// ---------------------------------------------------------------------------


/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology.
File Name: Vector2D.c
Purpose: Project2_Part 1 - Cage game to set up line segment and animated ball collisions
Language: C++ Visual Studio Enterprise 2015
Platform: Microsoft <R> C/C++ Optimizing Compiler Version 19.00.24210 Windows7
Project: CS529_rohit.tolety_3
Author: Rohit Tolety rohit.tolety 60000917
Creation date: 5th Oct 2017
- End Header --------------------------------------------------------*/




#include "Vector2D.h"

#define EPSILON 0.0001

////////////////////
// From Project 2 //
////////////////////
// ---------------------------------------------------------------------------

void Vector2DZero(Vector2D *pResult)
{
	pResult->x = 0;
	pResult->y = 0;
}

// ---------------------------------------------------------------------------

void Vector2DSet(Vector2D *pResult, float x, float y)
{
	pResult->x = x;
	pResult->y = y;
}

// ---------------------------------------------------------------------------

void Vector2DNeg(Vector2D *pResult, Vector2D *pVec0)
{
	pResult->x = -pVec0->x;
	pResult->y = -pVec0->y;

}

// ---------------------------------------------------------------------------

void Vector2DAdd(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1)
{
	pResult->x = pVec0->x + pVec1->x;
	pResult->y = pVec0->y + pVec1->y;

}

// ---------------------------------------------------------------------------

void Vector2DSub(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1)
{
	pResult->x = pVec0->x - pVec1->x;
	pResult->y = pVec0->y - pVec1->y;
}

// -------------------------------------	--------------------------------------

void Vector2DNormalize(Vector2D *pResult, Vector2D *pVec0)
{
	float len = Vector2DLength(pVec0);

	pResult->x = pVec0->x / len;
	pResult->y = pVec0->y / len;
}

// ---------------------------------------------------------------------------

void Vector2DScale(Vector2D *pResult, Vector2D *pVec0, float c)
{
	pResult->x = pVec0->x * c;
	pResult->y = pVec0->y * c;

}

// ---------------------------------------------------------------------------

void Vector2DScaleAdd(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1, float c)
{
	pResult->x = pVec0->x * c + pVec1->x;
	pResult->y = pVec0->y * c + pVec1->y;


}

// ---------------------------------------------------------------------------

void Vector2DScaleSub(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1, float c)
{
	pResult->x = pVec0->x * c - pVec1->x;
	pResult->y = pVec0->y * c - pVec1->y;
}

// ---------------------------------------------------------------------------

float Vector2DLength(Vector2D *pVec0)
{

	return sqrt((pVec0->x)*(pVec0->x) + (pVec0->y)*(pVec0->y));

}

// ---------------------------------------------------------------------------

float Vector2DSquareLength(Vector2D *pVec0)
{
	return ((pVec0->x)*(pVec0->x) + (pVec0->y)*(pVec0->y));
}

// ---------------------------------------------------------------------------

float Vector2DDistance(Vector2D *pVec0, Vector2D *pVec1)
{
	return sqrt(((pVec0->x - pVec1->x) * (pVec0->x - pVec1->x)) + ((pVec0->y - pVec1->y) * (pVec0->y - pVec1->y)));
}

// ---------------------------------------------------------------------------

float Vector2DSquareDistance(Vector2D *pVec0, Vector2D *pVec1)
{
	return (((pVec0->x - pVec1->x) * (pVec0->x - pVec1->x)) + ((pVec0->y - pVec1->y) * (pVec0->y - pVec1->y)));

}

// ---------------------------------------------------------------------------

float Vector2DDotProduct(Vector2D *pVec0, Vector2D *pVec1)
{
	return pVec0->x*pVec1->x + pVec0->y*pVec1->y;
}

// ---------------------------------------------------------------------------

void Vector2DFromAngleDeg(Vector2D *pResult, float angle)
{
	float angle1 = (3.1415926535897932384626433832795 * angle) / 180;
	pResult->x = cos(angle1);
	pResult->y = sin(angle1);
}

// ---------------------------------------------------------------------------

void Vector2DFromAngleRad(Vector2D *pResult, float angle)
{
	pResult->x = cos(angle);
	pResult->y = sin(angle);
}

// ---------------------------------------------------------------------------

void Vector2DFromAngle(Vector2D *pResult, float angle)
{
	pResult->x = cos(angle);
	pResult->y = sin(angle);
}

float Vector2DAngleFromVec2(Vector2D *pResult)
{
	return atan2f(pResult->y, pResult->x);
}

// ---------------------------------------------------------------------------
