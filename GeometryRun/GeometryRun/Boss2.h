#pragma once

#include "GameObjectManager.h"
#include "KeyAndObjUpdate.h"
#include "TimeManager.h"
#include "Block.h"
#include "Monster.h"
#include "AIMonster.h"
#include "BossBullet.h"

// Boss������һ��ʱ�������Ҷ��أ��ʵ�������������Boss����ʱ��ΪpBoss��ֵ
extern GameObj* pBoss2;

// Boss2��״̬
extern int Boss2Alive;		// Boss����״̬��Level4���õ�

// Boss2�ļ���
enum boss2Skills{
	B2SKILL_CREATEMONSTERS,
	B2SKILL_CREATEBLOCKS,
	B2SKILL_BULLET,
	B2SKILL_IMPACT,
	B2SKILL_Count
};

typedef Status (*BossSkills)(float curTime);

// Boss2��״̬
enum boss2Status
{
	//B2STATUS_
	B2STATUS_ENTER,
	B2STATUS_NORMAL,
	B2STATUS_ANGRY,
	B2STATUS_IMPACTL,
	B2STATUS_IMPACTR,
	B2STATUS_Count
};

Status Boss2Load();

Status Boss2Ini();

Status Boss2Start();

Status Boss2Update(GameObj* pInst);

Status Boss2Collision(insNode* pinsNode);

Status Boss2SkillLoad();

Status Boss2Skill_CreateMonster(float curTime);

Status Boss2Skill_CreateBlock(float curTime);

Status Boss2Skill_GetAngey();

Status Boss2Skill_Impact(float curTime);

Status Boss2Skill_Bullet(float curTime);

Status Boss2UseSkillRandomly(float curTime);

Status Boss2Dead();

Status Boss2GetHurt();

GameObj* Boss2Create();

float Boss2ScaleGet();

Status Boss2MaxHPSet(int boss2HP);

Status Boss2MaxHPChange(int change);
