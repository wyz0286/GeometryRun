/**
 * Project:		GeometryRun
 * File Name:	GameStateManager.c
 * Author:		王晶
 * Date:		2017-4-4
 * Purpose:		游戏状态管理模块
 */

#include "System.h"
#include "GameStateList.h"
#include "Menu.h"
#include "Staff.h"
#include "Help.h"
#include "Choose.h"
#include "Level0.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"
#include "Win.h"
#include "Lose.h"
#include "Pass.h"
#include "Calculate.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

void (*pLoad)(void);

void (*pIni)(void);

void (*pUpdate)(void);

void (*pDraw)(void);

void (*pFree)(void);

void (*pUnload)(void);

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

void GSM_Initialize(int cur)
{
	Previous = cur;
	Current = cur;
	Next = cur;
}

void GSM_Update(void)
{
	switch (Current)
	{
		case GS_Menu: {
			pLoad = Load_Menu;
			pIni = Ini_Menu;
			pUpdate = Update_Menu;
			pDraw = Draw_Menu;
			pFree = Free_Menu;
			pUnload = Unload_Menu;
			break;
		}
		case GS_Staff: {
			pLoad = Load_Staff;
			pIni = Ini_Staff;
			pUpdate = Update_Staff;
			pDraw = Draw_Staff;
			pFree = Free_Staff;
			pUnload = Unload_Staff;
			break;
		}
		case GS_Help: {
			pLoad = Load_Help;
			pIni = Ini_Help;
			pUpdate = Update_Help;
			pDraw = Draw_Help;
			pFree = Free_Help;
			pUnload = Unload_Help;
			break;
		}
		case GS_Choose: {
			pLoad = Load_Choose;
			pIni = Ini_Choose;
			pUpdate = Update_Choose;
			pDraw = Draw_Choose;
			pFree = Free_Choose;
			pUnload = Unload_Choose;
			break;
		}
    	case GS_L0: {
	    	pLoad = Load0;
		    pIni = Ini0;
		    pUpdate = Update0;
		    pDraw = Draw0;
		    pFree = Free0;
		    pUnload = Unload0;
		    break;
	    }
		case GS_L1: {
			pLoad = Load1;
			pIni = Ini1;
			pUpdate = Update1;
			pDraw = Draw1;
			pFree = Free1;
			pUnload = Unload1;
			break;
		}
		case GS_L2: {
			pLoad = Load2;
			pIni = Ini2;
			pUpdate = Update2;
			pDraw = Draw2;
			pFree = Free2;
			pUnload = Unload2;
			break;
		}
		case GS_L3: {
			pLoad = Load3;
			pIni = Ini3;
			pUpdate = Update3;
			pDraw = Draw3;
			pFree = Free3;
			pUnload = Unload3;
			break;
		}
		case GS_L4: {
			pLoad = Load4;
			pIni = Ini4;
			pUpdate = Update4;
			pDraw = Draw4;
			pFree = Free4;
			pUnload = Unload4;
			break;
		}
		case GS_Win: {
			pLoad = Load_Win;
			pIni = Ini_Win;
			pUpdate = Update_Win;
			pDraw = Draw_Win;
			pFree = Free_Win;
			pUnload = Unload_Win;
			break;
		}
		case GS_Lose: {
			pLoad = Load_Lose;
			pIni = Ini_Lose;
			pUpdate = Update_Lose;
			pDraw = Draw_Lose;
			pFree = Free_Lose;
			pUnload = Unload_Lose;
			break;
		}
		case GS_Pass: {
			pLoad = Load_Pass;
			pIni = Ini_Pass;
			pUpdate = Update_Pass;
			pDraw = Draw_Pass;
			pFree = Free_Pass;
			pUnload = Unload_Pass;
			break;
		}
		case GS_Calculate: {
			pLoad = Load_Calculate;
			pIni = Ini_Calculate;
			pUpdate = Update_Calculate;
			pDraw = Draw_Calculate;
			pFree = Free_Calculate;
			pUnload = Unload_Calculate;
			break;
		}
	}
	printf("GSM: Update\n");
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------
