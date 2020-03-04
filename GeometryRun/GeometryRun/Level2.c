/**
 * Project:		GeometryRun
 * File Name:	Level2.c
 * Author:		黄嘉维（Load、Ini），王晶（Update），王彦钊（Draw），帅晓雨（Free、Unload）
 * Date:		2017-4-22
 * Purpose:		关卡2
 */
#include "Level2.h"

clock_t timeStart_level2;
const float bossOccurTime_level2 = 28.0f;

void Load2(void)
{
	printf("Level2: Load\n");
	theBaseList = NULL;
	// 设置常量
	SetConstants();
	// 初始化游戏对象基类的实例列表
	InitialGameObjBaseList(&theBaseList);

	PlayerLoad();
	BlockLoad();
	BulletLoad();
	BossBulletLoad();
	MonsterLoad();
	AIMonsterLoad();
	PlatformLoad();
	Boss2Load();
	BackGroundLoad();
	PauseLoad();
	UIStatusLoad();

	// 载入音乐
	SoundAdd("source/sound/level2_backgd.mp3", FMOD_LOOP_NORMAL, SOUND_2);
}

void Ini2(void)
{
	// 初始化时间系统
	TimerIni(&timeStart_level2);

	// 设置当前关卡的一些属性值
	float BlockVel = -350.0f;
	float MonsterVel = -350.0f;
	int bossMaxHP = 20;
	float BossBulletVelAbs = 400.0f;

	printf("Level2: Ini\n");
	// 获取当前关卡时间
	timeStart_level2 = clock();
	PlayerStart();
	BlockStart();
	PlatformStart();
	BackGroundStart();
	MonsterStart();
	AIMonsterStart();
	BulletStart();
	BossBulletStart();
	Boss2Start();
	PauseStart();
	UIStatusStart();

	BlockDefaultVelSet(BlockVel, 0);
	MonsterDefaultVelSet(MonsterVel, 0);
	AIMonsterDefaultVelSet(MonsterVel, 0);
	BossBulletDefaultBossBulletVelyABSSet(BossBulletVelAbs);
	Boss2MaxHPSet(bossMaxHP);

	// 播放音乐
	SoundPlay(SOUND_2);

	// 更新暂停变量
	isPaused = FALSE;
	endPause = FALSE;

	CreateObjInMap4(1.0f);
	CreateObjInMap3(2.0f);
	CreateObjInMap2(3.0f);
	CreateObjInMap5(6.0f);
	CreateObjInMap0(9.0f);
	CreateObjInMap8(17.0f);
	CreateObjInMap1(20.0f);
	CreateBossInMap_Level2(bossOccurTime_level2);
}

void Update2(void)
{
	GetWinMaxMinXY();
	
	// =========================
	// 游戏逻辑响应输入
	// =========================
	KeyUpdate();

	if (endPause)
	{
		// 重新计算因暂停延迟的时间
		timeStart_level2 += pauseEndTime - pauseStartTime;
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
		TimerUpdate(timeStart_level2);
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

void Draw2(void)
{
	// 为开始画对象做准备
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	AEGfxSetBlendMode(AE_GFX_RM_TEXTURE);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

	// 逐个绘制对象列表中的所有对象
	BaseListTraverse(Visit_DrawObj);

}

void Free2(void)
{
	
	printf("Level2: free\n");
	// 使用函数gameObjDestroy删除列表中的对象
	BaseListTraverse(Visit_DestroyObj);

	//音乐停止播放
	SoundStop(SOUND_2);

	TimerFree();
}

void Unload2(void)
{
	printf("Level2: Unload\n");
	DestroyGameObjBaseList(&theBaseList);
}
