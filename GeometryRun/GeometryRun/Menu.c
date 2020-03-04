#include "Menu.h"

void Load_Menu(void)
{
	printf("Level2: Load\n");
	theBaseList = NULL;
	// 设置常量
	SetConstants();
	// 初始化游戏对象基类的实例列表
	InitialGameObjBaseList(&theBaseList);

	BackGroundLoad();
}

void Ini_Menu(void)
{
	printf("Level2: Ini\n");

	BackGroundStart();

}

void Update_Menu(void)
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

void Draw_Menu(void)
{
	// 为开始画对象做准备
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	AEGfxSetBlendMode(AE_GFX_RM_TEXTURE);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

	// 逐个绘制对象列表中的所有对象
	BaseListTraverse(Visit_DrawObj);
}

void Free_Menu(void)
{

	printf("Level_Menu: free\n");
	// 使用函数gameObjDestroy删除列表中的对象
	BaseListTraverse(Visit_DestroyObj);
	TimerFree();
}

void Unload_Menu(void)
{
	printf("Level_Menu: Unload\n");
	DestroyGameObjBaseList(&theBaseList);
}
