#pragma once

#include "GameObjectManager.h"
#include "KeyAndObjUpdate.h"
#include "GameStateList.h"
#include "input.h"
#include "UIStatus.h"

enum {
	BTYPE_MENU_START = 0,
	BTYPE_MENU_CHOOSE,
	BTYPE_MENU_HELP,
	BTYPE_MENU_STAFF,
	BTYPE_MENU_EXIT,
	BTYPE_PASS_NEXT,
	BTYPE_PASS_MENU,
	BTYPE_WIN_RESTART,
	BTYPE_WIN_MENU,
	BTYPE_LOSE_RESTART,
	BTYPE_LOSE_MENU,
	BTYPE_CALCULATE_MENU,
	BTYPE_CALCULATE_RESTART,
	BTYPE_FALSE,
	BTYPE_COUNT,
	BTYPE_CHOOSE_1,
	BTYPE_CHOOSE_2,
	BTYPE_CHOOSE_3,
	BTYPE_CHOOSE_4
};

// ����Level0��Help�п��ƶ�������
extern GameObj* pImage;
extern int xcurrentFrame;
extern float elpasedTime;

// ��ʼ���꼰�ٶ�
extern Vector2D iniPosition_Background;
extern Vector2D iniVelocity_Background;

Status BackGroundLoad();

Status BackGroundStart();

Status BackGroundUpdate(GameObj* pInst);

Status mousIsInRect(int minX, int minY, int maxX, int maxY);

int JudgeMousPos();

GameObj* BackGroundCreateWithPosAndVel(Vector2D thePos, Vector2D theVel);
