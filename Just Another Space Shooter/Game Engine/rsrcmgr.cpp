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




#include "rsrcmgr.h"
#include "stdio.h"
#include"SDL_surface.h"
//#include"phantomengine.h"

extern bool gameactive;
extern bool controlleractive;
extern bool win;
extern bool lose_scene;



rscmanager::rscmanager()
{

}



rscmanager::~rscmanager()
{
	
}

SDL_Surface *rscmanager::loadsurface(char *pPath)
{
	SDL_Surface *pSurface = mSurface[pPath];

	if (pSurface)
	{
		return pSurface;
	}

	pSurface = SDL_LoadBMP(pPath);
	
	if (pSurface)
	{
		mSurface[pPath] = pSurface;
	}

	return pSurface;

}




void rscmanager::Getsurface()
{
	ScreenImage[0] = loadsurface("controls.bmp");//control
	if (NULL == ScreenImage[0])
		printf("control Image NULL \n");
	ScreenImage[1] = NULL;// loadsurface("Girl-wat.bmp");//win scenario
	/*if (NULL == ScreenImage[1])
		printf("Null Image 1\n");*/
	ScreenImage[2] = loadsurface("Game_over_prefinal.bmp");//lose scenario
	if (NULL == ScreenImage[2])
		printf("Null Image 2\n");
	ScreenImage[3] = loadsurface("start1.bmp");//start
	if (NULL == ScreenImage[3])
		printf("start Image NULL \n");


}


void rscmanager::UpdateScreen(SDL_Window* pwindow, SDL_Surface* pSurface)
{
	if (win)
	{
		SDL_BlitSurface(ScreenImage[1], NULL, pSurface, NULL);//win
		SDL_UpdateWindowSurface(pwindow);
	}

	//else 
	if(lose_scene == true)
	{
		SDL_BlitSurface(ScreenImage[2], NULL, pSurface, NULL);//lose
		SDL_UpdateWindowSurface(pwindow);
	}


	 if (controlleractive)
	{
		SDL_BlitSurface(ScreenImage[0], NULL, pSurface, NULL);//controls
		SDL_UpdateWindowSurface(pwindow);
		SDL_Delay(1000);
		gameactive = true;
		controlleractive = false;
	}

	else if (gameactive == false)
	{
		SDL_BlitSurface(ScreenImage[3], NULL, pSurface, NULL);//start
		SDL_UpdateWindowSurface(pwindow);
	}


}

