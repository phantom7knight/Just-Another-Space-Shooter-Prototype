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




#include "Matrix2D.h"

////////////////////
// From project 2 //
////////////////////

/*
This function sets the matrix Result to the identity matrix
*/
void Matrix2DIdentity(Matrix2D *pResult)
{
	pResult->m[0][0] = 1;
	pResult->m[0][1] = 0;
	pResult->m[0][2] = 0;
	pResult->m[0][3] = 0;
	pResult->m[1][0] = 0;
	pResult->m[1][1] = 1;
	pResult->m[1][2] = 0;
	pResult->m[1][3] = 0;
	pResult->m[2][0] = 0;
	pResult->m[2][1] = 0;
	pResult->m[2][2] = 1;
	pResult->m[2][3] = 0;
	pResult->m[3][0] = 0;
	pResult->m[3][1] = 0;
	pResult->m[3][2] = 0;
	pResult->m[3][3] = 1;

}

// ---------------------------------------------------------------------------

/*
This functions calculated the transpose matrix of Mtx and saves it in Result
*/
void Matrix2DTranspose(Matrix2D *pResult, Matrix2D *pMtx)
{
	pResult->m[0][0] = pMtx->m[0][0];
	pResult->m[0][1] = pMtx->m[1][0];
	pResult->m[0][2] = pMtx->m[0][2];
	pResult->m[0][3] = pMtx->m[3][0];
	pResult->m[1][0] = pMtx->m[0][1];
	pResult->m[1][1] = pMtx->m[1][1];
	pResult->m[1][2] = pMtx->m[2][1];
	pResult->m[1][3] = pMtx->m[3][1];
	pResult->m[2][0] = pMtx->m[0][2];
	pResult->m[2][1] = pMtx->m[1][2];
	pResult->m[2][2] = pMtx->m[2][2];
	pResult->m[2][3] = pMtx->m[3][2];
	pResult->m[3][0] = pMtx->m[0][3];
	pResult->m[3][1] = pMtx->m[1][3];
	pResult->m[3][2] = pMtx->m[2][3];
	pResult->m[3][3] = pMtx->m[3][3];
}

// ---------------------------------------------------------------------------

