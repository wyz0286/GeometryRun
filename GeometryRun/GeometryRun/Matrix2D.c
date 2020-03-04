/**
 * Project:		GeometryRun
 * File Name:	Matrix2D.c
 * Author:		˧����
 * Date:		2017-4-22
 * Purpose:		Matrix2D.c
 */

#include "Matrix2D.h"


/*
��pResult����Ϊ��λ����
*/
void Matrix2DIdentity(Matrix2D *pResult)
{
	int i, j;
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			pResult->m[i][j] = (i==j)?1.f:0.f;
}

// ---------------------------------------------------------------------------

/*
����pMtx��ת�ã���������ŵ�pResult
*/
void Matrix2DTranspose(Matrix2D *pResult, Matrix2D *pMtx)
{
	int i, j;
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			pResult->m[j][i] = pMtx->m[i][j];
}

// ---------------------------------------------------------------------------

/*
Result = Mtx0*Mtx1
*/
void Matrix2DConcat(Matrix2D *pResult, Matrix2D *pMtx0, Matrix2D *pMtx1)
{
	int i, j, p;
	float m[3][3] = { 0 };
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++) 
			for (p = 0; p < 3; p++)
				m[i][j] = m[i][j] + pMtx0->m[i][p] * pMtx1->m[p][j];
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			pResult->m[i][j]=m[i][j];
}

// ---------------------------------------------------------------------------

/*
��pResult����Ϊƽ�ƾ���ƽ��λ��Ϊx��y
*/
void Matrix2DTranslate(Matrix2D *pResult, float x, float y)
{
	Matrix2DIdentity(pResult);
	pResult->m[0][2] = x;
	pResult->m[1][2] = y;
}

// ---------------------------------------------------------------------------

/*
��pResult����Ϊ���ž���x��y�ֱ�Ϊˮƽ�ʹ�ֱ��������ű���
*/
void Matrix2DScale(Matrix2D *pResult, float x, float y)
{
	Matrix2DIdentity(pResult);
	pResult->m[0][0] = x;
	pResult->m[1][1] = y;
}

// ---------------------------------------------------------------------------

/*
��pResult����Ϊ��ת������ת��ΪAngle��Ϊ����
*/
void Matrix2DRotDeg(Matrix2D *pResult, float Angle)
{
	Matrix2DIdentity(pResult);
	float a;
	a = (float)(Angle * PI / 180);
	pResult->m[0][0] = cosf(a);
	pResult->m[1][1] = cosf(a);
	pResult->m[0][1] = -sinf(a);
	pResult->m[1][0] = sinf(a);
}

// ---------------------------------------------------------------------------

/*
��pResult����Ϊ��ת������ת��ΪAngle��Ϊ����
*/
void Matrix2DRotRad(Matrix2D *pResult, float Angle)
{
	Matrix2DIdentity(pResult);
	pResult->m[0][0] = cosf(Angle);
	pResult->m[1][1] = cosf(Angle);
	pResult->m[0][1] = -sinf(Angle);
	pResult->m[1][0] = sinf(Angle);
}

// ---------------------------------------------------------------------------

/*
Result = Mtx * Vec
*/
void Matrix2DMultVec(Vector2D *pResult, Matrix2D *pMtx, Vector2D *pVec)
{
	int i, j;
	float m[3][1] = { 0 };
	float v[3][1] = { pVec->x,pVec->y,1 };
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			m[i][0] = m[i][0] + pMtx->m[i][j] * v[j][0];

    pResult->x = m[0][0];
	pResult->y = m[1][0];
}

// ---------------------------------------------------------------------------
