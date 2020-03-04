/**
 * Project:		GeometryRun
 * File Name:	main.c
 * Author:		����
 * Date:		2017-4-22
 * Purpose:		main����
 */

#include <Windows.h>
#include "System.h"
#include "GameStateList.h"
#include "GameStateManager.h"
#include "Input.h"
#include "AEEngine.h"

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
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// System Initialize
	System_Initialize(hInstance, nCmdShow);

	// GSM Initialize
	GSM_Initialize(GS_Menu);

	// Game Flow
	while (Current != GS_Quit)
	{
		if (Current == GS_Restart)
		{
			Current = Previous;
			Next = Previous;
		}
		else
		{
			// GSM Update
			GSM_Update();
			pLoad();
		}

		pIni();

		// Game Loop
		while (Current == Next)
		{
			// Alpha - ֡��ʼ
			AESysFrameStart();
			//Input_Handle();  �ص�����
			pUpdate();
			pDraw();
			Input_Initialize();
			// Alpha - ֡����
			AESysFrameEnd();
		}

		pFree();

		if (Next != GS_Restart)
			pUnload();

		Previous = Current;
		Current = Next;
	}

	// System Exit
	System_Exit();
	return 0;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------
