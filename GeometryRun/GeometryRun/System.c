/**
 * Project:		GeometryRun
 * File Name:	System.c
 * Author:		����
 * Date:		2017-4-22
 * Purpose:		ϵͳ����ģ��
 */

#include "System.h"
#include "AEEngine.h"
#include "Input.h"
#include "SoundSystem.h"

#pragma comment (lib, "Alpha_Engine.lib")
#pragma comment (lib, "fmodex_vc.lib")
#pragma comment (lib, "fmodexL_vc.lib")

 //------------------------------------------------------------------------------
 // Private Consts:
 //------------------------------------------------------------------------------

 //------------------------------------------------------------------------------
 // Private Structures:
 //------------------------------------------------------------------------------

 //------------------------------------------------------------------------------
 // Public Variables:
 //------------------------------------------------------------------------------

 //------------------------------------------------------------------------------
 // Private Variables:
 //------------------------------------------------------------------------------

 //------------------------------------------------------------------------------
 // Private Function Declarations:
 //------------------------------------------------------------------------------

 //------------------------------------------------------------------------------
 // Public Functions:
 //------------------------------------------------------------------------------
 // ϵͳ��ʼ��
int System_Initialize(HINSTANCE hInstance, int nCmdShow)
{
	// ����Alpha��������
	AESysInitInfo sysInitInfo;
	sysInitInfo.mAppInstance = hInstance;	// WinMain�ĵ�1������
	sysInitInfo.mShow = nCmdShow;		// WinMain�ĵ�4������
	sysInitInfo.mWinWidth = 800;
	sysInitInfo.mWinHeight = 600;
	sysInitInfo.mCreateConsole = 1;			// �Ƿ���Ҫ�򿪿���̨
	sysInitInfo.mCreateWindow = 1;			// �Ƿ���Ҫ��������
	sysInitInfo.mMaxFrameRate = 60;			// ����֡�ʣ����ʹ��Alpha��֡�ʿ��ƹ��ܵĻ���
	sysInitInfo.mpWinCallBack = Input_Handle;
	sysInitInfo.mClassStyle = CS_HREDRAW | CS_VREDRAW;		// �����ඨ����ػ淽ʽ									
	sysInitInfo.mWindowStyle = WS_DLGFRAME | WS_SYSMENU;			// ���ڷ��ȡֵ��WS_POPUP | WS_VISIBLE | WS_SYSMENU | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
															// Alphaϵͳ��ʼ�� �� ģ������
	if (0 == AESysInit(&sysInitInfo))
		return -1;
	AESysReset();
	AllocConsole();
	freopen("conout$", "w", stdout);
	printf("hello!\n");
	printf("System:Initialize\n");

	// ���ֳ�ʼ��
	SoundSystemLoad();

	return 0;
}

// ϵͳ�˳�
void System_Exit(void)
{
	// Alphaϵͳ�˳�
	AESysExit();

	// ����ϵͳ�˳�
	SoundSystemExit();
	printf("System:Exit\n");
}
