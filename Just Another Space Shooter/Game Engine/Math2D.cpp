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
File Name: Math2D.c
Purpose: Project2_Part 1 - Cage game to set up line segment and animated ball collisions
Language: C++ Visual Studio Enterprise 2015
Platform: Microsoft <R> C/C++ Optimizing Compiler Version 19.00.24210 Windows7
Project: CS529_rohit.tolety_3
Author: Rohit Tolety rohit.tolety 60000917
Creation date: 5th Oct 2017
- End Header --------------------------------------------------------*/



#include "Math2D.h"
#include "stdio.h"
#include "Vector2D.h"
//#include "AEEngine.h"
////////////////////
// From Project 1 //
////////////////////

/*
This function checks if the point P is colliding with the circle whose
center is "Center" and radius is "Radius"
*/
int StaticPointToStaticCircle(Vector2D *pP, Vector2D *pCenter, float Radius)
{
	if ((sqrt(((pP->x - pCenter->x)*(pP->x - pCenter->x)) + ((pP->y - pCenter->y)*(pP->y - pCenter->y))) <= Radius))
		return 1;
	else
		return 0;
}


/*
This function checks if the point Pos is colliding with the rectangle
whose center is Rect, width is "Width" and height is Height
*/
int StaticPointToStaticRect(Vector2D *pPos, Vector2D *pRect, float Width, float Height)
{
	if ((pPos->x < (pRect->x - Width / 2)) || (pPos->x >(pRect->x + Width / 2)) || (pPos->y < (pRect->y - Height / 2)) || (pPos->y < (pRect->y - Height / 2)))
		return 0;
	else
		return 1;
}

/*
This function checks for collision between 2 circles.
Circle0: Center is Center0, radius is "Radius0"
Circle1: Center is Center1, radius is "Radius1"
*/
int StaticCircleToStaticCircle(Vector2D *pCenter0, float Radius0, Vector2D *pCenter1, float Radius1)
{
	if ((sqrt((pCenter0->x - pCenter1->x) * (pCenter0->x - pCenter1->x) + (pCenter0->y - pCenter1->y) * (pCenter0->y - pCenter1->y))) <= (Radius0 + Radius1))
		return 1;
	else
		return 0;
}

/*
This functions checks if 2 rectangles are colliding
Rectangle0: Center is pRect0, width is "Width0" and height is "Height0"
Rectangle1: Center is pRect1, width is "Width1" and height is "Height1"
*/
int StaticRectToStaticRect(Vector2D *pRect0, float Width0, float Height0, Vector2D *pRect1, float Width1, float Height1)
{

	if (((pRect0->x - Width0 / 2) > (pRect1->x + Width1 / 2)) || ((pRect1->x - Width1 / 2) > (pRect0->x + Width0 / 2)) || ((pRect0->y + Height0 / 2) < (pRect1->y - Height1 / 2)) || ((pRect1->y + Height1 / 2) < (pRect0->y - Height0 / 2)))
		return 0;
	else
		return 1;
}

//////////////////////
// New to project 2 //
//////////////////////


/*
This function determines the distance separating a point from a line

 - Parameters
	- P:		The point whose location should be determined
	- LS:		The line segment

 - Returned value: The distance. Note that the returned value should be:
	- Negative if the point is in the line's inside half plane
	- Positive if the point is in the line's outside half plane
	- Zero if the point is on the line
*/
float StaticPointToStaticLineSegment(Vector2D *P, LineSegment2D *LS)
{

	Vector2D vec;

	Vector2DSub(&vec,P, &LS->mP0);
	return Vector2DDotProduct(&vec,&LS->mN);
	
	//return 0.0f;
}


/*
This function checks whether an animated point is colliding with a line segment

 - Parameters
	- Ps:		The point's starting location
	- Pe:		The point's ending location
	- LS:		The line segment
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)

 - Returned value: Intersection time t
	- -1.0f:				If there's no intersection
	- Intersection time:	If there's an intersection
*/
float AnimatedPointToStaticLineSegment(Vector2D *Ps, Vector2D *Pe, LineSegment2D *LS, Vector2D *Pi)
{	//done
	float t;
	Vector2D  peps,  pip0, p1p0, pip1, p0p1;
	//Vector2DNormalize(&LS->mN, &LS->mN);
	float nps = Vector2DDotProduct(&LS->mN, Ps);
	float np0 = Vector2DDotProduct(&LS->mN, &LS->mP0);	//n.P0
	float npe = Vector2DDotProduct(&LS->mN, Pe);	//n.Pe
	//float res4 = Vector2DDotProduct(&LS->mN, &LS->mP0);	//n.P0
	Vector2DSub(&peps, Pe, Ps);	//v vector which is Pe-Ps
	float nv = Vector2DDotProduct(&LS->mN, &peps); //n.v
	//calculate Pi
	t = (np0 - nps) / nv;
	//AESysPrintf("t: %f \n",t);
	Vector2DScaleAdd(Pi,&peps, Ps, t);

	Vector2DSub(&pip0, Pi, &LS->mP0);  // Pi-P0
	Vector2DSub(&p1p0, &LS->mP1, &LS->mP0);	//P1-P0
	float res6 = Vector2DDotProduct(&pip0, &p1p0); //(pip0).(p1p0)
	Vector2DSub(&pip1, Pi, &LS->mP1);  // Pi-P1
	Vector2DSub(&p0p1, &LS->mP0, &LS->mP1); //p0-p1
	float res7 = Vector2DDotProduct(&pip1,&p0p1);
	
	if(nps<np0 && npe<np0)
		return -1.0f;
	else if(nps>np0 && npe>np0)
		return -1.0f;
	else if (nv == 0)
		return -1.0f;
	else if (res6 < 0)
		return -1.0f;
	else if (res7 < 0)
		return -1.0f;
	else
		return t;

}


