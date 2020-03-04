/**
 * Project:		GeometryRun
 * File Name:	Math2D.c
 * Author:		帅晓雨
 * Date:		2017-4-22
 * Purpose:		Math2D.c
 */

#include "Math2D.h"
#include "stdio.h"

/*
检测点pP是否与圆（圆心pCenter，半径pRadius）发生碰撞
*/
int StaticPointToStaticCircle(Vector2D *pP, Vector2D *pCenter, float Radius)
{
	if (Vector2DDistance(pP, pCenter)< Radius)  return 1;          //碰撞发生
	else return 0;                      //碰撞未发生
}


/*
检测点pPos是否与矩形（中心pRect，宽度Width，高度Height）发生碰撞
*/
int StaticPointToStaticRect(Vector2D *pPos, Vector2D *pRect, float Width, float Height)
{
	if (pPos->x < pRect->x - Width / 2) return 0;
	if (pPos->x > pRect->x + Width / 2) return 0;
	if (pPos->y < pRect->y - Height / 2) return 0;
	if (pPos->y > pRect->y + Height / 2) return 0;  //未发生碰撞
	return 1;                                       //发生碰撞
}

/*
Circle0: 圆心pCenter0，半径pRadius0
Circle1: 圆心pCenter1，半径pRadius1
*/
int StaticCircleToStaticCircle(Vector2D *pCenter0, float Radius0, Vector2D *pCenter1, float Radius1)
{
	if (Vector2DDistance(pCenter0, pCenter1) < Radius0 + Radius1) return 1; //碰撞发生
	return 0;
}

/*
检测两个矩形是否发生碰撞
Rectangle0: 中心pRect0，宽度Width0，高度Height0
Rectangle1: 中心pRect1，宽度Width1，高度Height1
*/
int StaticRectToStaticRect(Vector2D *pRect0, float Width0, float Height0, Vector2D *pRect1, float Width1, float Height1)
{
	if (pRect0->x - Width0 / 2 > pRect1->x + Width1 / 2) return 0;
	if (pRect0->x + Width0 / 2 < pRect1->x - Width1 / 2) return 0;
	if (pRect0->y - Height0 / 2 > pRect1->y + Height1 / 2) return 0;
	if (pRect0->y + Height0 / 2 < pRect1->y - Height1 / 2) return 0;
    return 1;              //碰撞发生
}
