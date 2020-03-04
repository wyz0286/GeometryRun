#pragma once

#include "GameObjectManager.h"
#include "KeyAndObjUpdate.h"

Status PlatformLoad();

Status PlatformStart();

Status PlatformUpdate(GameObj* pInst);

float PlatformHeightGet();