/*
This function checks whether an animated circle is colliding with a line segment

 - Parameters
	- Ps:		The center's starting location
	- Pe:		The center's ending location
	- Radius:	The circle's radius
	- LS:		The line segment
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)

 - Returned value: Intersection time t
	- -1.0f:				If there's no intersection
	- Intersection time:	If there's an intersection
*/




float AnimatedCircleToStaticLineSegment(Vector2D *Ps, Vector2D *Pe, float Radius, LineSegment2D *LS, Vector2D *Pi)
{
	// done
	float t;
	Vector2D  peps, pip0, p1p0, pip1, p0p1;
	float nps = Vector2DDotProduct(&LS->mN, Ps);
	float np0 = Vector2DDotProduct(&LS->mN, &LS->mP0);	//n.P0
	float npe = Vector2DDotProduct(&LS->mN, Pe);	//n.Pe
	Vector2DSub(&peps, Pe, Ps);	//v vector which is Pe-Ps
	float nv = Vector2DDotProduct(&LS->mN, &peps); //n.v
	if ((StaticPointToStaticLineSegment(Ps, LS)) < 0)
		Radius = Radius * -1;
	t = (np0 - nps + Radius) / (nv);
	Vector2DScaleAdd(Pi, &peps, Ps, t);

	Vector2DSub(&pip0, Pi, &LS->mP0);  // Pi-P0
	Vector2DSub(&p1p0, &LS->mP1, &LS->mP0);	//P1-P0
	float res6 = Vector2DDotProduct(&pip0, &p1p0); //(pip0).(p1p0)
	Vector2DSub(&pip1, Pi, &LS->mP1);  // Pi-P1
	Vector2DSub(&p0p1, &LS->mP0, &LS->mP1); //p0-p1
	float res7 = Vector2DDotProduct(&pip1, &p0p1);

	if ((nps - np0) < Radius && (npe - np0) < Radius)
		return -1.0f;
	else if ((nps - np0) > Radius && (npe - np0) > Radius)
		return -1.0f;
	else if (res7 < 0)
		return -1.0f;
	else if (res6 < 0)
		return -1.0f;

	else
		return t;
}


/*
This function reflects an animated point on a line segment.
It should first make sure that the animated point is intersecting with the line 

 - Parameters
	- Ps:		The point's starting location
	- Pe:		The point's ending location
	- LS:		The line segment
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)
	- R:		Reflected vector R

 - Returned value: Intersection time t
	- -1.0f:				If there's no intersection
	- Intersection time:	If there's an intersection
*/
float ReflectAnimatedPointOnStaticLineSegment(Vector2D *Ps, Vector2D *Pe, LineSegment2D *LS, Vector2D *Pi, Vector2D *R)
{
	
	float t = AnimatedPointToStaticLineSegment(Ps, Pe,  LS, Pi);
	if(t == -1.0f)
	{
		return t;
	}
	Vector2D i,res;
	Vector2DSub(&i, Pe, Pi);	//i
	float in = -2 * Vector2DDotProduct( &i, &LS->mN); //i.n
	Vector2DScaleAdd(R, &LS->mN, &i, in);
	return t;
	

}