/*
This function multiplies Mtx0 with Mtx1 and saves the result in Result
Result = Mtx0*Mtx1
*/
void Matrix2DConcat(Matrix2D *pResult, Matrix2D *pMtx0, Matrix2D *pMtx1)
{

	float abc[3][3];



	abc[0][0] = pMtx0->m[0][0] * pMtx1->m[0][0] + pMtx0->m[0][1] * pMtx1->m[1][0] + pMtx0->m[0][2] * pMtx1->m[2][0] + pMtx0->m[0][3] * pMtx1->m[3][0];
	abc[0][1] = pMtx0->m[0][0] * pMtx1->m[0][1] + pMtx0->m[0][1] * pMtx1->m[1][1] + pMtx0->m[0][2] * pMtx1->m[2][1] + pMtx0->m[0][3] * pMtx1->m[3][1];
	abc[0][2] = pMtx0->m[0][0] * pMtx1->m[0][2] + pMtx0->m[0][1] * pMtx1->m[1][2] + pMtx0->m[0][2] * pMtx1->m[2][2] + pMtx0->m[0][3] * pMtx1->m[3][2];
	abc[0][3] = pMtx0->m[0][0] * pMtx1->m[0][3] + pMtx0->m[0][1] * pMtx1->m[1][3] + pMtx0->m[0][2] * pMtx1->m[2][3] + pMtx0->m[0][3] * pMtx1->m[3][3];
	
	abc[1][0] = pMtx0->m[1][0] * pMtx1->m[0][0] + pMtx0->m[1][1] * pMtx1->m[1][0] + pMtx0->m[1][2] * pMtx1->m[2][0] + pMtx0->m[1][3] * pMtx1->m[3][0];
	abc[1][1] = pMtx0->m[1][0] * pMtx1->m[0][1] + pMtx0->m[1][1] * pMtx1->m[1][1] + pMtx0->m[1][2] * pMtx1->m[2][1] + pMtx0->m[1][3] * pMtx1->m[3][1];
	abc[1][2] = pMtx0->m[1][0] * pMtx1->m[0][2] + pMtx0->m[1][1] * pMtx1->m[1][2] + pMtx0->m[1][2] * pMtx1->m[2][2] + pMtx0->m[1][3] * pMtx1->m[3][2];
	abc[1][3] = pMtx0->m[1][0] * pMtx1->m[0][3] + pMtx0->m[1][1] * pMtx1->m[1][3] + pMtx0->m[1][2] * pMtx1->m[2][3] + pMtx0->m[1][3] * pMtx1->m[3][3];

	abc[2][0] = pMtx0->m[2][0] * pMtx1->m[0][0] + pMtx0->m[2][1] * pMtx1->m[1][0] + pMtx0->m[2][2] * pMtx1->m[2][0] + pMtx0->m[2][3] * pMtx1->m[3][0];
	abc[2][1] = pMtx0->m[2][0] * pMtx1->m[0][1] + pMtx0->m[2][1] * pMtx1->m[1][1] + pMtx0->m[2][2] * pMtx1->m[2][1] + pMtx0->m[2][3] * pMtx1->m[3][1];
	abc[2][2] = pMtx0->m[2][0] * pMtx1->m[0][2] + pMtx0->m[2][1] * pMtx1->m[1][2] + pMtx0->m[2][2] * pMtx1->m[2][2] + pMtx0->m[2][3] * pMtx1->m[3][2];
	abc[2][3] = pMtx0->m[2][0] * pMtx1->m[0][3] + pMtx0->m[2][1] * pMtx1->m[1][3] + pMtx0->m[2][2] * pMtx1->m[2][3] + pMtx0->m[2][3] * pMtx1->m[3][3];

	abc[3][0] = pMtx0->m[3][0] * pMtx1->m[0][0] + pMtx0->m[3][1] * pMtx1->m[1][0] + pMtx0->m[3][2] * pMtx1->m[2][0] + pMtx0->m[3][3] * pMtx1->m[3][0];
	abc[3][1] = pMtx0->m[3][0] * pMtx1->m[0][1] + pMtx0->m[3][1] * pMtx1->m[1][1] + pMtx0->m[3][2] * pMtx1->m[2][1] + pMtx0->m[3][3] * pMtx1->m[3][1];
	abc[3][2] = pMtx0->m[3][0] * pMtx1->m[0][2] + pMtx0->m[3][1] * pMtx1->m[1][2] + pMtx0->m[3][2] * pMtx1->m[2][2] + pMtx0->m[3][3] * pMtx1->m[3][2];
	abc[3][3] = pMtx0->m[3][0] * pMtx1->m[0][3] + pMtx0->m[3][1] * pMtx1->m[1][3] + pMtx0->m[3][2] * pMtx1->m[2][3] + pMtx0->m[3][3] * pMtx1->m[3][3];


	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			pResult->m[i][j] = abc[i][j];
		}
	}

}

// ---------------------------------------------------------------------------

/*
This function creates a translation matrix from x & y and saves it in Result
*/
void Matrix2DTranslate(Matrix2D *pResult, float x, float y)
{
	for (int i = 0; i <4; i++) {
		for (int j = 0; j < 4; j++) {
			pResult->m[i][j] = 0;
		}
	}
	pResult->m[0][0] = pResult->m[0][0] + 1;
	pResult->m[0][3] = pResult->m[0][3] + x;
	pResult->m[1][1] = pResult->m[1][1] + 1;
	pResult->m[1][3] = pResult->m[1][3] + y;
	pResult->m[2][2] = pResult->m[2][2] + 1;
	pResult->m[3][3] = pResult->m[3][3] + 1;

}

