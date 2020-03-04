#include "BossBullet.h"

// 子弹速度
static float defaultBossBulletVelyABS;
static float BossBulletDir, defaultBossBulletScale;

Status BossBulletLoad()
{
	// ========================
	// 子弹
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
	CreateGameObjBase(OTYPE_BOSSBULLET, AEGfxMeshEnd(), AEGfxTextureLoad("source/image/enemy/bossbullet.png"), theBaseList);
	return OK;
}

Status BossBulletStart()
{
	defaultBossBulletScale = 12.0f;
	defaultBossBulletVelyABS = 10.0f;
	return OK;
}

Status BossBulletUpdate(GameObj* pInst)
{
	pInst->posCurr.x += pInst->velCurr.x * frameTime;
	pInst->posCurr.y += pInst->velCurr.y * frameTime;
	if ((pInst->posCurr.x < winMinX) || (pInst->posCurr.x > winMaxX) || (pInst->posCurr.y < winMinY) || (pInst->posCurr.y > winMaxY))
		GameObjDelete(pInst);
	return OK;
}

Status BossBulletCollision(insNode* pinsNode)
{
	GameObj* pInstOther = &(pinsNode->gameobj);
	if (pInstOther->pObject->type == OTYPE_PLAYER)
	{
		//BossBullet VS Player
		// 碰撞检测
		if (StaticCircleToStaticCircle(&(pInstForCollisionDetect->posCurr), pInstForCollisionDetect->scale, &(pInstOther->posCurr), pInstOther->scale))
		{
			// 撞上Player，Player掉血
			if (!isProtected)
				PlayerGetHurt(1);
			printf("\n Collision with the %s: Pos(%.1f, %.1f)\n Restart\n", ObjTypeName[pInstOther->pObject->type], pInstOther->posCurr.x, pInstOther->posCurr.y);
			GameObjDelete(pInstForCollisionDetect);
		}
	}
	return OK;
}


// 实例化方法
GameObj* BossBulletCreateAtDefaultPosWithDefaultVel()
{
	float CurBoss2Scale = Boss2ScaleGet();
	Vector2D CurPlayerPos = PlayerPosGet();
	Vector2D iniBossBulletPos, Velocity_BossBullet;
	Vector2DSet(&iniBossBulletPos, pBoss2->posCurr.x - 1.5 * CurBoss2Scale, pBoss2->posCurr.y);
	BossBulletDir = Vector2DAngle(&iniBossBulletPos, &CurPlayerPos);
	Vector2DSet(&Velocity_BossBullet, defaultBossBulletVelyABS * cosf(BossBulletDir / 180 * PI), defaultBossBulletVelyABS * sinf(BossBulletDir / 180 * PI));
	printf("  vel : %.1f   %.1f\n", Velocity_BossBullet.x, Velocity_BossBullet.y);
	return CreateGameObj(OTYPE_BOSSBULLET, defaultBossBulletScale, iniBossBulletPos, Velocity_BossBullet, BossBulletDir, theBaseList, 0, NULL);
}


Status BossBulletDefaultBossBulletVelyABSSet(float vel)
{
	defaultBossBulletVelyABS = vel;
	return OK;
}

Status BossBulletDefaultVelyABSChange(float change)
{
	defaultBossBulletVelyABS += change;
	return OK;
}

