/**
 * Project:		GeometryRun
 * File Name:	Level1.c
 * Author:		王彦钊（Ini、Draw），黄嘉维（Load），王晶（Update），帅晓雨（Free、Unload）
 * Date:		2017-6-7
 * Purpose:		关卡1
 */
#include "Level1.h"

clock_t timeStart_level1;


void Load1(void)
{
	printf("Level1: Load\n");
	theBaseList = NULL;
	// 设置常量
	SetConstants();
	// 初始化游戏对象基类的实例列表
	InitialGameObjBaseList(&theBaseList);

	PlayerLoad();
	BlockLoad();
	BulletLoad();
	MonsterLoad();
	PlatformLoad();
	BackGroundLoad();
	PauseLoad();
	UIStatusLoad();
	
	// 载入音乐
	SoundAdd("source/sound/level1_backgd.mp3", FMOD_LOOP_NORMAL, SOUND_1);
}

void Ini1(void)
{
	// 初始化时间系统
	TimerIni(&timeStart_level1);

	// 设置当前关卡的一些属性值
	float BlockVel = -320.0f;
	float MonsterVel = -320.0f;

	printf("Level1: Ini\n");
	// 获取当前关卡时间
	timeStart_level1 = clock();

	PlayerStart();
	BlockStart();
    PlatformStart();
	BackGroundStart();
	MonsterStart();
	BulletStart();
	PauseStart();
	UIStatusStart();
	
	BlockDefaultVelSet(BlockVel, 0);
	MonsterDefaultVelSet(MonsterVel, 0);

	// 播放音乐
	SoundPlay(SOUND_1);

	CreateObjInMap4(1.0f);
	CreateObjInMap3(2.5f);
	CreateObjInMap5(4.0f);
	CreateObjInMap0(6.0f);
	CreateObjInMap6(16.0f);
	SwithSceneAtTime(20.5f, GS_Pass);

}

void Update1(void)
{
	GetWinMaxMinXY();

	// =========================
	// 游戏逻辑响应输入
	// =========================
	KeyUpdate();

	if (endPause)
	{
		// 重新计算因暂停延迟的时间
		timeStart_level1 += pauseEndTime - pauseStartTime;
		endPause = FALSE;
		GameObjDelete(pPause);
		pauseCreated = FALSE;
		SoundPausePlay(Current - GS_L0);
	}

	if (isPaused)
	{
		if (!pauseCreated)
		{
			pPause = PauseCreate();
			pauseCreated = TRUE;
			SoundPausePlay(Current - GS_L0);
		}
	}
	else
	{
		TimerUpdate(timeStart_level1);
		// 更新对象
		ObjUpdate();

		// ====================
		// 碰撞检测
		// ====================
		BaseListTraverse(Visit_CollisionDetect);

	}
	// =====================================
	// 计算所有对象的2D变换矩阵
	// =====================================
	BaseListTraverse(Visit_Matrix2DCount);
}

void Draw1(void)
{
	// 为开始画对象做准备
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	AEGfxSetBlendMode(AE_GFX_RM_TEXTURE);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

	// 逐个绘制对象列表中的所有对象
	BaseListTraverse(Visit_DrawObj);

}

void Free1(void)
{

	printf("Level1: free\n");
	// 使用函数gameObjDestroy删除列表中的对象
	BaseListTraverse(Visit_DestroyObj);

	//音乐停止播放
	SoundStop(SOUND_1);

	TimerFree();
}

void Unload1(void)
{
	printf("Level1: Unload\n");
	DestroyGameObjBaseList(&theBaseList);
	
	printf ("atry");
}
