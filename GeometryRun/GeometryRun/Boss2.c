#include "Boss2.h"

// Boss对象：在一定时间后产生且独特，故单独声明，生成Boss对象时需为pBoss赋值
GameObj* pBoss2;

// Boss2的状态
int Boss2Alive;		// Boss生存状态，Level4中用到
static float defaultBoss2Scale;
static int Boss2Status;
static float Boss2SkillCycle;
static int Boss2HP, Boss2AngerHP, Boss2MaxHP;
// 上下巡逻范围
static float Boss2PatrolMaxY, Boss2PatrolMinY;
// 进入的距离
static float Boss2EnterX, Boss2ImpactX;
static Vector2D Boss2IniPos;
static Vector2D Boss2EnterVel, Boss2MoveUpward, Boss2MoveDownward;
static Vector2D Boss2ImpactVelLeft, Boss2ImpactVelRight;
static float Boss2ImpactSpeed;

// Boss2上一次使用的技能
static int Boss2LastSkill;

static BossSkills boss2skills[B2SKILL_Count];
static int Boss2SkillCount;

Status Boss2Load()
{
	// ========================
	// boss2
	// ========================
	AEGfxMeshStart();
	AEGfxTriAdd(
		-1.0f, -1.0f, COLOR_DEFAULT, 0.0f, 1.0f,
		1.0f, -1.0f, COLOR_DEFAULT, 1.0f, 1.0f,
		-1.0f, 1.0f, COLOR_DEFAULT, 0.0f, 0.0f);
	AEGfxTriAdd(
		1.0f, -1.0f, COLOR_DEFAULT, 1.0f, 1.0f,
		1.0f, 1.0f, COLOR_DEFAULT, 1.0f, 0.0f,
		-1.0f, 1.0f, COLOR_DEFAULT, 0.0f, 0.0f);
	switch (Current)
	{
	//case GS_L1:
	case GS_L2:
		CreateGameObjBase(OTYPE_BOSS2, AEGfxMeshEnd(), AEGfxTextureLoad("source/image/enemy/boss2.png"), theBaseList);
		break;
	case GS_L3:
		CreateGameObjBase(OTYPE_BOSS2, AEGfxMeshEnd(), AEGfxTextureLoad("source/image/enemy/boss3.png"), theBaseList);
		break;
	default:
		CreateGameObjBase(OTYPE_BOSS2, AEGfxMeshEnd(), AEGfxTextureLoad("source/image/enemy/boss3.png"), theBaseList);
		break;
	}
	
	return OK;
}

Status Boss2Ini()
{
	Boss2Alive = FALSE;
	Boss2Status = B2STATUS_ENTER;
	Boss2HP = Boss2MaxHP;
	Boss2AngerHP = Boss2MaxHP / 2;
	Boss2SkillLoad();
	printf("\nBossHP : %d   BosAngHP: %d\n", Boss2HP, Boss2AngerHP);
	return OK;
}

Status Boss2Start()
{
	defaultBoss2Scale = 45.0f;
	pBoss2 = NULL;
	Boss2MaxHP = 30;
	Boss2Ini();
	Boss2LastSkill = B2SKILL_CREATEBLOCKS;
	Boss2ImpactSpeed = 60.0f;
	Boss2SkillCycle = 100.0f;
	// 上下巡逻范围
	Boss2PatrolMaxY = 100.0f;
	Boss2PatrolMinY = -100.0f;
	// 进入的距离
	Boss2EnterX = 30.0f;
	// 冲撞至的x
	Boss2ImpactX = -400.0f;
	Vector2DSet(&Boss2EnterVel, -138.0f, 0.0f);
	Vector2DSet(&Boss2MoveUpward, 0.0f, 90.0f);
	Vector2DSet(&Boss2MoveDownward, 0.0f, -90.0f);
	Vector2DSet(&Boss2IniPos, 500.0f, 0.0f);
	Vector2DSet(&Boss2ImpactVelLeft, -600.0f, 0.0f);
	Vector2DSet(&Boss2ImpactVelRight, 600.0f, 0.0f);
	return OK;
}

Status Boss2SkillLoad()
{
	Boss2SkillCount = 3;
	boss2skills[0] = Boss2Skill_CreateMonster;
	boss2skills[1] = Boss2Skill_CreateBlock;
	boss2skills[2] = Boss2Skill_Bullet;
	
	return OK;
}

