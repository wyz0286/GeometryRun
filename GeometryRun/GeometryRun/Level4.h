/**
 * Project:		GeometryRun
 * File Name:	Level4.h
 * Author:		Íõ¾§
 * Date:		2017-6-12
 * Purpose:		¹Ø¿¨4
 */

#pragma once

#include "CreateObjectInMap.h"
#include "BackGround.h"
#include "Pause.h"
#include "Block.h"
#include "Boss2.h"
#include "Bullet.h"
#include "Monster.h"
#include "AIMonster.h"
#include "Platform.h"
#include "Player.h"
#include "SoundSystem.h"

extern int stage;

void Load4(void);

void Ini4(void);

void Update4(void);

void Draw4(void);

void Free4(void);

void Unload4(void);
