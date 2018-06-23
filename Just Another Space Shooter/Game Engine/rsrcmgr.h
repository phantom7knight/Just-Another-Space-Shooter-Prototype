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



//#pragma once
#ifndef rsrcmgr_H
#define rsrcmgr_H

#include "phantomengine.h"
#include <string.h>
#include <unordered_map>
#include"SDL_stdinc.h"
class rscmanager
{
public:
	rscmanager();
	~rscmanager();

	SDL_Surface *loadsurface(char* rfilepath);//getsurface

	void Getsurface();
	void UpdateScreen(SDL_Window* pwindow, SDL_Surface* pSurface);


private:
	std::unordered_map<std::string, SDL_Surface*>mSurface;
	SDL_Surface* ScreenImage[4] = { NULL,NULL, NULL, NULL };

};
#endif