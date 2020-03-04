/**
 * Project:		GeometryRun
 * File Name:	Matrix2D.h
 * Author:		帅晓雨
 * Date:		2017-4-22
 * Purpose:		Matrix2D.h
 */

#pragma once

#define PI 3.1415926535897932384626433832795

#include "Vector2D.h"

// 3by3的矩阵
typedef struct Matrix2D
{
	float m[3][3];
}Matrix2D;


/*
将pResult设置为单位矩阵
*/
void Matrix2DIdentity(Matrix2D *pResult);

/*
计算pMtx的转置，并将结果放到pResult
*/
void Matrix2DTranspose(Matrix2D *pResult, Matrix2D *pMtx);

/*
pResult = pMtx0 * pMtx1
*/
void Matrix2DConcat(Matrix2D *pResult, Matrix2D *pMtx0, Matrix2D *pMtx1);

/*
将pResult设置为平移矩阵，平移位移为x和y 
*/
void Matrix2DTranslate(Matrix2D *pResult, float x, float y);

/*
将pResult设置为缩放矩阵，x和y分别为水平和垂直方向的缩放比例
*/
void Matrix2DScale(Matrix2D *pResult, float x, float y);

/*
将pResult设置为旋转矩阵，旋转量为Angle，为度数
*/
void Matrix2DRotDeg(Matrix2D *pResult, float Angle);

/*
将pResult设置为旋转矩阵，旋转量为Angle，为弧度
*/
void Matrix2DRotRad(Matrix2D *pResult, float Angle);

/*
pResult = pMtx * pVec
*/
void Matrix2DMultVec(Vector2D *pResult, Matrix2D *pMtx, Vector2D *pVec);
