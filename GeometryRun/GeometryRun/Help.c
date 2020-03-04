/* Project:GeometryRun
File Name:	Help.c
Author:		帅晓雨
Date:
Purpose:		帮助  */

#include "Help.h"

#define MAX_TIME 2.0f

void Load_Help(void)
{
	printf("Level_Help: Load\n");
	theBaseList = NULL;

	// 设置常量
	SetConstants();
	// 初始化游戏对象基类的实例列表
	InitialGameObjBaseList(&theBaseList);

	BackGroundLoad();

}

void Ini_Help(void)
{
	printf("Level_Help: Ini\n");
	Vector2D iniPosition_Images = { 0.0f, 0.0f };
	Vector2D iniVelocity_Images = { 0.0f, 0.0f };

	xcurrentFrame = 0;
	elpasedTime = 0;

	// 对象实例化：
	pImage = BackGroundCreateWithPosAndVel(iniPosition_Images, iniVelocity_Images);

}

void Update_Help(void)
{

	GetWinMaxMinXY();

	// =========================
	// 游戏逻辑响应输入
	// =========================
	KeyUpdate();

	elpasedTime += frameTime;

	if (elpasedTime > MAX_TIME)
	{
		++xcurrentFrame;
		elpasedTime = 0;
	}
	// =====================================
	// 计算所有对象的2D变换矩阵
	// =====================================
	BaseListTraverse(Visit_Matrix2DCount);

}

void Draw_Help(void)
{

	// 为开始画对象做准备
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	AEGfxSetBlendMode(AE_GFX_RM_TEXTURE);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

	// 设置纹理
	AEGfxTextureSet(pImage->pObject->pTex, xcurrentFrame / 6.0f, 0);
	// 设置对象的2D变换矩阵，使用函数：AEGfxSetTransform
	AEGfxSetTransform(pImage->transform.m);
	// 绘制当前对象，使用函数：AEGfxMeshDraw
	AEGfxMeshDraw(pImage->pObject->pMesh, AE_GFX_MDM_TRIANGLES);

}

void Free_Help(void)
{
	printf("Level_Help: free\n");
	// 使用函数gameObjDestroy删除列表中的对象
	BaseListTraverse(Visit_DestroyObj);
}

void Unload_Help(void)
{
	printf("Level_Help: Unload\n");
	DestroyGameObjBaseList(&theBaseList);
}
