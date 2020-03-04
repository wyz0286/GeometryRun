/* Project:GeometryRun
File Name:	Level0.c
Author:		˧����
Date:
Purpose:		�ؿ�0������ģʽ��  */

#include "Level0.h"

#define MAX_TIME 2.0f

void Load0(void)
{
	printf("Level0: Load\n");
	theBaseList = NULL;

	// ���ó���
	SetConstants();
	// ��ʼ����Ϸ��������ʵ���б�
	InitialGameObjBaseList(&theBaseList);

	BackGroundLoad();

}

void Ini0(void)
{
	printf("Level0: Ini\n");
	Vector2D iniPosition_Images = { 0.0f, 0.0f };
	Vector2D iniVelocity_Images = { 0.0f, 0.0f };

	xcurrentFrame = 0;
	elpasedTime = 0;

	// ����ʵ������
	pImage = BackGroundCreateWithPosAndVel(iniPosition_Images, iniVelocity_Images);

}

void Update0(void)
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

void Draw0(void)
{
	
	// Ϊ��ʼ��������׼��
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	AEGfxSetBlendMode(AE_GFX_RM_TEXTURE);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

	// ��������
	AEGfxTextureSet(pImage->pObject->pTex, xcurrentFrame/12.0f, 0);
	// ���ö����2D�任����ʹ�ú�����AEGfxSetTransform
	AEGfxSetTransform(pImage->transform.m);
	// ���Ƶ�ǰ����ʹ�ú�����AEGfxMeshDraw
	AEGfxMeshDraw(pImage->pObject->pMesh, AE_GFX_MDM_TRIANGLES);

}

void Free0(void)
{
	printf("Level0: free\n");
	// ʹ�ú���gameObjDestroyɾ���б��еĶ���
	BaseListTraverse(Visit_DestroyObj);
}

void Unload0(void)
{
	printf("Level0: Unload\n");
	DestroyGameObjBaseList(&theBaseList);
}
