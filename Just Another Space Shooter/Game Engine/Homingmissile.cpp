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




#include "Homingmissile.h"
#include "gameobject.h"
#include "ObjectFactory.h"
#include "Body.h"
#include "sprite.h"
#include "frc.h"
#include "Matrix2D.h"
#include "Eventmanager.h"
#include "controller.h"


extern EventManager *pEM;
extern GameObjectManager *pGOM;
extern frameratecontroller *pfrc;

#define MISSILE_TURNRATE 3.14/2.0
#define MISSILE_SPEED 0.3

//getting windows limits

extern float  winMaxX;
extern float  winMaxY;
extern float  winMinX;
extern float  winMinY;



Homingmissile::Homingmissile() :component(COMPONENT_TYPES::COMPONENT_HOMINGMISSILE)
{
	mposx = 0;
	mposy = 0;
	home_around_ = false;
}


Homingmissile::~Homingmissile()
{
}

/*

void Homingmissile::update(void)
{
	
	gameobject* missile;
	missile = mpowner;

	if (missile->type == HOMINGMISSILE)
	{
		
		gameobject* mtarget = NULL;


		for (gameobject* pOB : pGOM->asteroids)
		{
			for (auto i : pOB->mcomponents)
			{
				sprite* pSprite = (sprite *)pOB->getcomponent(COMPONENT_TYPES::COMPONENT_SPRITE);


				if (pOB->type == ASTEROID)
				{
					if (target == NULL)
					{
						float mindistance;
						int flag = 0;

						//check

						gameobject* asteroidobj;
						asteroidobj = pSprite->mpowner;

						transform* missileptr = (transform *)missile->getcomponent(COMPONENT_TYPES::COMPONENT_TRANSFORM);
						transform* asteroidptr = (transform *)asteroidobj->getcomponent(COMPONENT_TYPES::COMPONENT_TRANSFORM);

						if (!flag)
						{
							flag = 1;
							mindistance = Vector2DDistance(&missileptr->position, &asteroidptr->position);
							if (mindistance > 0.5)
							{
								return;
							}
							else
							{
								target = asteroidobj;
							}
						}
						
						else if (Vector2DDistance(&missileptr->position, &asteroidptr->position) < mindistance)
						{
							mindistance = Vector2DDistance(&missileptr->position, &asteroidptr->position);
							if (mindistance > 0.5)
							{
								return;
							}
							else
							{
								target = asteroidobj;
							}
						}

						if (flag)
						{
							target = mtarget;
						}

					}

					//If there is target
					else //if(target != NULL)
					{

						if (missile->isactive_)
						{
							Vector2D killShotVelocity;
							Vector2D normalVect;    // normal mapped to generate dot product onto the target
							float dotProduct, angle;

							Body* killShotBody = (Body *)target->getcomponent(COMPONENT_TYPES::COMPONENT_BODY);


							Vector2DSet(&normalVect, -killShotBody->mvely, killShotBody->mvelx);     // computing normal vector by setting the x value as -y and y value as x

							transform* pTarget = (transform *)target->getcomponent(COMPONENT_TYPES::COMPONENT_TRANSFORM);
							transform* pKillShotTransform = (transform *)missile->getcomponent(COMPONENT_TYPES::COMPONENT_TRANSFORM);

							Vector2DSub(&killShotVelocity, &pTarget->position, &pKillShotTransform->position);

							dotProduct = Vector2DDotProduct(&killShotVelocity, &normalVect);

							Vector2D tempVelocity;    // current velocity of Kill Shot

							tempVelocity.x = killShotBody->mvelx;
							tempVelocity.y = killShotBody->mvelx;


							if (dotProduct < 0)
							{
								pKillShotTransform->angle -= 0.1 * pfrc->GetFrameTime();//0.1
							}
							else
							{
								pKillShotTransform->angle += 0.1  * pfrc->GetFrameTime();
							}

							tempVelocity.x = cosf((pKillShotTransform->angle + 90)* 3.14 / 180);
							tempVelocity.y = sinf((pKillShotTransform->angle + 90)* 3.14 / 180);

							tempVelocity.x *= 0.1;
							tempVelocity.y *= 0.1;

							killShotBody->mvelx = tempVelocity.x;
							killShotBody->mvely = tempVelocity.y;

						}

					}
				}
				}
			}
		}
	}


	*/

