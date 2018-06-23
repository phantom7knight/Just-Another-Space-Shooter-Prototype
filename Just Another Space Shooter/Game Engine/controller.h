#pragma once

#include "component.h"
#include "inputmanager.h"

class SDL_Surface;
class component;
class gameobject;

//Player Hit class 

class PlayerHitEvent : public Event
{
public:
	PlayerHitEvent();
	~PlayerHitEvent() {}
};

class Pause : public Event
{
public:
	Pause();
	~Pause() {}
};


class controller:public component
{
public:
	controller();
	~controller();

	void update(void);

	SDL_Surface *msprite;

	bool home_around_;
	gameobject* target;
	float dotproduct;

	void serialize(FILE **fp);
	void Initialize() {}
	void HandleEvent(Event *pEvent);
	//gameobject *mpowner;

};

