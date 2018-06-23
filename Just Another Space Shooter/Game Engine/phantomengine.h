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


//#include<iostream>
#include <SDL.h>
#include "stdio.h"
#include "inputmanager.h"
#include "frc.h"
#include "rsrcmgr.h"
#include "component.h"
#include<Windows.h>

//
//FILE _iob[] = { *stdin, *stdout, *stderr };
//
//extern "C" FILE * __cdecl __iob_func(void)
//{
//	return _iob;
//}
//
//#pragma comment(lib, "legacy_stdio_definitions.lib")	


class phantomengine
{
public:

	phantomengine();
	//~phantomengine();

	//starts SDL and creates a window
	bool init();

	//loads a media
	bool loadmedia();

	//frees media and shuts down SDL
	void close();

private:
	SDL_Window *pWindow;
	SDL_Surface* pImages[5];
	SDL_Surface* gsurface;
	SDL_Surface* currentsurface;
	bool appIsRunning;
	int error;
	const Uint8* currentkeystate;
	int posX, posY;
	int counter_;
};


