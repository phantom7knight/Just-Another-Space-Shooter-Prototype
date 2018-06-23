#include "HomingEnemy.h"


#include "Enemy.h"

#include "gameobject.h"
#include "component.h"
#include "Vector2D.h"
#include "ObjectFactory.h"
#include "Body.h"

#include "Eventmanager.h"
#include "controller.h"

class gameobject;
extern EventManager *pEM;

//getting windows limits

extern float  winMaxX;
extern float  winMaxY;
extern float  winMinX;
extern float  winMinY;



HomingEnemy::HomingEnemy() :component(COMPONENT_TYPES::COMPONENT_ENEMY)
{
	mposx = 0;
	mposy = 0;
	isup = false;
}


HomingEnemy::~HomingEnemy()
{
}



void HomingEnemy::update(void)
{


	


	int count;
	transform *ptrans = static_cast<transform*>(mpowner->getcomponent(COMPONENT_TYPES::COMPONENT_TRANSFORM));
	//if (result == false)
	if (!isup)
	{
		if (ptrans->mposy <= 300)
		{
			ptrans->mposy++;

		}
		else {
			isup = true;
		}
		//result = true;
	}

	if (isup) {

		if (ptrans->mposy >0)
		{


			ptrans->mposy--;
		}
		else {
			isup = false;
		}


	}


}


void HomingEnemy::serialize(FILE **fp)
{
	int sub;


	fscanf(*fp, "%d\n", &sub);

	if (1 == sub)
		pEM->Subscribe(EventType::PLAYER_HIT, this->mpowner);

}



void HomingEnemy::HandleEvent(Event *pEvent)
{
	if (EventType::PLAYER_HIT == pEvent->mtype)
	{
		PlayerHitEvent *pREvent = (PlayerHitEvent *)pEvent;

		
		transform *ptr = (transform *)mpowner->getcomponent(COMPONENT_TYPES::COMPONENT_TRANSFORM);

		gameobject *gam = mpowner;

		//if(gam->type == SHIP)



	}
}
