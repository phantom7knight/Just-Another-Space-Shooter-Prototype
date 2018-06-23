#include <Windows.h>
#include <cstdio>
#include "SDL.h"
#include "controller.h"
#include "inputmanager.h"
#include "component.h"
#include "SDL_Keyboard.h"
#include "gameobject.h"
#include "transform.h"
#include "Body.h"
#include "ObjectFactory.h"
#include "Matrix2D.h"
#include "Eventmanager.h"
#include "Physicsmanager.h"
#include "frc.h"
#include "Vector2D.h"
#include "sprite.h"
#include <stdio.h>
//#include <iostream>
extern frameratecontroller *pfrc;
extern gameobject* ship;
extern gameobject* bullet;


#define GAME_OBJ_INST_NUM_MAX  40
//frameratecontroller *pfrchere = new frameratecontroller();

#define turn 0.2
#define MISSILE_SPEED 0.3

//float frametime = pfrc->GetFrameTime();

extern inputmanager* pinputmanager;
extern EventManager *pEM;
extern ObjectFactory *objfactory;
extern GameObjectManager *pGOM;
//Body *pBody = new Body();

Pause::Pause() : Event(EventType::PAUSE)
{

}



PlayerHitEvent::PlayerHitEvent() :Event(EventType::PLAYER_HIT)
{

}





controller::controller():component(COMPONENT_TYPES::COMPONENT_CONTROLLER)
{
	mpowner = NULL;
}


controller::~controller()
{
}