/*
This function reflects an animated circle on a line segment.
It should first make sure that the animated point is intersecting with the line 

 - Parameters
	- Ps:		The center's starting location
	- Pe:		The center's ending location
	- Radius:	The circle's radius
	- LS:		The line segment
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)
	- R:		Reflected vector R

 - Returned value: Intersection time t
	- -1.0f:				If there's no intersection
	- Intersection time:	If there's an intersection
*/
float ReflectAnimatedCircleOnStaticLineSegment(Vector2D *Ps, Vector2D *Pe, float Radius, LineSegment2D *LS, Vector2D *Pi, Vector2D *R)
{
	//Done
	float t = AnimatedCircleToStaticLineSegment(Ps, Pe, Radius, LS, Pi);
	if (t == -1.0f)
	{
		return t;
	}

	Vector2D i, res;
	Vector2DSub(&i, Pe, Pi);	//i
	float in = -2 * Vector2DDotProduct(&i, &LS->mN); //i.n
													 //float mult = 2 * in;
													 //float PidotmN = -2* Vector2DDotProduct()
													 //Vector2DScale(&res, &LS->mN, mult);	//	2*(in).n
	Vector2DScaleAdd(R, &LS->mN, &i, in);
	return t;

	//Vector2D i, res;
	//
	//Vector2DSub(&i, Pe, Pi);	//i
	//float in = Vector2DDotProduct(&i, &LS->mN); //i.n
	//float mult = 2 * in;
	//Vector2DScale(&res, &LS->mN, mult);	//	2*(in).n

	//Vector2DSub(R, &i, &res);
	//return -1.0f;
}


/*
This function checks whether an animated point is colliding with a static circle

 - Parameters
	- Ps:		The point's starting location
	- Pe:		The point's ending location
	- Center:	The circle's center
	- Radius:	The circle's radius
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)

 - Returned value: Intersection time t
	- -1.0f:		If there's no intersection
	- Intersection time:	If there's an intersection
*/
/*
float AnimatedPointToStaticCircle(Vector2D *Ps, Vector2D *Pe, Vector2D *Center, float Radius, Vector2D *Pi)
{

	float ti,t0,t1,a,b,c,pscv,psc2,det,m, pscmag,pscdist,n;
	Vector2D v, psc,mult,vnorm;
	Vector2DSub(&v, &Pe, &Ps);	//v vector which is Pe-Ps
	a = Vector2DDotProduct(&v, &v); //a=v.v
	Vector2DSub(&psc, &Center, &Ps);  //PsC = Centre - Ps
	pscv = Vector2DDotProduct(&psc, &v);
	b = -2 * pscv; //b = -2(psc).v
	psc2 = Vector2DDotProduct(&psc, &psc);
	c = psc2 - Radius * Radius;
	det = sqrt(b*b - 4 * a*c);
	
	t0 = (-b - (det)) / (2 * a);
	t1 = (-b + (det)) / (2 * a);

	Vector2DNormalize(&vnorm, &v);
	m = Vector2DDotProduct(&psc, &vnorm);
	
	
	pscmag = Vector2DSquareDistance(&Center, &Ps);
	n = pscmag - m*m;
	
	pscdist =  Vector2DDistance(Ps, Center);


	if((m<0 && (pscdist > Radius))||(n*n>Radius*Radius))
		return -1.0f;
	else 
		return ti = min(t0, t1);

	
	
}

*/

/*
This function reflects an animated point on a static circle.
It should first make sure that the animated point is intersecting with the circle 

 - Parameters
	- Ps:		The point's starting location
	- Pe:		The point's ending location
	- Center:	The circle's center
	- Radius:	The circle's radius
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)
	- R:		Reflected vector R

 - Returned value: Intersection time t
	- -1.0f:		If there's no intersection
	- Intersection time:	If there's an intersection
*/
float ReflectAnimatedPointOnStaticCircle(Vector2D *Ps, Vector2D *Pe, Vector2D *Center, float Radius, Vector2D *Pi, Vector2D *R)
{
	return -1.0f;
}


/*
This function checks whether an animated circle is colliding with a static circle

 - Parameters
	- Center0s:		The starting position of the animated circle's center 
	- Center0e:		The ending position of the animated circle's center 
	- Radius0:		The animated circle's radius
	- Center1:		The static circle's center
	- Radius1:		The static circle's radius
	- Pi:			This will be used to store the intersection point's coordinates (In case there's an intersection)

 - Returned value: Intersection time t
	- -1.0f:		If there's no intersection
	- Intersection time:	If there's an intersection
*/
float AnimatedCircleToStaticCircle(Vector2D *Center0s, Vector2D *Center0e, float Radius0, Vector2D *Center1, float Radius1, Vector2D *Pi)
{
	return -1.0f;
}


/*
This function reflects an animated circle on a static circle.
It should first make sure that the animated circle is intersecting with the static one 

 - Parameters
	- Center0s:		The starting position of the animated circle's center 
	- Center0e:		The ending position of the animated circle's center 
	- Radius0:		The animated circle's radius
	- Center1:		The static circle's center
	- Radius1:		The static circle's radius
	- Pi:			This will be used to store the intersection point's coordinates (In case there's an intersection)
	- R:			Reflected vector R

 - Returned value: Intersection time t
	- -1.0f:		If there's no intersection
	- Intersection time:	If there's an intersection
*/
float ReflectAnimatedCircleOnStaticCircle(Vector2D *Center0s, Vector2D *Center0e, float Radius0, Vector2D *Center1, float Radius1, Vector2D *Pi, Vector2D *R)
{
	return -1.0f;
}
