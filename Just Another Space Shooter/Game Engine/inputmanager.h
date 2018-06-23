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




#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include<SDL_stdinc.h>
//#include "phantomengine.h"
class inputmanager
{
	private:
		Uint8 mcurrentstate[512];
		Uint8 mprevstate[512];
		//x and y positions 
		int xpos, ypos;

		//velocity along x and y
		int xvel, yvel;

	public:
		inputmanager();
		//~inputmanager();

		void update(void);

		bool iskeypressed(unsigned int keyscancode);
		bool iskeytriggered(unsigned int keyscancode);
		bool iskeyreleased(unsigned int keyscancode);
};

#endif // !INPUTMANAGER_H
