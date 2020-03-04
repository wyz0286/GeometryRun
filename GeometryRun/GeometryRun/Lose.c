#include "Lose.h"

clock_t timeStart_level_Lose;


void Load_Lose(void)
{
	// ��ʼ��ʱ��ϵͳ
	//TimerIni(&timeStart_level_Lose);

	printf("Level_Lose: Load\n");
	theBaseList = NULL;
	// ���ó���
	SetConstants();
	// ��ʼ����Ϸ��������ʵ���б�
	InitialGameObjBaseList(&theBaseList);

	BackGroundLoad();

	// ��������
	SoundAdd("source/sound/Lose.mp3", FMOD_LOOP_OFF, SOUND_Lose);
}

void Ini_Lose(void)
{
	printf("Level_Lose: Ini\n");
	BackGroundStart();

	// ��������
	SoundPlay(SOUND_Lose);
}

void Update_Lose(void)
{
	GetWinMaxMinXY();

	// =========================
	// ��Ϸ�߼���Ӧ����
	// =========================
	KeyUpdate();

	// ���¶���
	ObjUpdate();

	// =====================================
	// �������ж����2D�任����
	// =====================================
	BaseListTraverse(Visit_Matrix2DCount);
}

void Draw_Lose(void)
{
	// Ϊ��ʼ��������׼��
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	AEGfxSetBlendMode(AE_GFX_RM_TEXTURE);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	// ������ƶ����б��е����ж���
	BaseListTraverse(Visit_DrawObj);

}

void Free_Lose(void)
{

	printf("Level_Lose: free\n");
	// ʹ�ú���gameObjDestroyɾ���б��еĶ���
	BaseListTraverse(Visit_DestroyObj);
	TimerFree();
}

void Unload_Lose(void)
{
	printf("Level_Lose: Unload\n");
	DestroyGameObjBaseList(&theBaseList);
}
