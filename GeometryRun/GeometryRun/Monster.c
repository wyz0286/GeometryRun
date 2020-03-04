#include "Monster.h"

// 怪物默认速度（与关卡相关）
static Vector2D defaultMonsterVel;

static float defaultMonsterScale;

Status MonsterLoad()
{
	// ========================
	// 怪物
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
	case GS_L1:
		CreateGameObjBase(OTYPE_MONSTER, AEGfxMeshEnd(), AEGfxTextureLoad("source/image/enemy/TriangleMonster.png"), theBaseList);
		break;
	case GS_L2:
		CreateGameObjBase(OTYPE_MONSTER, AEGfxMeshEnd(), AEGfxTextureLoad("source/image/enemy/StarMonster.png"), theBaseList);
		break;
	case GS_L3:
		CreateGameObjBase(OTYPE_MONSTER, AEGfxMeshEnd(), AEGfxTextureLoad("source/image/enemy/DiamondMonster.png"), theBaseList);
		break;
	case GS_L4:
		CreateGameObjBase(OTYPE_MONSTER, AEGfxMeshEnd(), AEGfxTextureLoad("source/image/enemy/StarMonster.png"), theBaseList);
		break;
	}
	
	return OK;
}

Status MonsterStart()
{
	defaultMonsterScale = 30.0f;
	Vector2DSet(&defaultMonsterVel, -300.0f, 0.0f);
	return OK;
}

Status MonsterUpdate(GameObj* pInst)
{
	pInst->posCurr.x += pInst->velCurr.x * frameTime;
	pInst->posCurr.y += pInst->velCurr.y * frameTime;
	if ((pInst->posCurr.x < winMinX) || (pInst->posCurr.x > winMaxX) || (pInst->posCurr.y < winMinY) || (pInst->posCurr.y > winMaxY))
		GameObjDelete(pInst);
	return OK;
}

Status MonsterCollision(insNode* pinsNode)
{
	return OK;
}

GameObj* MonsterCreateAtPosWithVel(Vector2D monsterPos, Vector2D monsterVel)
{
	return CreateGameObj(OTYPE_MONSTER, defaultMonsterScale, monsterPos, monsterVel, 0, theBaseList, 0, NULL);
}

GameObj* MonsterCreateAtPos(Vector2D monsterPos)
{
	return CreateGameObj(OTYPE_MONSTER, defaultMonsterScale, monsterPos, defaultMonsterVel, 0, theBaseList, 0, NULL);
}

float MonsterScaleGet()
{
	return defaultMonsterScale;
}

Status MonsterDefaultVelSet(float vx, float vy)
{
	Vector2DSet(&defaultMonsterVel, vx, vy);
	return OK;
}

Status MonsterDefaultVxChange(float change)
{
	defaultMonsterVel.x += change;
	return OK;
}
