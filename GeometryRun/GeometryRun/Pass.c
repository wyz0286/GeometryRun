#include "Lose.h"

clock_t timeStart_level_Pass;


void Load_Pass(void)
{
	// 初始化时间系统
	//TimerIni(&timeStart_level_Pass);

	printf("Level_Pass: Load\n");
	theBaseList = NULL;
	// 设置常量
	SetConstants();
	// 初始化游戏对象基类的实例列表
	InitialGameObjBaseList(&theBaseList);

	BackGroundLoad();

	// 载入音乐
	SoundAdd("source/sound/Pass.mp3", FMOD_LOOP_OFF, SOUND_Pass);
}

void Ini_Pass(void)
{
	printf("Level_Pass: Ini\n");
	// 获取当前关卡时间
	//timeStart_level_Pass = clock();
	BackGroundStart();

	// 播放音乐
	SoundPlay(SOUND_Pass);
}

void Update_Pass(void)
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

void Draw_Pass(void)
{
	// 为开始画对象做准备
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	AEGfxSetBlendMode(AE_GFX_RM_TEXTURE);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	// 逐个绘制对象列表中的所有对象
	BaseListTraverse(Visit_DrawObj);

}

void Free_Pass(void)
{

	printf("Level_Pass: free\n");
	// 使用函数gameObjDestroy删除列表中的对象
	BaseListTraverse(Visit_DestroyObj);
	TimerFree();
}

void Unload_Pass(void)
{
	printf("Level_Pass: Unload\n");
	DestroyGameObjBaseList(&theBaseList);
}