void controller::update()
{	
	Body *ptr = static_cast<Body *>(mpowner->getcomponent(COMPONENT_TYPES::COMPONENT_BODY));
	transform *pBody = static_cast<transform *>(mpowner->getcomponent(COMPONENT_TYPES::COMPONENT_TRANSFORM));
	if(pinputmanager->iskeypressed(SDL_SCANCODE_UP))	
	{
		
		//Vector2D unit_dir;
		//Vector2DSet(&unit_dir, cosf(ptr->angle), sinf(ptr->angle));

		////scaling for accel
		//Vector2DScale(&unit_dir, &unit_dir, (100 * 0.1));

		//// vnew
		//Vector2DAdd(&sgpShip->mpComponent_Physics->mVelocity, &sgpShip->mpComponent_Physics->mVelocity, &unit_dir);


		if (NULL != ptr)
		{
			float acclerationvalue = 0.5f;

			ptr->maccx = acclerationvalue * cosf((ptr->angle + 90) * 3.14 / 180);
			ptr->maccy = acclerationvalue * sinf((ptr->angle + 90) * 3.14 / 180);
		}
			//ptr->mtotalforcey += 1.5f;
			//ptr->mtotalforcey -= 0.8f;

		
	}
	
	if (pinputmanager->iskeypressed(SDL_SCANCODE_RIGHT))
	{

		//SDL_BlitSurface(pImages[1], NULL, gsurface, NULL);
		if (NULL != ptr)
		{
			
//			ptr->mtotalforcex += .58f;
			ptr->angle -= turn * pfrc->GetFrameTime();
			//ptr->angle -= turn *(float) frametime;

		}
			
		//ptr->mtotalforcex += .001f;
		//index = 4;
	}


	  if (pinputmanager->iskeypressed(SDL_SCANCODE_LEFT))
	{
		//SDL_BlitSurface(pImages[3], NULL, gsurface, NULL);
		if (NULL != ptr)
		{
			//ptr->mtotalforcex -= .001f;
			ptr->angle += turn * pfrc->GetFrameTime();
			//ptr->angle += (turn * frametime);
			
		}
			
		//index = 4;
	}
	 if (pinputmanager->iskeyreleased(SDL_SCANCODE_DOWN))
	{
		float acclerationvalue =	-0.5f;

		ptr->maccx = acclerationvalue * cosf((ptr->angle + 90) * 3.14 / 180);
		ptr->maccy = acclerationvalue * sinf((ptr->angle + 90) * 3.14 / 180);

	}


	 if (pinputmanager->iskeytriggered(SDL_SCANCODE_SPACE))
	 {

		 printf("SPACE is triggered \n");
		 //create game obj;
		 //add required componets
		 //set values of bullet using ship values
		// bullet->set_is_active(true);

		 for (gameobject* pObj : pGOM->bullets)
		 {
			 // here pobj = bullets
			 //pObj->isactive_ = true;

			 if (pObj->isactive_ == false)
			 {
				 pObj->isactive_ = true;
				 //gameobject* ship = pBody->mpowner;//for transformation
				 transform* bulletpTr = (transform*)pObj->getcomponent(COMPONENT_TYPES::COMPONENT_TRANSFORM);
				 Body* bulletbody = (Body*)pObj->getcomponent(COMPONENT_TYPES::COMPONENT_BODY);

				 bulletpTr->mposx = pBody->mposx;
				 bulletpTr->mposy = pBody->mposy;

				 bulletbody->mposx = pBody->mposx;
				 bulletbody->mposy = pBody->mposy;

				 #define BULLET_SPEED 30.0f

				 bulletbody->maccx = ptr->maccx + (BULLET_SPEED * cosf((ptr->angle + 90) *3.14 / 180));
				 bulletbody->maccy = ptr->maccy + (BULLET_SPEED * sinf((ptr->angle + 90) *3.14 / 180));

				 break;
			 }

		 }


			
		
	 }

	 if (pinputmanager->iskeytriggered(SDL_SCANCODE_M))
	 {
		 printf("M is triggered \n");
		 //create game obj;
		 //add required componets
		 //set values of bullet using ship values
		 // bullet->set_is_active(true);
	/*
		 for (gameobject* pObj : pGOM->missile)
		 {
			 // here pobj = bullets
			 //pObj->isactive_ = true;

			 if (pObj->isactive_ == false)
			 {
				 pObj->isactive_ = true;
				 //gameobject* ship = pBody->mpowner;//for transformation
				 transform* bulletpTr = (transform*)pObj->getcomponent(COMPONENT_TYPES::COMPONENT_TRANSFORM);
				 Body* bulletbody = (Body*)pObj->getcomponent(COMPONENT_TYPES::COMPONENT_BODY);

				 bulletpTr->mposx = pBody->mposx;
				 bulletpTr->mposy = pBody->mposy;

				 bulletbody->mposx = pBody->mposx;
				 bulletbody->mposy = pBody->mposy;

				#define MISSILE_SPEED 30.0f

				 bulletbody->maccx = ptr->maccx + (MISSILE_SPEED * cosf((ptr->angle + 90) *3.14 / 180));
				 bulletbody->maccy = ptr->maccy + (MISSILE_SPEED * sinf((ptr->angle + 90) *3.14 / 180));

				 break;
			 }

		 }*/

		 for (gameobject* pObj : pGOM->missile)
		 {
			 // here pobj = bullets
			 //pObj->isactive_ = true;

			 if (pObj->isactive_ == false)
			 {
				 pObj->isactive_ = true;
				 //gameobject* ship = pBody->mpowner;//for transformation
				 transform* bulletpTr = (transform*)pObj->getcomponent(COMPONENT_TYPES::COMPONENT_TRANSFORM);
				 Body* bulletbody = (Body*)pObj->getcomponent(COMPONENT_TYPES::COMPONENT_BODY);

				 bulletpTr->mposx = pBody->mposx;
				 bulletpTr->mposy = pBody->mposy;

				 bulletbody->mposx = pBody->mposx;
				 bulletbody->mposy = pBody->mposy;

				#define BULLET_SPEED 30.0f

				 bulletbody->maccx = ptr->maccx + (BULLET_SPEED * cosf((ptr->angle + 90) *3.14 / 180));
				 bulletbody->maccy = ptr->maccy + (BULLET_SPEED * sinf((ptr->angle + 90) *3.14 / 180));

				 break;
			 }

		 }



	 }
		 
		 /*
		 for (auto gameObjects : pGOM->missile)
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

		 missileBody->mBodyVel = newVel;		



		 Matrix2D rotation;
		 Vector2D target_vector, normalized_target_vector, normal;
		 float dist_target, cos_angle, angle, turnM;


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
		 turnM = Vector2DDotProduct(&normal, &target_vector);
		 if (turnM>0)
		 {
			 /*if (angle<MISSILE_TURNRATE)
			 {
			 missileTrans-> += glm::degrees(angle);
			 }
			 else
			 }
			 {

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
			 }
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
		 */



	 

	 



	 if (pinputmanager->iskeytriggered(SDL_SCANCODE_P))
	{
		if (NULL != ptr)
		{
			Pause pPause;

			pEM->BroadcastEvent(&pPause);
			
		}
	}

	
}

void controller::serialize(FILE **fp)
{

}



void controller::HandleEvent(Event *pEvent)
{

	if (EventType::PLAYER_HIT == pEvent->mtype)
	{
		printf("YOLO 2 \n");

		home_around_ = false;
		target = nullptr;
	}
	/*if (EventType::COLLIDE == pEvent->mtype)
	{
		CollideEvent *pREvent = (CollideEvent *)pEvent;
		//pREvent->


		Body *pBody = (Body *)mpowner->getcomponent(COMPONENT_TYPES::COMPONENT_BODY);

		gameobject* gamobj = mpowner;


		if (pBody)
		{
			//pBody->mposx = 0.0f;
			gamobj->isactive_ = false;
		}


		PlayerHitEvent *pPHE = new PlayerHitEvent();
		//pPHE->mTimer = 2.0f;
		pEM->AddTimedevent(pPHE);	

		pPHE = new PlayerHitEvent();
		//pPHE->mTimer = 3.0f;
		pEM->AddTimedevent(pPHE);


	}*/
}




