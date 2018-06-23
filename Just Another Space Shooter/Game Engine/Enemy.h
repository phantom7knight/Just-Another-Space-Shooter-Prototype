#pragma once

#include "component.h"
#include "transform.h"


class Enemy : public component
{
public:
	Enemy();
	~Enemy();

	void update(void);
	//void update2(void);

	void serialize(FILE **fp);
	void HandleEvent(Event *pEvent);

	bool isup;
	int mposx;
	int mposy;




};

