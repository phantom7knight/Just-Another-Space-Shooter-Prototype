// ---------------------------------------------------------------------------
// Project Name		:	Cage Implementation
// File Name		:	LineSegment.c
// Author			:	Antoine Abi Chacra
// Creation Date	:	2008/01/31
// Purpose			:	implementation of the Line Segment
// History			:
// - 2015/12/10		:	Implemented C style component based architecture 
// ---------------------------------------------------------------------------


/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology.
File Name: LineSegment2D.c
Purpose: Project2_Part 1 - Cage game to set up line segment and animated ball collisions
Language: C++ Visual Studio Enterprise 2015
Platform: Microsoft <R> C/C++ Optimizing Compiler Version 19.00.24210 Windows7
Project: CS529_rohit.tolety_3
Author: Rohit Tolety rohit.tolety 60000917
Creation date: 5th Oct 2017
- End Header --------------------------------------------------------*/


#include "LineSegment2D.h"


int BuildLineSegment2D(LineSegment2D *LS, Vector2D *Point0, Vector2D *Point1)
{
	//return;
	Vector2D pResult,normal;
	//Vector2D *pResult2;

	Vector2DSet(&LS->mP0, Point0->x, Point0->y);
	Vector2DSet(&LS->mP1, Point1->x, Point1->y);
	Vector2DSub(&pResult, &LS->mP1, &LS->mP0);
	Vector2DSet(&normal, pResult.y , -pResult.x);
	Vector2DNormalize(&LS->mN, &normal);

	//	LS->mNdotP0 = Vector2DDotProduct(&LS->mN, Point0);
	LS->mNdotP0 = Vector2DDotProduct(&LS->mN, Point0);

	return 1;
}