/**
 * Project:		GeometryRun
 * File Name:	Level4.c
 * Author:		王晶
 * Date:		2017-6-12
 * Purpose:		关卡4
 */
#include "Level4.h"

clock_t timeStart_level4;

int stage;				// 阶段
int stageWaves;			// 当前阶段障碍物波数
int currentWave;		// 当前障碍物波数
float toCreateTime;		// 下一波障碍物生成时间

void Load4(void)
{
	printf("Level4: Load\n");
	theBaseList = NULL;
	// 设置常量
	SetConstants();
	// 初始化游戏对象基类的实例列表
	InitialGameObjBaseList(&theBaseList);
	// 初始化随机生成对象函数指针数组
	IniCreateRandomArrays();

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
	SoundAdd("source/sound/level4_backgd.mp3", FMOD_LOOP_NORMAL, SOUND_4);
}

void Ini4(void)
{
	// 初始化时间系统
	TimerIni(&timeStart_level4);

	// 设置当前关卡的一些属性值
	float BlockVel = -400.0f;
	float MonsterVel = -400.0f;
	int bossMaxHP = 5;
	float BossBulletVelAbs = 400.0f;

	stage = 0;
	stageWaves = 5 + rand() % 2;	// 第一关波数随机5~6
	currentWave = 0;
	toCreateTime = 0.0f;

	printf("Level4: Ini\n");
	// 获取当前关卡时间
	timeStart_level4 = clock();

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
	SoundPlay(SOUND_4);
}

void Update4(void)
{
	GetWinMaxMinXY();

	// =========================
	// 游戏逻辑响应输入
	// =========================
	KeyUpdate();

	if (endPause)
	{
		// 重新计算因暂停延迟的时间
		timeStart_level4 += pauseEndTime - pauseStartTime;
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
		TimerUpdate(timeStart_level4);

		if (!Boss2Alive && passTime >= toCreateTime)
		{
			if (currentWave <= stageWaves)
			{
				if (currentWave == 0)
				{
					// 更新阶段变量
					stage++;
					// 增加难度
					BlockDefaultVxChange(-20.0f);
					MonsterDefaultVxChange(-20.0f);
					AIMonsterDefaultVxChange(-20.0f);
					AIMonsterDefaultVelyABSChange(10.0f);
					BossBulletDefaultVelyABSChange(20.0f);
					Boss2MaxHPChange(4);
					stageWaves = 5 + rand() % 3;	// 波数随机为5~7
					
					if (!PlayerClearCountGet())
						PlayerClearReload();

					// 每个阶段间隔3.0s
					toCreateTime = passTime + 3.0f;
					currentWave++;
				}
				else
				{
					// 当前时刻随机用一种方式生成一波障碍物，并这波结束后延迟2.5s生成下一波
					int createMethod = rand() % CreateMethods;
					toCreateTime =	passTime + (CreateObjInMapRamdom[createMethod])(passTime) + 2.5f;
					currentWave++;
				}
			}
			else
			{
				Boss2Alive = TRUE;
				pBoss2 = Boss2Create();
				//printf("\nBossHP : %d\n", Boss2HP);
				//printf("Boss vx : %f, vy: %f\n", Boss2EnterVel.x, Boss2EnterVel.y);

				// 准备进入下个阶段
				currentWave = 0;

			}
		}

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

void Draw4(void)
{
	// 为开始画对象做准备
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	AEGfxSetBlendMode(AE_GFX_RM_TEXTURE);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

	// 逐个绘制对象列表中的所有对象
	BaseListTraverse(Visit_DrawObj);

}

void Free4(void)
{

	printf("Level4: free\n");
	// 使用函数gameObjDestroy删除列表中的对象
	BaseListTraverse(Visit_DestroyObj);

	//音乐停止播放
	SoundStop(SOUND_4);

	TimerFree();
}

void Unload4(void)
{
	printf("Level4: Unload\n");
	DestroyGameObjBaseList(&theBaseList);
}
