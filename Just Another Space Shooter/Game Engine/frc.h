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
#ifndef frc_H
#define frc_H
#include "SDL_stdinc.h"


class frameratecontroller
{
public:
	frameratecontroller(unsigned int maxframerate);
	~frameratecontroller();

	void framestart(void);
	void frameend(void);
	unsigned int GetFrameTime();

private:
	unsigned int rmaxframerate;
	unsigned int rticksperframe;
	unsigned int rtickstart;
	unsigned int rtickend;
	unsigned int rframetime;

};


#endif