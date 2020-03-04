/**
 * Project:		GeometryRun
 * File Name:	Calculate.c
 * Author:		帅晓雨
 * Date:		2017-6-21
 * Purpose:		无尽模式关卡结算
 */

#include "Calculate.h"

void Load_Calculate(void)
{
	printf("Level_Calculate: Load\n");
	theBaseList = NULL;
	// 设置常量
	SetConstants();
	// 初始化游戏对象基类的实例列表
	InitialGameObjBaseList(&theBaseList);

	BackGroundLoad();
	UICalculateLoad();
}

void Ini_Calculate(void)
{
	printf("Level_Calculate: Ini\n");
	// 获取当前关卡时间
	//timeStart_level_Win = clock();
	BackGroundStart();
	UICalculateStart();


}

void Update_Calculate(void)
{
	GetWinMaxMinXY();

	// =========================
	// 游戏逻辑响应输入
	// =========================
	KeyUpdate();

	// 更新对象
	ObjUpdate();

	// =====================================
	// 计算所有对象的2D变换矩阵
	// =====================================
	BaseListTraverse(Visit_Matrix2DCount);
}

void Draw_Calculate(void)
{
	// 为开始画对象做准备
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	AEGfxSetBlendMode(AE_GFX_RM_TEXTURE);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	// 逐个绘制对象列表中的所有对象
	BaseListTraverse(Visit_DrawObj);

}

void Free_Calculate(void)
{

	printf("Level_Calculate: free\n");
	// 使用函数gameObjDestroy删除列表中的对象
	BaseListTraverse(Visit_DestroyObj);
	TimerFree();
}

void Unload_Calculate(void)
{
	printf("Level_Calculate: Unload\n");
	DestroyGameObjBaseList(&theBaseList);
}
