/**
 * Project:		GeometryRun
 * File Name:	CreateObjectInMap.h
 * Author:		闷声发大财
 * Date:		2017-5-28
 * Purpose:		障碍物创建模型素材库
 */
#pragma once

#include "GameObjectManager.h"
#include "KeyAndObjUpdate.h"
#include "Block.h"
#include "Platform.h"
#include "Boss2.h"

#define CreateMethods 10

extern float(*CreateObjInMapRamdom[CreateMethods])(float);

Status IniCreateRandomArrays();

float CreateObjInMap0(float startTime);

float CreateObjInMap1(float startTime);

float CreateObjInMap2(float startTime);

float CreateObjInMap3(float startTime);

float CreateObjInMap4(float startTime);

float CreateObjInMap5(float startTime);

float CreateObjInMap6(float startTime);

float CreateObjInMap7(float startTime);

float CreateObjInMap8(float startTime);

float CreateObjInMap9(float startTime);

float CreateBossInMap_Level2(float startTime);
