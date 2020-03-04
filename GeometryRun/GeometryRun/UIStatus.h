#pragma once

#include "GameObjectManager.h"
#include "KeyAndObjUpdate.h"
#include "GameStateList.h"
#include "Player.h"
#include "BackGround.h"
#include "Level4.h"

#define SIZE_STAGE 2// ��ʾ�Ľ׶ε�λ��

enum {
	STYPE_LEVEL,
	STYPE_UNLIMITED,
	STYPE_COUNT
};

extern Status UIStatusLoad();

extern Status UIStatusStart();

extern Status UIStatusUpdate();

extern float UIStatusScaleGet();

