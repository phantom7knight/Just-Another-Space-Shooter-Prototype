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

float posX[10] = { 0.69f,-0.45f,0.42f,-0.14f ,-0.1f,0.202f,-0.8,0.0f,0.39f,0.11f };
float posY[10] = { -0.70f,-0.9f,0.97f,-0.81f,0.72f,0.62f,-0.98f,0.99f,-0.89f,0.69f };



Enemy::Enemy() :component(COMPONENT_TYPES::COMPONENT_ENEMY)
{
	mposx = 0;
	mposy = 0;
	isup = false;
}


Enemy::~Enemy()
{
}



void Enemy::update(void)
{

	/*int ast_ct = rand() % 1;
	int i = 0;
	gameobject* pInst = mpowner;

	for (i = 0; i <= ast_ct; i++)
	{
		if (pInst->type == ASTEROID)
		{
			transform *pTr = static_cast<transform *>(pInst->getcomponent(COMPONENT_TYPES::COMPONENT_TRANSFORM));
			Body *pBody = static_cast<Body *>(pInst->getcomponent(COMPONENT_TYPES::COMPONENT_BODY));

			pTr->angle = rand() % 360 + 0;
			float asteroid_speed = static_cast <float>(rand()) / static_cast <float>(RAND_MAX); 
			pTr->scale = glm::vec3(0.2f, 0.2f, 0.2f);
			pInst->addcomponent(pTr);
			pBody->mposx = posX[rand() % 10 + 0];
			pBody->mposy = posY[rand() % 10 + 0];

			//pInst->type = ASTEROID; 






	}*/

	int ast_ct = rand() % 1;
	int i = 0;
	float xr, yr, vxr, vyr, scx, scy, r, l, t, b;
	//r = ;
	l = winMinX;
	//t = ();
	b = winMinY;
	 gameobject* pInst = mpowner;
	for (i = 0; i <= ast_ct; i++)
	{
		

		if (pInst->type == ASTEROID)
		{

			xr = rand() % (int)winMaxX;
			yr = rand() % (int)winMaxY;
			/*vxr = rand() % 199;
			vyr = rand() % 160;*/
			/*scx = rand() % 140;
			scy = rand() % 190;*///yeha pe

			transform *pTr = static_cast<transform *>(pInst->getcomponent(COMPONENT_TYPES::COMPONENT_TRANSFORM));
			Body *pBody = static_cast<Body *>(pInst->getcomponent(COMPONENT_TYPES::COMPONENT_BODY));

			//Vector2DSet(&pInst->mpComponent_Transform->mPosition, xr, yr);
			pBody->mvelx = 0.1;
			//pBody->mvelx = 0.1;
			/*pInst->mpComponent_Transform->mScaleX = scx;
			pInst->mpComponent_Transform->mScaleY = scy;*///yeha pe
			

			
		}
	}
	







}


void Enemy::serialize(FILE **fp)
{
	int sub;


	fscanf(*fp, "%d\n", &sub);

	if (1 == sub)
		pEM->Subscribe(EventType::PLAYER_HIT, this->mpowner);

}



void Enemy::HandleEvent(Event *pEvent)
{
	if (EventType::PLAYER_HIT == pEvent->mtype)
	{
		PlayerHitEvent *pREvent = (PlayerHitEvent *)pEvent;

		transform *ptr = (transform *)mpowner->getcomponent(COMPONENT_TYPES::COMPONENT_TRANSFORM);
		//mpowner->type = SHIP;
		gameobject* obj = mpowner;


		if (ptr)
		{
			ptr->mposy = 50.0;
			{
				//obj->isactive_ = false;
				printf("Enemy attacked the ship \n");

			}
		}
	}
}