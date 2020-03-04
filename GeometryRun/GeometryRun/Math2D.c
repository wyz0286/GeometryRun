/**
 * Project:		GeometryRun
 * File Name:	Math2D.c
 * Author:		˧����
 * Date:		2017-4-22
 * Purpose:		Math2D.c
 */

#include "Math2D.h"
#include "stdio.h"

/*
����pP�Ƿ���Բ��Բ��pCenter���뾶pRadius��������ײ
*/
int StaticPointToStaticCircle(Vector2D *pP, Vector2D *pCenter, float Radius)
{
	if (Vector2DDistance(pP, pCenter)< Radius)  return 1;          //��ײ����
	else return 0;                      //��ײδ����
}


/*
����pPos�Ƿ�����Σ�����pRect�����Width���߶�Height��������ײ
*/
int StaticPointToStaticRect(Vector2D *pPos, Vector2D *pRect, float Width, float Height)
{
	if (pPos->x < pRect->x - Width / 2) return 0;
	if (pPos->x > pRect->x + Width / 2) return 0;
	if (pPos->y < pRect->y - Height / 2) return 0;
	if (pPos->y > pRect->y + Height / 2) return 0;  //δ������ײ
	return 1;                                       //������ײ
}

/*
Circle0: Բ��pCenter0���뾶pRadius0
Circle1: Բ��pCenter1���뾶pRadius1
*/
int StaticCircleToStaticCircle(Vector2D *pCenter0, float Radius0, Vector2D *pCenter1, float Radius1)
{
	if (Vector2DDistance(pCenter0, pCenter1) < Radius0 + Radius1) return 1; //��ײ����
	return 0;
}

/*
������������Ƿ�����ײ
Rectangle0: ����pRect0�����Width0���߶�Height0
Rectangle1: ����pRect1�����Width1���߶�Height1
*/
int StaticRectToStaticRect(Vector2D *pRect0, float Width0, float Height0, Vector2D *pRect1, float Width1, float Height1)
{
	if (pRect0->x - Width0 / 2 > pRect1->x + Width1 / 2) return 0;
	if (pRect0->x + Width0 / 2 < pRect1->x - Width1 / 2) return 0;
	if (pRect0->y - Height0 / 2 > pRect1->y + Height1 / 2) return 0;
	if (pRect0->y + Height0 / 2 < pRect1->y - Height1 / 2) return 0;
    return 1;              //��ײ����
}
