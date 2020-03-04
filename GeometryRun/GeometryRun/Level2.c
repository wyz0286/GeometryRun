/**
 * Project:		GeometryRun
 * File Name:	Level2.c
 * Author:		�Ƽ�ά��Load��Ini����������Update���������ȣ�Draw����˧���꣨Free��Unload��
 * Date:		2017-4-22
 * Purpose:		�ؿ�2
 */
#include "Level2.h"

clock_t timeStart_level2;
const float bossOccurTime_level2 = 28.0f;

void Load2(void)
{
	printf("Level2: Load\n");
	theBaseList = NULL;
	// ���ó���
	SetConstants();
	// ��ʼ����Ϸ��������ʵ���б�
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

	// ��������
	SoundAdd("source/sound/level2_backgd.mp3", FMOD_LOOP_NORMAL, SOUND_2);
}

void Ini2(void)
{
	// ��ʼ��ʱ��ϵͳ
	TimerIni(&timeStart_level2);

	// ���õ�ǰ�ؿ���һЩ����ֵ
	float BlockVel = -350.0f;
	float MonsterVel = -350.0f;
	int bossMaxHP = 20;
	float BossBulletVelAbs = 400.0f;

	printf("Level2: Ini\n");
	// ��ȡ��ǰ�ؿ�ʱ��
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

	// ��������
	SoundPlay(SOUND_2);

	// ������ͣ����
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
	// ��Ϸ�߼���Ӧ����
	// =========================
	KeyUpdate();

	if (endPause)
	{
		// ���¼�������ͣ�ӳٵ�ʱ��
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

void Draw2(void)
{
	// Ϊ��ʼ��������׼��
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	AEGfxSetBlendMode(AE_GFX_RM_TEXTURE);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

	// ������ƶ����б��е����ж���
	BaseListTraverse(Visit_DrawObj);

}

void Free2(void)
{
	
	printf("Level2: free\n");
	// ʹ�ú���gameObjDestroyɾ���б��еĶ���
	BaseListTraverse(Visit_DestroyObj);

	//����ֹͣ����
	SoundStop(SOUND_2);

	TimerFree();
}

void Unload2(void)
{
	printf("Level2: Unload\n");
	DestroyGameObjBaseList(&theBaseList);
}
