#include "Block.h"

// 障碍物默认速度（与关卡相关）
static Vector2D defaultBlockVel;
static float defaultBlockScale;

Status BlockLoad()
{
	// ========================
	// 障碍物
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
	CreateGameObjBase(OTYPE_BLOCK, AEGfxMeshEnd(), AEGfxTextureLoad("source/image/enemy/theBlock2.png"), theBaseList);
	return OK;
}

Status BlockStart()
{
	defaultBlockScale = 30.0f;
	Vector2DSet(&defaultBlockVel, -10.0f, 0.0f);
	return OK;
}

Status BlockUpdate(GameObj* pInst)
{
	pInst->posCurr.x += pInst->velCurr.x * frameTime;
	pInst->posCurr.y += pInst->velCurr.y * frameTime;
	if ((pInst->posCurr.x < winMinX) || (pInst->posCurr.x > winMaxX) || (pInst->posCurr.y < winMinY) || (pInst->posCurr.y > winMaxY))
		GameObjDelete(pInst);
	return OK;
}

Status BlockCollision(insNode* pinsNode)
{
	return OK;
}

GameObj* BlockCreateAtPosWithVel(Vector2D blockPos, Vector2D blockVel)
{
	return CreateGameObj(OTYPE_BLOCK, defaultBlockScale, blockPos, blockVel, 0, theBaseList, 0, NULL);
}

GameObj* BlockCreateAtPos(Vector2D blockPos)
{
	return CreateGameObj(OTYPE_BLOCK, defaultBlockScale, blockPos, defaultBlockVel, 0, theBaseList, 0, NULL);
}

float BlockScaleGet()
{
	return defaultBlockScale;
}

Status BlockDefaultVelSet(float vx, float vy)
{
	Vector2DSet(&defaultBlockVel, vx, vy);
	return OK;
}

Status BlockDefaultVxChange(float change)
{
	defaultBlockVel.x += change;
	return OK;
}

////Status BlockDead()
//{
//
//}
