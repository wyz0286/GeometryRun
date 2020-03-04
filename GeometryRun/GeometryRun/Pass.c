#include "Lose.h"

clock_t timeStart_level_Pass;


void Load_Pass(void)
{
	// ��ʼ��ʱ��ϵͳ
	//TimerIni(&timeStart_level_Pass);

	printf("Level_Pass: Load\n");
	theBaseList = NULL;
	// ���ó���
	SetConstants();
	// ��ʼ����Ϸ��������ʵ���б�
	InitialGameObjBaseList(&theBaseList);

	BackGroundLoad();

	// ��������
	SoundAdd("source/sound/Pass.mp3", FMOD_LOOP_OFF, SOUND_Pass);
}

void Ini_Pass(void)
{
	printf("Level_Pass: Ini\n");
	// ��ȡ��ǰ�ؿ�ʱ��
	//timeStart_level_Pass = clock();
	BackGroundStart();

	// ��������
	SoundPlay(SOUND_Pass);
}

void Update_Pass(void)
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

void Draw_Pass(void)
{
	// Ϊ��ʼ��������׼��
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	AEGfxSetBlendMode(AE_GFX_RM_TEXTURE);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	// ������ƶ����б��е����ж���
	BaseListTraverse(Visit_DrawObj);

}

void Free_Pass(void)
{

	printf("Level_Pass: free\n");
	// ʹ�ú���gameObjDestroyɾ���б��еĶ���
	BaseListTraverse(Visit_DestroyObj);
	TimerFree();
}

void Unload_Pass(void)
{
	printf("Level_Pass: Unload\n");
	DestroyGameObjBaseList(&theBaseList);
}
