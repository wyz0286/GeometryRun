#pragma once

/**
* Project:		Geometry Run
* File Name:	Pause.h
* Author:		Íõ¾§
* Date:			2017-6-7
* Purpose:		realize pause function
*/

#include "GameObjectManager.h"
#include "KeyAndObjUpdate.h"
#include "GameStateList.h"
#include "input.h"

extern int isPaused;
extern int endPause;
extern int pauseCreated;
extern clock_t pauseStartTime;
extern clock_t pauseEndTime;
extern Vector2D iniPosition_Pause;

extern GameObj *pPause;

Status PauseLoad();

Status PauseStart();

GameObj* PauseCreate();
