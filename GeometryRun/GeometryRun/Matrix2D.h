/**
 * Project:		GeometryRun
 * File Name:	Matrix2D.h
 * Author:		˧����
 * Date:		2017-4-22
 * Purpose:		Matrix2D.h
 */

#pragma once

#define PI 3.1415926535897932384626433832795

#include "Vector2D.h"

// 3by3�ľ���
typedef struct Matrix2D
{
	float m[3][3];
}Matrix2D;


/*
��pResult����Ϊ��λ����
*/
void Matrix2DIdentity(Matrix2D *pResult);

/*
����pMtx��ת�ã���������ŵ�pResult
*/
void Matrix2DTranspose(Matrix2D *pResult, Matrix2D *pMtx);

/*
pResult = pMtx0 * pMtx1
*/
void Matrix2DConcat(Matrix2D *pResult, Matrix2D *pMtx0, Matrix2D *pMtx1);

/*
��pResult����Ϊƽ�ƾ���ƽ��λ��Ϊx��y 
*/
void Matrix2DTranslate(Matrix2D *pResult, float x, float y);

/*
��pResult����Ϊ���ž���x��y�ֱ�Ϊˮƽ�ʹ�ֱ��������ű���
*/
void Matrix2DScale(Matrix2D *pResult, float x, float y);

/*
��pResult����Ϊ��ת������ת��ΪAngle��Ϊ����
*/
void Matrix2DRotDeg(Matrix2D *pResult, float Angle);

/*
��pResult����Ϊ��ת������ת��ΪAngle��Ϊ����
*/
void Matrix2DRotRad(Matrix2D *pResult, float Angle);

/*
pResult = pMtx * pVec
*/
void Matrix2DMultVec(Vector2D *pResult, Matrix2D *pMtx, Vector2D *pVec);
