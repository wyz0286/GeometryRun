#pragma once

#include "GameObjectManager.h"
#include "KeyAndObjUpdate.h"

Status MonsterLoad();

Status MonsterStart();

Status MonsterUpdate(GameObj* pInst);

Status MonsterCollision(insNode* pinsNode);

GameObj* MonsterCreateAtPosWithVel(Vector2D monsterPos, Vector2D monsterVel);

GameObj* MonsterCreateAtPos(Vector2D monsterPos);

float MonsterScaleGet();

Status MonsterDefaultVelSet(float vx, float vy);

Status MonsterDefaultVxChange(float change);
