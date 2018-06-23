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





#include "inputmanager.h"
#include<SDL_config.h>
#include<memory.h>
#include<SDL_keyboard.h>
#include"frc.h"

inputmanager::inputmanager()
{
	xpos = 0;
	ypos = 0;
	xvel = 0;
	yvel = 0;

	memset(mcurrentstate,0, 512*sizeof(Uint8));

}


//inputmanager::~inputmanager()
//{
//}


void inputmanager::update(void)
{
	int fetchednum = 0;
	const Uint8* currentkeystate = SDL_GetKeyboardState(&fetchednum);
	if (fetchednum > 512) fetchednum = 512;
	//copy from current to previous
	memcpy(mprevstate, mcurrentstate, fetchednum * sizeof(Uint8));
	//get the key press to the current state
	memcpy(mcurrentstate, currentkeystate, fetchednum*sizeof(Uint8));


}

bool inputmanager::iskeypressed(unsigned int keyscancode)
{
	if (keyscancode > 512)
		return false;


	return mcurrentstate[keyscancode] == 1;
}


bool inputmanager::iskeytriggered(unsigned int keyscancode)
{
	if (keyscancode > 512)
		return false;

	if (mcurrentstate[keyscancode] && !mprevstate[keyscancode])
		return true;


	return false;
}


bool inputmanager:: iskeyreleased(unsigned int keyscancode)
{
	if (keyscancode > 512)
		return false;

	if (mcurrentstate[keyscancode] && mprevstate[keyscancode])
		return true;


	return false;
}
