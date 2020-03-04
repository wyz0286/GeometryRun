/**
 * Project:		GeometryRun
 * File Name:	Matrix2D.c
 * Author:		帅晓雨
 * Date:		2017-4-22
 * Purpose:		Matrix2D.c
 */

#include "Matrix2D.h"


/*
将pResult设置为单位矩阵
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
计算pMtx的转置，并将结果放到pResult
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
将pResult设置为平移矩阵，平移位移为x和y
*/
void Matrix2DTranslate(Matrix2D *pResult, float x, float y)
{
	Matrix2DIdentity(pResult);
	pResult->m[0][2] = x;
	pResult->m[1][2] = y;
}

// ---------------------------------------------------------------------------

/*
将pResult设置为缩放矩阵，x和y分别为水平和垂直方向的缩放比例
*/
void Matrix2DScale(Matrix2D *pResult, float x, float y)
{
	Matrix2DIdentity(pResult);
	pResult->m[0][0] = x;
	pResult->m[1][1] = y;
}

// ---------------------------------------------------------------------------

/*
将pResult设置为旋转矩阵，旋转量为Angle，为度数
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
将pResult设置为旋转矩阵，旋转量为Angle，为弧度
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
