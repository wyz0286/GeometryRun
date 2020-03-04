#pragma once

#include "GameObjectManager.h"
#include "BackGround.h"
#include "Input.h"
#include "Player.h"
#include "Boss2.h"
#include "Pause.h"
#include "UICalculate.h"
#include "SoundSystem.h"

#define FLAG_IMPORTANTKEY 2

extern float winMaxX, winMaxY, winMinX, winMinY;
// ��ײ��������󣬷������ʱʹ��
extern GameObj *pInstForCollisionDetect;

// ======================
// ֡ʱ�䣺Unity�е�dt
// ======================
extern float frameTime;

Status GetWinMaxMinXY();

Status KeyUpdate();

Status ObjUpdate();

Status Visit_CollisionDetect(insNode* pinsNode);

Status Visit_Matrix2DCount(insNode* pinsNode);

// never used
Status BossUpdate(int level, clock_t LevelTime, float bossOccurTime);

Status Visit_DestroyObj(insNode* pinsNode);

Status Visit_DrawObj(insNode* pinsNode);

