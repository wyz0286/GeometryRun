/**
 * Project:		GeometryRun
 * File Name:	Level4.c
 * Author:		����
 * Date:		2017-6-12
 * Purpose:		�ؿ�4
 */
#include "Level4.h"

clock_t timeStart_level4;

int stage;				// �׶�
int stageWaves;			// ��ǰ�׶��ϰ��ﲨ��
int currentWave;		// ��ǰ�ϰ��ﲨ��
float toCreateTime;		// ��һ���ϰ�������ʱ��

void Load4(void)
{
	printf("Level4: Load\n");
	theBaseList = NULL;
	// ���ó���
	SetConstants();
	// ��ʼ����Ϸ��������ʵ���б�
	InitialGameObjBaseList(&theBaseList);
	// ��ʼ��������ɶ�����ָ������
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

	// ��������
	SoundAdd("source/sound/level4_backgd.mp3", FMOD_LOOP_NORMAL, SOUND_4);
}

void Ini4(void)
{
	// ��ʼ��ʱ��ϵͳ
	TimerIni(&timeStart_level4);

	// ���õ�ǰ�ؿ���һЩ����ֵ
	float BlockVel = -400.0f;
	float MonsterVel = -400.0f;
	int bossMaxHP = 5;
	float BossBulletVelAbs = 400.0f;

	stage = 0;
	stageWaves = 5 + rand() % 2;	// ��һ�ز������5~6
	currentWave = 0;
	toCreateTime = 0.0f;

	printf("Level4: Ini\n");
	// ��ȡ��ǰ�ؿ�ʱ��
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


	// ��������
	SoundPlay(SOUND_4);
}

void Update4(void)
{
	GetWinMaxMinXY();

	// =========================
	// ��Ϸ�߼���Ӧ����
	// =========================
	KeyUpdate();

	if (endPause)
	{
		// ���¼�������ͣ�ӳٵ�ʱ��
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
					// ���½׶α���
					stage++;
					// �����Ѷ�
					BlockDefaultVxChange(-20.0f);
					MonsterDefaultVxChange(-20.0f);
					AIMonsterDefaultVxChange(-20.0f);
					AIMonsterDefaultVelyABSChange(10.0f);
					BossBulletDefaultVelyABSChange(20.0f);
					Boss2MaxHPChange(4);
					stageWaves = 5 + rand() % 3;	// �������Ϊ5~7
					
					if (!PlayerClearCountGet())
						PlayerClearReload();

					// ÿ���׶μ��3.0s
					toCreateTime = passTime + 3.0f;
					currentWave++;
				}
				else
				{
					// ��ǰʱ�������һ�ַ�ʽ����һ���ϰ�����Ⲩ�������ӳ�2.5s������һ��
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

				// ׼�������¸��׶�
				currentWave = 0;

			}
		}

		// ���¶���
		ObjUpdate();

		// ====================
		// ��ײ���
		// ====================
		BaseListTraverse(Visit_CollisionDetect);

	}
	// =====================================
	// �������ж����2D�任����
	// =====================================
	BaseListTraverse(Visit_Matrix2DCount);
}

void Draw4(void)
{
	// Ϊ��ʼ��������׼��
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	AEGfxSetBlendMode(AE_GFX_RM_TEXTURE);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

	// ������ƶ����б��е����ж���
	BaseListTraverse(Visit_DrawObj);

}

void Free4(void)
{

	printf("Level4: free\n");
	// ʹ�ú���gameObjDestroyɾ���б��еĶ���
	BaseListTraverse(Visit_DestroyObj);

	//����ֹͣ����
	SoundStop(SOUND_4);

	TimerFree();
}

void Unload4(void)
{
	printf("Level4: Unload\n");
	DestroyGameObjBaseList(&theBaseList);
}
