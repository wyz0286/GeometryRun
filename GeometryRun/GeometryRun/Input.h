/**
 * Project:		GeometryRun
 * File Name:	Input.h
 * Author:		����
 * Date:		2017-4-22
 * Purpose:		����ģ��
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
	KeyNUM    // �ܷ������һ��
};
extern int KeyPressed[KeyNUM];

extern POINT mousPos;
extern int posType;

 //------------------------------------------------------------------------------
 // Public Functions:
 //------------------------------------------------------------------------------

 // ��������
LRESULT CALLBACK Input_Handle(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// ����״̬����
void Input_Initialize(void);
