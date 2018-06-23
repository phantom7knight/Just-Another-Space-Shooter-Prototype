#pragma once
#define COMPONENT


//#include <stdio.h>
#include "gameobject.h"
#include "Eventmanager.h"
enum COMPONENT_TYPES
{
	COMPONENT_TRANSFORM=1,
	COMPONENT_SPRITE, 
	COMPONENT_CONTROLLER,
	COMPONENT_UPDOWN,
	COMPONENT_BODY,
	COMPONENT_ENEMY,
	COMPONENT_HOMINGENEMY,
	COMPONENT_HOMINGMISSILE

};

class Event;
class component
{
public:
	component(unsigned int mtype);
	virtual ~component();

	virtual void update() = 0;

	virtual void serialize(FILE **fp)=0;

	//void HandleEvent(Event *pEvent);
	virtual void HandleEvent(Event *pEvent) {}
	gameobject *mpowner;
	unsigned int mtype;

};