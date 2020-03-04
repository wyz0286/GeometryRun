#pragma once

#include "GameObjectManager.h"
#include "KeyAndObjUpdate.h"
#include "Boss2.h"
#include "Player.h"
#include <math.h>


Status BossBulletLoad();

Status BossBulletStart();

Status BossBulletUpdate(GameObj* pInst);

Status BossBulletCollision(insNode* pinsNode);

GameObj* BossBulletCreateAtDefaultPosWithDefaultVel();

Status BossBulletDefaultBossBulletVelyABSSet(float vel);

Status BossBulletDefaultVelyABSChange(float change);