// ---------------------------------------------------------------------------

/*
This function creates a scaling matrix from x & y and saves it in Result
*/
void Matrix2DScale(Matrix2D *pResult, float x, float y)
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			pResult->m[i][j] = 0;
		}
	}
	pResult->m[0][0] = pResult->m[0][0] + x;
	pResult->m[1][1] = pResult->m[1][1] + y;
	pResult->m[2][2] = pResult->m[2][2] + 1;
	pResult->m[3][3] = pResult->m[3][3] + 1;

}

// ---------------------------------------------------------------------------

/*
This matrix creates a rotation matrix from "Angle" whose value is in degree.
Save the resultant matrix in Result
*/
void Matrix2DRotDeg(Matrix2D *pResult, float Angle)
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			pResult->m[i][j] = 0;
		}
	}

	float Angle1 = (3.1415926535897932384626433832795 * Angle) / 180.0f;
	pResult->m[0][0] = pResult->m[0][0] + cosf(Angle1);
	pResult->m[0][1] = pResult->m[0][1] - sinf(Angle1);
	pResult->m[1][0] = pResult->m[1][0] + sinf(Angle1);
	pResult->m[1][1] = pResult->m[1][1] + cosf(Angle1);
	pResult->m[2][2] = pResult->m[2][2] + 1;
}

// ---------------------------------------------------------------------------

/*
This matrix creates a rotation matrix from "Angle" whose value is in radian.
Save the resultant matrix in Result
*/
void Matrix2DRotRad(Matrix2D *pResult, float Angle)
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			pResult->m[i][j] = 0;
		}
	}

	//float Angle1 = (3.1415926535897932384626433832795 * Angle) / 180;
	pResult->m[0][0] = pResult->m[0][0] + cosf(Angle);
	pResult->m[0][1] = pResult->m[0][1] - sinf(Angle);
	pResult->m[1][0] = pResult->m[1][0] + sinf(Angle);
	pResult->m[1][1] = pResult->m[1][1] + cosf(Angle);
	pResult->m[2][2] = pResult->m[2][2] + 1;
	pResult->m[3][3] = pResult->m[3][3] + 1;

}

// ---------------------------------------------------------------------------

/*
This function multiplies the matrix Mtx with the vector Vec and saves the result in Result
Result = Mtx * Vec
*/
void Matrix2DMultVec(Vector2D *pResult, Matrix2D *pMtx, Vector2D *pVec)
{
	/*
	float b[3][1];

	b[0][0] = pVec->x;
	b[1][0] = pVec->y;
	b[2][0] = 1;
	//b[100][100] = 0;
	//b[3][0] = 1;

	float abc[3][1];
	abc[0][0] = pMtx->m[0][0] * b[0][0] + pMtx->m[0][1] * b[1][0] + pMtx->m[0][2] * b[2][0] + pMtx->m[0][3] * b[3][0];
	abc[1][0] = pMtx->m[1][0] * b[0][0] + pMtx->m[1][1] * b[1][0] + pMtx->m[1][2] * b[2][0] + pMtx->m[1][3] * b[3][0];
	abc[2][0] = pMtx->m[2][0] * b[0][0] + pMtx->m[2][1] * b[1][0] + pMtx->m[2][2] * b[2][0] + +pMtx->m[2][3] * b[3][0];



	pResult->x = abc[0][0];
	pResult->y = abc[1][0];*/

	Vector2D temp;


	temp.x = (pMtx->m[0][0] * pVec->x) + (pMtx->m[0][1] * pVec->y) + pMtx->m[0][2] + pMtx->m[0][3];
	temp.y = (pMtx->m[1][0] * pVec->x) + (pMtx->m[1][1] * pVec->y) + pMtx->m[1][2] + pMtx->m[1][3];

	pResult->x = temp.x;
	pResult->y = temp.y;


}
// ---------------------------------------------------------------------------
