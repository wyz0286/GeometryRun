#include "Bullet.h"

static Vector2D defaultBulletVel;
static float defaultBulletScale;

Status BulletLoad()
{
	// ========================
	// �ӵ�
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
	CreateGameObjBase(OTYPE_BULLET, AEGfxMeshEnd(), AEGfxTextureLoad("source/image/player/playerbullet.png"), theBaseList);
	return OK;
}

Status BulletStart()
{
	defaultBulletScale = 9.0f;
	Vector2DSet(&defaultBulletVel, 400.0f, 0.0f);
	return OK;
}

Status BulletUpdate(GameObj* pInst)
{
	pInst->posCurr.x += pInst->velCurr.x * frameTime;
	pInst->posCurr.y += pInst->velCurr.y * frameTime;
	if ((pInst->posCurr.x < winMinX) || (pInst->posCurr.x > winMaxX) || (pInst->posCurr.y < winMinY) || (pInst->posCurr.y > winMaxY))
		GameObjDelete(pInst);
	return OK;
}

Status BulletCollision(insNode* pinsNode)
{
	GameObj* pInstOther = &(pinsNode->gameobj);

	switch (pInstOther->pObject->type)
	{
		//BULLET VS MONSTER/AIMONSTER
		case OTYPE_MONSTER:
		case OTYPE_AIMONSTER:
		{
			// ��ײ���
			if (StaticCircleToStaticCircle(&(pInstForCollisionDetect->posCurr), pInstForCollisionDetect->scale, &(pInstOther->posCurr), pInstOther->scale))
			{
				// ײ��Monster�������ӵ���MONSTER
				GameObjDelete(pInstOther);
				GameObjDelete(pInstForCollisionDetect);
			}
			break;//BULLET VS MONSTER/AIMONSTER����
		}

		//BULLET VS BLOCK
		case OTYPE_BLOCK:
		{
			// ��ײ���
			if (StaticCircleToStaticCircle(&(pInstForCollisionDetect->posCurr), pInstForCollisionDetect->scale, &(pInstOther->posCurr), pInstOther->scale))
			{
				// ײ��BLOCK������BULLET
				GameObjDelete(pInstForCollisionDetect);
			}
			break;//BULLET VS BLOCK����
		}
		case OTYPE_BOSS2:
		{
			// ��ײ���
			if (StaticCircleToStaticCircle(&(pInstForCollisionDetect->posCurr), pInstForCollisionDetect->scale, &(pInstOther->posCurr), pInstOther->scale))
			{
				// ײ��BOSS2, ��Ѫ,����BULLET
				Boss2GetHurt();
				GameObjDelete(pInstForCollisionDetect);
			}
		}
		default:
			break;
	}
	return OK;
}

GameObj* BulletCreateAtPos(Vector2D bulletPos)
{
	return CreateGameObj(OTYPE_BULLET, defaultBulletScale, bulletPos, defaultBulletVel, 0, theBaseList, 0, NULL);
}

GameObj* BulletCreateAtPosWithVel(Vector2D bulletPos, Vector2D bulletVel)
{
	return CreateGameObj(OTYPE_BULLET, defaultBulletScale, bulletPos, bulletVel, 0, theBaseList, 0, NULL);
}
