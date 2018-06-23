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


#include"frc.h"
#include "limits.h"
#include "SDL_timer.h"
#include "stdio.h"

frameratecontroller::frameratecontroller(unsigned int maxframerate)
{
	if (0 == maxframerate)
		maxframerate = UINT_MAX;

	rmaxframerate = maxframerate;
	rticksperframe = 1000 / rmaxframerate;
	rtickstart = 0;
	rtickend = 0;
	rframetime = 0;
}

frameratecontroller::~frameratecontroller()
{

}

void frameratecontroller::framestart(void)
{
	//rticksperframe
	rtickstart = SDL_GetTicks();
}


void frameratecontroller::frameend(void)
{
	rtickend = SDL_GetTicks();
	while (rtickend - rtickstart < rticksperframe)
	{
		rtickend = SDL_GetTicks();
	}

	rframetime = rtickend - rtickstart;
}


unsigned int frameratecontroller::GetFrameTime(void)
{
	return rframetime;
}