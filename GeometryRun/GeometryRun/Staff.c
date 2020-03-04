#include "Staff.h"

void Load_Staff(void)
{
	// ��ʼ��ʱ��ϵͳ
	//TimerIni(&timeStart_level_Lose);

	printf("Level_Staff: Load\n");
	theBaseList = NULL;
	// ���ó���
	SetConstants();
	// ��ʼ����Ϸ��������ʵ���б�
	InitialGameObjBaseList(&theBaseList);

	BackGroundLoad();
}

void Ini_Staff(void)
{
	printf("Level_Staff: Ini\n");
	// ��ȡ��ǰ�ؿ�ʱ��
	//timeStart_level_Lose = clock();
	BackGroundStart();
}

void Update_Staff(void)
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

void Draw_Staff(void)
{
	// Ϊ��ʼ��������׼��
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	AEGfxSetBlendMode(AE_GFX_RM_TEXTURE);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	// ������ƶ����б��е����ж���
	BaseListTraverse(Visit_DrawObj);

}

void Free_Staff(void)
{

	printf("Level_Staff: free\n");
	// ʹ�ú���gameObjDestroyɾ���б��еĶ���
	BaseListTraverse(Visit_DestroyObj);
	TimerFree();
}

void Unload_Staff(void)
{
	printf("Level_Staff: Unload\n");
	DestroyGameObjBaseList(&theBaseList);
}
