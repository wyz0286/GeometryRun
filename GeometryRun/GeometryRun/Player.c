#include "Player.h"

// Player对象：因为是Player，所以单独声明，方便程序设计
static GameObj* pHero;

// 初始坐标
static Vector2D iniPosition_Player;

static int MaxBulletCount, CurSupplyTime, SupplyTime, BulletCount, ClearCount;

static AEGfxTexture* pTex_Hero;
//jumpCheck:跳跃次数，用于二级跳
static int jumpCheck, dropCheck;
int isProtected, ClearUsed;
// 用于设置保护时间的长短
int ProtectCur, MaxProtectCur;
static int PlayerHP;

Status PlayerLoad()
{
	// =========================
	// 主角
	// =========================
	AEGfxMeshStart();
	AEGfxTriAdd(
		-1.0f, -1.0f, COLOR_DEFAULT, 0.0f, 1.0f,
		1.0f, -1.0f, COLOR_DEFAULT, 1.0f, 1.0f,
		-1.0f, 1.0f, COLOR_DEFAULT, 0.0f, 0.0f);
	AEGfxTriAdd(
		1.0f, -1.0f, COLOR_DEFAULT, 1.0f, 1.0f,
		1.0f, 1.0f, COLOR_DEFAULT, 1.0f, 0.0f,
		-1.0f, 1.0f, COLOR_DEFAULT, 0.0f, 0.0f);

	CreateGameObjBase(OTYPE_PLAYER, AEGfxMeshEnd(), AEGfxTextureLoad("source/image/player/thePlayer.png"), theBaseList);
	return OK;
}

Status PlayerStart()
{
	Vector2DSet(&iniPosition_Player, -250.0f, 40.0f);
	jumpCheck = 0;
	dropCheck = 0;
	PlayerHP = 3;
	ProtectCur = 0;
	MaxProtectCur = 70;
	ClearCount = 1;

	MaxBulletCount = 8;
	CurSupplyTime = 0;
	SupplyTime = 30;
	BulletCount = 4;
	pHero = CreateGameObj(OTYPE_PLAYER, SIZE_HERO, iniPosition_Player, zero, 0, theBaseList, 0, NULL);
	return OK;
}

Status PlayerUpdate(GameObj* pInst)
{

	// Player跳起后的重力效应
	if (jumpCheck > 0)
		pHero->velCurr.y -= GRAVITY * frameTime;

	// 控制玩家player跳跃、倒挂
	if (KeyPressed[KeyDown] == TRUE || KeyPressed[KeyS] == TRUE)
	{
		if (jumpCheck > 0)
		{
			jumpCheck = -1;
			dropCheck = 1;
			pHero->velCurr.y = -DROP_VELOCITY;
		}
		else if (jumpCheck == 0)
		{
			jumpCheck = -1;
			dropCheck = 0;
			pHero->velCurr.y = -DROP_VELOCITY;
		}
	}
	if (KeyPressed[KeyW] == TRUE || KeyPressed[KeyUp] == TRUE)
	{
		printf("Input : up\n");
		if (jumpCheck == -1 && !dropCheck)		// 倒挂或在平台底下
		{
			jumpCheck = 0;
			pHero->velCurr.y = DROP_VELOCITY;
		}
		else if (jumpCheck < 2 && !dropCheck)
		{
			pHero->velCurr.y = JUMP_VELOCITY;
			jumpCheck++;
		}
	}
	if (CurSupplyTime <= SupplyTime)
	{
		CurSupplyTime++;
	}
	else
	{
		if (BulletCount < MaxBulletCount)
			BulletCount++;
		CurSupplyTime = 0;
	}
	if (KeyPressed[KeyJ] == TRUE || KeyPressed[KeySpace] == TRUE)
	{
		Vector2D iniBulletPos = { pHero->posCurr.x + 1.5 * SIZE_HERO, pHero->posCurr.y };
		if (BulletCount > 0)
			BulletCount--;
		else
			return OK;
		BulletCreateAtPos(iniBulletPos);
	}

	// K/B清屏技能
	if (KeyPressed[KeyK] == TRUE || KeyPressed[KeyB] == TRUE)
	{
		if (!ClearCount)
			return OK;
		ClearCount = 0;
		BaseListTraverse(PlayerClear);
		return OK;
	}

	pHero->posCurr.x += pHero->velCurr.x * frameTime;
	pHero->posCurr.y += pHero->velCurr.y * frameTime;
	return OK;
}

