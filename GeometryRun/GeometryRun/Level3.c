/**
 * Project:		GeometryRun
 * File Name:	Level3.c
 * Author:		黄嘉维
 * Date:		2017-4-22
 * Purpose:		关卡3
 */
#include "Level3.h"

clock_t timeStart_level3;
const float bossOccurTime_level3 = 23.0f;

void Load3(void)
{
	printf("Level3: Load\n");
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
	SoundAdd("source/sound/level3_backgd.mp3", FMOD_LOOP_NORMAL, SOUND_3);
}

void Ini3(void)
{
	// 初始化时间系统
	TimerIni(&timeStart_level3);

	// 设置当前关卡的一些属性值
	float BlockVel = -400.0f;
	float MonsterVel = -400.0f;
	int bossMaxHP = 25;
	float BossBulletVelAbs = 400.0f;

	printf("Level3: Ini\n");
	// 获取当前关卡时间
	timeStart_level3 = clock();

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
	SoundPlay(SOUND_3);

	CreateObjInMap8(1.0f);
	CreateObjInMap4(3.0f);
	CreateObjInMap2(4.0f);
	CreateObjInMap7(7.5f);
	CreateObjInMap5(9.4f);
	CreateObjInMap9(12.0f);
	CreateObjInMap0(15.0f);
	CreateBossInMap_Level2(bossOccurTime_level3);
}

void Update3(void)
{
	GetWinMaxMinXY();

	// =========================
	// 游戏逻辑响应输入
	// =========================
	KeyUpdate();

	if (endPause)
	{
		// 重新计算因暂停延迟的时间
		timeStart_level3 += pauseEndTime - pauseStartTime;
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
		TimerUpdate(timeStart_level3);
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

void Draw3(void)
{
	// 为开始画对象做准备
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	AEGfxSetBlendMode(AE_GFX_RM_TEXTURE);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

	// 逐个绘制对象列表中的所有对象
	BaseListTraverse(Visit_DrawObj);

}

void Free3(void)
{

	printf("Level3: free\n");
	// 使用函数gameObjDestroy删除列表中的对象
	BaseListTraverse(Visit_DestroyObj);

	//音乐停止播放
	SoundStop(SOUND_3);

	TimerFree();
}

void Unload3(void)
{
	printf("Level3: Unload\n");
	DestroyGameObjBaseList(&theBaseList);
}
