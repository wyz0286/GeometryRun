/**
 * Project:		GeometryRun
 * File Name:	System.c
 * Author:		王晶
 * Date:		2017-4-22
 * Purpose:		系统处理模块
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
 // 系统初始化
int System_Initialize(HINSTANCE hInstance, int nCmdShow)
{
	// 利用Alpha创建窗口
	AESysInitInfo sysInitInfo;
	sysInitInfo.mAppInstance = hInstance;	// WinMain的第1个参数
	sysInitInfo.mShow = nCmdShow;		// WinMain的第4个参数
	sysInitInfo.mWinWidth = 800;
	sysInitInfo.mWinHeight = 600;
	sysInitInfo.mCreateConsole = 1;			// 是否需要打开控制台
	sysInitInfo.mCreateWindow = 1;			// 是否需要创建窗口
	sysInitInfo.mMaxFrameRate = 60;			// 设置帧率（如果使用Alpha的帧率控制功能的话）
	sysInitInfo.mpWinCallBack = Input_Handle;
	sysInitInfo.mClassStyle = CS_HREDRAW | CS_VREDRAW;		// 窗口类定义的重绘方式									
	sysInitInfo.mWindowStyle = WS_DLGFRAME | WS_SYSMENU;			// 窗口风格，取值：WS_POPUP | WS_VISIBLE | WS_SYSMENU | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
															// Alpha系统初始化 及 模块重置
	if (0 == AESysInit(&sysInitInfo))
		return -1;
	AESysReset();
	AllocConsole();
	freopen("conout$", "w", stdout);
	printf("hello!\n");
	printf("System:Initialize\n");

	// 音乐初始化
	SoundSystemLoad();

	return 0;
}

// 系统退出
void System_Exit(void)
{
	// Alpha系统退出
	AESysExit();

	// 音乐系统退出
	SoundSystemExit();
	printf("System:Exit\n");
}
