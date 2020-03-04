/* Project:GeometryRun
File Name:	Help.c
Author:		˧����
Date:
Purpose:		����  */

#include "Help.h"

#define MAX_TIME 2.0f

void Load_Help(void)
{
	printf("Level_Help: Load\n");
	theBaseList = NULL;

	// ���ó���
	SetConstants();
	// ��ʼ����Ϸ��������ʵ���б�
	InitialGameObjBaseList(&theBaseList);

	BackGroundLoad();

}

void Ini_Help(void)
{
	printf("Level_Help: Ini\n");
	Vector2D iniPosition_Images = { 0.0f, 0.0f };
	Vector2D iniVelocity_Images = { 0.0f, 0.0f };

	xcurrentFrame = 0;
	elpasedTime = 0;

	// ����ʵ������
	pImage = BackGroundCreateWithPosAndVel(iniPosition_Images, iniVelocity_Images);

}

void Update_Help(void)
{

	GetWinMaxMinXY();

	// =========================
	// ��Ϸ�߼���Ӧ����
	// =========================
	KeyUpdate();

	elpasedTime += frameTime;

	if (elpasedTime > MAX_TIME)
	{
		++xcurrentFrame;
		elpasedTime = 0;
	}
	// =====================================
	// �������ж����2D�任����
	// =====================================
	BaseListTraverse(Visit_Matrix2DCount);

}

void Draw_Help(void)
{

	// Ϊ��ʼ��������׼��
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	AEGfxSetBlendMode(AE_GFX_RM_TEXTURE);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

	// ��������
	AEGfxTextureSet(pImage->pObject->pTex, xcurrentFrame / 6.0f, 0);
	// ���ö����2D�任����ʹ�ú�����AEGfxSetTransform
	AEGfxSetTransform(pImage->transform.m);
	// ���Ƶ�ǰ����ʹ�ú�����AEGfxMeshDraw
	AEGfxMeshDraw(pImage->pObject->pMesh, AE_GFX_MDM_TRIANGLES);

}

void Free_Help(void)
{
	printf("Level_Help: free\n");
	// ʹ�ú���gameObjDestroyɾ���б��еĶ���
	BaseListTraverse(Visit_DestroyObj);
}

void Unload_Help(void)
{
	printf("Level_Help: Unload\n");
	DestroyGameObjBaseList(&theBaseList);
}
