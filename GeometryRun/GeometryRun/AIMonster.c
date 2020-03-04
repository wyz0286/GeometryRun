#include "AIMonster.h"

// 怪物默认速度（与关卡相关）
Vector2D defaultAIMonsterVel;
float defaultAIMonsterVelyABS;		// 纵轴移动速度绝对值，可更改
static float defaultAIMonsterScale;

Status AIMonsterLoad()
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
	switch(Current)
	{
	case GS_L2:
		CreateGameObjBase(OTYPE_AIMONSTER, AEGfxMeshEnd(), AEGfxTextureLoad("source/image/enemy/StarAIMonster.png"), theBaseList);
		break;
	case GS_L3:
		CreateGameObjBase(OTYPE_AIMONSTER, AEGfxMeshEnd(), AEGfxTextureLoad("source/image/enemy/DiamondAIMonster.png"), theBaseList);
		break;
	case GS_L4:
		CreateGameObjBase(OTYPE_AIMONSTER, AEGfxMeshEnd(), AEGfxTextureLoad("source/image/enemy/StarAIMonster.png"), theBaseList);
		break;
	default:
		CreateGameObjBase(OTYPE_AIMONSTER, AEGfxMeshEnd(), AEGfxTextureLoad("source/image/enemy/StarAIMonster.png"), theBaseList);
		break;
	}
	
	return OK;
}

Status AIMonsterStart()
{
	Vector2DSet(&defaultAIMonsterVel, -10.0f, 0.0f);
	defaultAIMonsterVelyABS = 100.0f;
	defaultAIMonsterScale = 30.0f;
	return OK;
}

Status AIMonsterUpdate(GameObj* pInst)
{
	Vector2D CurPlayerPos = PlayerPosGet();
	if (pInst->posCurr.y > CurPlayerPos.y)
		pInst->velCurr.y = -1 * defaultAIMonsterVelyABS;
	else
		pInst->velCurr.y = defaultAIMonsterVelyABS;

	pInst->posCurr.x += pInst->velCurr.x * frameTime;
	pInst->posCurr.y += pInst->velCurr.y * frameTime;
	if ((pInst->posCurr.x < winMinX) || (pInst->posCurr.x > winMaxX) || (pInst->posCurr.y < winMinY) || (pInst->posCurr.y > winMaxY))
		GameObjDelete(pInst);
	return OK;
}

Status AIMonsterCollision(insNode* pinsNode)
{
	return OK;
}

GameObj* AIMonsterCreateAtPos(Vector2D aimonsterPos)
{
	return CreateGameObj(OTYPE_AIMONSTER, defaultAIMonsterScale, aimonsterPos, defaultAIMonsterVel, 0, theBaseList, 0, NULL);
}

Status AIMonsterDefaultVelSet(float vx, float vy)
{
	Vector2DSet(&defaultAIMonsterVel, vx, vy);
	return OK;
}

Status AIMonsterDefaultVelyABSChange(float change)
{
	defaultAIMonsterVelyABS += change;
	return OK;
}

Status AIMonsterDefaultVxChange(float change)
{
	defaultAIMonsterVel.x += change;
	return OK;
}