Status Boss2Update(GameObj* pInst)
{
	pBoss2->posCurr.x += pBoss2->velCurr.x * frameTime;
	pBoss2->posCurr.y += pBoss2->velCurr.y * frameTime;
	switch (Boss2Status)
	{
		case B2STATUS_ENTER:
		{
			if (pBoss2->posCurr.x <= winMaxX - Boss2EnterX)
			{
 				Boss2Status = B2STATUS_NORMAL;
				SetObjSpeed(pBoss2, Boss2MoveUpward);
				break;
			}
			break;
		}
		case B2STATUS_NORMAL:
		{
			if (Boss2HP <= Boss2AngerHP)
			{
				Boss2Status = B2STATUS_ANGRY;
				Boss2Skill_GetAngey();
				break;
			}
			if (pBoss2->posCurr.y >= Boss2PatrolMaxY)
			{
				SetObjSpeed(pBoss2, Boss2MoveDownward);
				Boss2UseSkillRandomly(passTime);
			}
			else if (pBoss2->posCurr.y <= Boss2PatrolMinY)
			{
				SetObjSpeed(pBoss2, Boss2MoveUpward);
				Boss2UseSkillRandomly(passTime);
			}
			break;
		}
		case B2STATUS_ANGRY:
		{
			if (pBoss2->posCurr.y >= Boss2PatrolMaxY)
			{
				SetObjSpeed(pBoss2, Boss2MoveDownward);
				Boss2UseSkillRandomly(passTime);
			}
			else if (pBoss2->posCurr.y <= Boss2PatrolMinY)
			{
				SetObjSpeed(pBoss2, Boss2MoveUpward);
				Boss2UseSkillRandomly(passTime);
			}
			break;
		}
		case B2STATUS_IMPACTL:
		{
			if (pBoss2->posCurr.x <= Boss2ImpactX)
			{
				SetObjSpeed(pBoss2, Boss2ImpactVelRight);
				Boss2Status = B2STATUS_IMPACTR;
			}
			break;
		}
		case B2STATUS_IMPACTR:
		{
			if (pBoss2->posCurr.x >= winMaxX - Boss2EnterX)
			{
				if (pBoss2->posCurr.y <= 0)
					SetObjSpeed(pBoss2, Boss2MoveUpward);
				else
					SetObjSpeed(pBoss2, Boss2MoveDownward);
				Boss2Status = B2STATUS_ANGRY;
			}
			break;
		}
		default:
			break;
	}
	// Boss2Dead中恢复Boss生命值，绘制血条时在Boss2Dead前进行
	if (Boss2HP <= 0)
		Boss2Dead();
	return OK;
}

Status Boss2Collision(insNode* pinsNode)
{
	return OK;
}

Status Boss2Skill_CreateMonster(float curTime)
{
	float iniFloat = 1.0f;
	float iniMinX = winMaxX - 300.0f, iniMaxX = winMaxX, iniMinY = winMinY + 140.0f, iniMaxY = winMaxY - 140.0f, iniMinVx = -400.0f, iniMaxVx = -300.0f;
	float iniMinVy = 0.0f, iniMaxVy = 0.0f, iniMinDir = -3.0f, iniMaxDir = 3.0f;
	float CurMonsterScale = MonsterScaleGet();
	return CreateSomeObjAtSameTimeWithRange(curTime, 4, OTYPE_MONSTER, CurMonsterScale, theBaseList, 0, NULL, iniMinX, iniMaxX, iniMinY, iniMaxY, iniMinVx, iniMaxVx, iniMinVy, iniMaxVy, iniMinDir, iniMaxDir);
}

Status Boss2Skill_CreateBlock(float curTime)
{
	float CurBlockScale = BlockScaleGet();
	float iniFloat = 1.0f;
	float iniMinX = winMaxX - 300.0f, iniMaxX = winMaxX, iniMinY = winMinY + 140.0f, iniMaxY = winMaxY - 140.0f, iniMinVx = -240.0f, iniMaxVx = -120.0f;
	float iniMinVy = 0.0f, iniMaxVy = 0.0f, iniMinDir = 0.0f, iniMaxDir = 0.0f;

	return CreateSomeObjAtSameTimeWithRange(curTime, 2, OTYPE_BLOCK, CurBlockScale, theBaseList, 0, NULL, iniMinX, iniMaxX, iniMinY, iniMaxY, iniMinVx, iniMaxVx, iniMinVy, iniMaxVy, iniMinDir, iniMaxDir);

}

Status Boss2Skill_Impact(float curTime)
{
	Boss2Status = B2STATUS_IMPACTL;
	SetObjSpeed(pBoss2, Boss2ImpactVelLeft);
	return OK;
}

Status Boss2Skill_Bullet(float curTime)
{
	BossBulletCreateAtDefaultPosWithDefaultVel();
	return OK;
}

Status Boss2Skill_GetAngey()
{
	Vector2DSet(&Boss2MoveUpward, 0.0f, 140.0f);
	Vector2DSet(&Boss2MoveDownward, 0.0f, -140.0f);
	Boss2SkillCount = 4;
	boss2skills[3] = Boss2Skill_Impact;
	return OK;
}

Status Boss2UseSkillRandomly(float curTime)
{
	int CurSkill;
// 确保boss使用的技能每次都不同
	while ((CurSkill = rand() % Boss2SkillCount) == Boss2LastSkill);
	Boss2LastSkill = CurSkill;
	boss2skills[CurSkill](curTime + OFFSETTIME);
	return OK;
}

Status Boss2GetHurt()
{
	Boss2HP--;
	if (Boss2HP <= 0)
		Boss2Dead();
	return OK;
}

Status Boss2Dead(){
	GameObjDelete(pBoss2);
	Boss2Ini();
	if (Current == GS_L2)
		Next = GS_Pass;
	else if (Current == GS_L3)
		Next = GS_Win;
	return OK;
}

GameObj* Boss2Create()
{
	return CreateGameObj(OTYPE_BOSS2, defaultBoss2Scale, Boss2IniPos, Boss2EnterVel, 0, theBaseList, 0, NULL);
}

float Boss2ScaleGet()
{
	return defaultBoss2Scale;
}

Status Boss2MaxHPSet(int boss2HP)
{
	Boss2HP = boss2HP;
	return OK;
}

Status Boss2MaxHPChange(int change)
{
	Boss2HP += change;
	return OK;
}