Status PlayerCollision(insNode* pinsNode)
{
	GameObj* pInstOther = &(pinsNode->gameobj);
	float CurPlatformHeight = PlatformHeightGet();
	switch (pInstOther->pObject->type)
	{
			// Player vs. Platform
		case OTYPE_PLATFORM:
		{
			// 检测位置调整主角方向
			if (pInstForCollisionDetect->posCurr.y >= 0)
			{
				pInstForCollisionDetect->properties[0].value = 1;
			}
			else
			{
				pInstForCollisionDetect->properties[0].value = -1;
			}
			//是否在平台上
			if ((pInstForCollisionDetect->posCurr.y) <= pInstForCollisionDetect->scale + CurPlatformHeight)
			{
				dropCheck = 0;
				if (jumpCheck > 0)	// 自由落体过程
				{
					jumpCheck = 0;
					pInstForCollisionDetect->velCurr.y = 0.0f;
					pInstForCollisionDetect->posCurr.y = pInstForCollisionDetect->scale + CurPlatformHeight;
				}
				else if (jumpCheck == 0)
				{
					if (pInstForCollisionDetect->posCurr.y >= pInstForCollisionDetect->scale)			// 翻转回地上过程
					{
						pInstForCollisionDetect->velCurr.y = 0.0f;
						pInstForCollisionDetect->posCurr.y = pInstForCollisionDetect->scale + CurPlatformHeight;
					}
				}
				else if (pInstForCollisionDetect->posCurr.y <= -1 * pInstForCollisionDetect->scale - CurPlatformHeight)		// 迅速下落过程
				{
					pInstForCollisionDetect->velCurr.y = 0.0f;
					pInstForCollisionDetect->posCurr.y = -1 * pInstForCollisionDetect->scale - CurPlatformHeight;
				}
			}
			else
			{
				if (jumpCheck == 0)
				{
					pInstForCollisionDetect->velCurr.y = 0.0f;
					pInstForCollisionDetect->posCurr.y = pInstForCollisionDetect->scale + CurPlatformHeight;
				}
			}
		}
		break;//Player VS Platform结束

		// Player vs. Block/Monster/AIMonster
		case OTYPE_BLOCK:
		case OTYPE_MONSTER:
		case OTYPE_AIMONSTER:
		{
			// 碰撞检测
			if (StaticCircleToStaticCircle(&(pInstForCollisionDetect->posCurr), pInstForCollisionDetect->scale, &(pInstOther->posCurr), pInstOther->scale))
			{
				// 撞上BLOCK死亡
				// 重新开始关卡
				if (!isProtected)
					PlayerGetHurt(1);
				printf("\n Collision with the %s: Pos(%.1f, %.1f)\n Restart\n", ObjTypeName[pInstOther->pObject->type], pInstOther->posCurr.x, pInstOther->posCurr.y);
			}
		}
		break;// Player vs. Block/Monster/AIMonster结束

		case OTYPE_BOSS2:
		// 碰撞检测
		if (StaticCircleToStaticCircle(&(pInstForCollisionDetect->posCurr), pInstForCollisionDetect->scale, &(pInstOther->posCurr), pInstOther->scale))
		{
			// hero HP-1
			if (!isProtected)
				PlayerGetHurt(2);
			printf("\n Collision with the Boss2: Pos(%.1f, %.1f)\n", pInstOther->posCurr.x, pInstOther->posCurr.y);
		}
		break;
		default:
			break;
	}

	return OK;
}

//清屏技能
Status PlayerClear(insNode* pinsNode)
{
	GameObj* pInstOther = &(pinsNode->gameobj);

	switch (pInstOther->pObject->type)
	{
	case OTYPE_BLOCK:
	case OTYPE_MONSTER:
	case OTYPE_AIMONSTER:
	case OTYPE_BOSSBULLET:
		// Monster、Block、BossBullet消除
		GameObjDelete(pInstOther);
		break;
	default:
		break;
	}

	return OK;
}

Status PlayerGetHurt(int hurt)
{
	PlayerHP -= hurt;
	if (PlayerHP <= 0)
		PlayerDead();
	else
	{
		isProtected = 1;
	}
	return OK;
}

Status PlayerDead()
{
	GameObjDelete(pHero);
	if (Current == GS_L4)
		Next = GS_Calculate;
	else
    	Next = GS_Lose;
	return OK;
}

int PlayerHPGet()
{
	return PlayerHP;
}

int PlayerBulletCountGet()
{
	return BulletCount;
}

int PlayerClearCountGet()
{
	return ClearCount;
}

Status PlayerClearReload()
{
	ClearCount = 1;
	return OK;
}

Vector2D PlayerPosGet()
{
	return pHero->posCurr;
}
