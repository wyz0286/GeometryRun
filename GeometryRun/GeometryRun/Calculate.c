/**
 * Project:		GeometryRun
 * File Name:	Calculate.c
 * Author:		˧����
 * Date:		2017-6-21
 * Purpose:		�޾�ģʽ�ؿ�����
 */

#include "Calculate.h"

void Load_Calculate(void)
{
	printf("Level_Calculate: Load\n");
	theBaseList = NULL;
	// ���ó���
	SetConstants();
	// ��ʼ����Ϸ��������ʵ���б�
	InitialGameObjBaseList(&theBaseList);

	BackGroundLoad();
	UICalculateLoad();
}

void Ini_Calculate(void)
{
	printf("Level_Calculate: Ini\n");
	// ��ȡ��ǰ�ؿ�ʱ��
	//timeStart_level_Win = clock();
	BackGroundStart();
	UICalculateStart();


}

void Update_Calculate(void)
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

void Draw_Calculate(void)
{
	// Ϊ��ʼ��������׼��
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	AEGfxSetBlendMode(AE_GFX_RM_TEXTURE);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	// ������ƶ����б��е����ж���
	BaseListTraverse(Visit_DrawObj);

}

void Free_Calculate(void)
{

	printf("Level_Calculate: free\n");
	// ʹ�ú���gameObjDestroyɾ���б��еĶ���
	BaseListTraverse(Visit_DestroyObj);
	TimerFree();
}

void Unload_Calculate(void)
{
	printf("Level_Calculate: Unload\n");
	DestroyGameObjBaseList(&theBaseList);
}
