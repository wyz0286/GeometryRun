/**
 * Project:		GeometryRun
 * File Name:	Level1.c
 * Author:		�����ȣ�Ini��Draw�����Ƽ�ά��Load����������Update����˧���꣨Free��Unload��
 * Date:		2017-6-7
 * Purpose:		�ؿ�1
 */
#include "Level1.h"

clock_t timeStart_level1;


void Load1(void)
{
	printf("Level1: Load\n");
	theBaseList = NULL;
	// ���ó���
	SetConstants();
	// ��ʼ����Ϸ��������ʵ���б�
	InitialGameObjBaseList(&theBaseList);

	PlayerLoad();
	BlockLoad();
	BulletLoad();
	MonsterLoad();
	PlatformLoad();
	BackGroundLoad();
	PauseLoad();
	UIStatusLoad();
	
	// ��������
	SoundAdd("source/sound/level1_backgd.mp3", FMOD_LOOP_NORMAL, SOUND_1);
}

void Ini1(void)
{
	// ��ʼ��ʱ��ϵͳ
	TimerIni(&timeStart_level1);

	// ���õ�ǰ�ؿ���һЩ����ֵ
	float BlockVel = -320.0f;
	float MonsterVel = -320.0f;

	printf("Level1: Ini\n");
	// ��ȡ��ǰ�ؿ�ʱ��
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

	// ��������
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
	// ��Ϸ�߼���Ӧ����
	// =========================
	KeyUpdate();

	if (endPause)
	{
		// ���¼�������ͣ�ӳٵ�ʱ��
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

void Draw1(void)
{
	// Ϊ��ʼ��������׼��
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	AEGfxSetBlendMode(AE_GFX_RM_TEXTURE);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

	// ������ƶ����б��е����ж���
	BaseListTraverse(Visit_DrawObj);

}

void Free1(void)
{

	printf("Level1: free\n");
	// ʹ�ú���gameObjDestroyɾ���б��еĶ���
	BaseListTraverse(Visit_DestroyObj);

	//����ֹͣ����
	SoundStop(SOUND_1);

	TimerFree();
}

void Unload1(void)
{
	printf("Level1: Unload\n");
	DestroyGameObjBaseList(&theBaseList);
	
	printf ("atry");
}
