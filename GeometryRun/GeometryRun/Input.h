/**
 * Project:		GeometryRun
 * File Name:	Input.h
 * Author:		王晶
 * Date:		2017-4-22
 * Purpose:		输入模块
 */

#pragma once

 //------------------------------------------------------------------------------
 // Typedef:
 //------------------------------------------------------------------------------

 //------------------------------------------------------------------------------
 // Public Consts:
 //------------------------------------------------------------------------------

 //------------------------------------------------------------------------------
 // Public Structures:
 //------------------------------------------------------------------------------

 //------------------------------------------------------------------------------
 // Public Variables:
 //------------------------------------------------------------------------------

enum {
	KeyR,
	KeyESC,
	Key0,
	Key1,
	Key2,
	Key3,
	Key4,
	Key6,
	Key7,
	Key8,
	KeyUp,
	KeyDown,
	KeySpace,
	KeyM,
	KeyW,
	KeyS,
	KeyJ,
	KeyP,
	KeyB,
	KeyK,
	KeyLButton,
	KeyVolumeUp,
	KeyVolumeDown,
	KeyVolumeStop,
	KeyNUM    // 总放在最后一个
};
extern int KeyPressed[KeyNUM];

extern POINT mousPos;
extern int posType;

 //------------------------------------------------------------------------------
 // Public Functions:
 //------------------------------------------------------------------------------

 // 处理输入
LRESULT CALLBACK Input_Handle(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// 输入状态重置
void Input_Initialize(void);