void Homingmissile::update(void)
{	
	
			for (auto gameObjects : pGOM->gameobjects)
			{
				
				if (gameObjects->type == ASTEROID)
				{
					home_around_ = true;
					if (!target) {
						
						target = gameObjects;
						break;
					}
				}
			}


		if (!home_around_) {

			return;
		}
		home_around_ = false;
		//	target = sgpShip;

		if (target == NULL)
		{
			for (auto gameObjects : pGOM->gameobjects)
			{
				if (gameObjects->type == ASTEROID)
				{
					home_around_ = true;
					if (!target) {

						target = gameObjects;
						break;
					}
				}
			}
		}




		Body *targetBody = static_cast<Body*>(target->getcomponent(COMPONENT_TYPES::COMPONENT_BODY));
		transform *targetTrans = static_cast<transform*>(target->getcomponent(COMPONENT_TYPES::COMPONENT_TRANSFORM));

		Body *missileBody = static_cast<Body*>(this->mpowner->getcomponent(COMPONENT_TYPES::COMPONENT_BODY));
		transform *missileTrans = static_cast<transform*>(this->mpowner->getcomponent(COMPONENT_TYPES::COMPONENT_TRANSFORM));
		/*
		normal=glm::normalize(missileBody->mBodyVel);
		normal.y = -normal.y;

		missileDir = targetBody->mBodyPos - missileBody->mBodyPos;

		dotProduct = glm::dot(missileDir,normal);

		if (dotProduct < 0)
		{
		missileTrans->mAngle -= MISSILE_TURNRATE*dt;
		}
		else
		{
		missileTrans->mAngle += MISSILE_TURNRATE*dt;
		}

		newVel.x= cosf((missileTrans->mAngle + 90)* 3.14 / 180.0f)*MISSILE_SPEED;
		newVel.y = sinf((missileTrans->mAngle + 90)* 3.14 / 180.0f)*MISSILE_SPEED;

		missileBody->mBodyVel = newVel;		*/



		Matrix2D rotation;
		Vector2D target_vector, normalized_target_vector, normal;
		float dist_target, cos_angle, angle, turn;


		Vector2D missileposition;
		Vector2DSet(&missileposition, missileBody->mposx, missileBody->mposy);


		Vector2D targetPosition;
		Vector2DSet(&targetPosition, targetBody->mposx, targetBody->mposy);


		// target vector
		Vector2DSub(&target_vector, &targetPosition, &missileposition);
		// unit vector in dir of target
		Vector2DNormalize(&normalized_target_vector, &target_vector);
		//distance between target and missile
		//	Vector2DDistance(mis, mis->mpComponent_Target);
		//angle between normalized_target and missile

		Vector2D missileVel;
		Vector2DSet(&missileVel, missileBody->mvelx, missileBody->mvely);
		cos_angle = Vector2DDotProduct(&normalized_target_vector, &missileVel);

		angle = glm::radians(acosf(cos_angle));
		//calculating normal
		Matrix2DRotRad(&rotation, 90);
		Matrix2DMultVec(&normal, &rotation, &missileVel);
		// DOT product for turning
		turn = Vector2DDotProduct(&normal, &target_vector);
		if (turn>0)
		{
			/*if (angle<MISSILE_TURNRATE)
			{
				missileTrans-> += glm::degrees(angle);
			}
			else
			}
			{*/

				missileTrans->angle += glm::degrees(angle);

			Vector2D missinewVel;
			missinewVel.x = missileBody->mvelx;
			missinewVel.y = missileBody->mvely;

			Vector2DFromAngle(&missinewVel, (missileTrans->angle));
			Vector2DScale(&missinewVel, &missinewVel, .9f);
			missileBody->mvelx = missinewVel.x;
			missileBody->mvelx = missinewVel.y;
		}
		else
		{
			/*if (angle<MISSILE_TURNRATE)
			{
				missileTrans->mAngle += glm::degrees(angle);
			}
			else
			{
			}*/
				missileTrans->angle -= glm::degrees(angle);


			Vector2D missinewVel;
			missinewVel.x = missileBody->mvelx;
			missinewVel.y = missileBody->mvely;

			Vector2DFromAngle(&missinewVel, (missileTrans->angle));
			Vector2DScale(&missinewVel, &missinewVel, .9);
			missileBody->mvelx = missinewVel.x;
			missileBody->mvely = missinewVel.y;

		}

		missileBody->mvelx = cosf((missileTrans->angle + 90)* 3.14 / 180.0f)*MISSILE_SPEED;
		missileBody->mvely = sinf((missileTrans->angle + 90)* 3.14 / 180.0f)*MISSILE_SPEED;

}







void Homingmissile::serialize(FILE **fp)
{
	int sub;


	fscanf(*fp, "%d\n", &sub);

	if (1 == sub)
		pEM->Subscribe(EventType::PLAYER_HIT, this->mpowner);

}



void Homingmissile::HandleEvent(Event *pEvent)
{

	//printf("YOLO\n");
	if (EventType::PLAYER_HIT == pEvent->mtype)
	{
		printf("YOLO 2 \n");

		home_around_ = false;
		target = nullptr;

		/*
		printf("YOLO 2 \n");
		PlayerHitEvent *pREvent = (PlayerHitEvent *)pEvent;

		transform *ptr = (transform *)mpowner->getcomponent(COMPONENT_TYPES::COMPONENT_TRANSFORM);
		//mpowner->type = SHIP;
		gameobject* obj = mpowner;


		if (ptr)
		{

			home_around_ = false;
			target = nullptr;
			//ptr->mposx += 50.0;
			{
				//obj->isactive_ = false;
				printf("Enemy attacked the ship \n");

			}
		}*/


	}
}