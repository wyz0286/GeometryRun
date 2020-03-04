#include "KeyAndObjUpdate.h"

// 碰撞检测主对象，方便遍历时使用
GameObj *pInstForCollisionDetect;

float winMaxX, winMaxY, winMinX, winMinY;

// ======================
// 帧时间：Unity中的dt
// ======================
float frameTime;

Status GetWinMaxMinXY()
{
	// ==========================================================================================
	// 获取窗口四条边的坐标，当窗口发生移动或缩放，以下值会发生变化
	// ==========================================================================================
	winMaxX = AEGfxGetWinMaxX();
	winMaxY = AEGfxGetWinMaxY();
	winMinX = AEGfxGetWinMinX();
	winMinY = AEGfxGetWinMinY();
	return OK;
}

Status KeyUpdate()
{
	// 状态切换
	if (KeyPressed[KeyESC] == TRUE)
	{
		Next = GS_Quit;
		return FLAG_IMPORTANTKEY;
	}
	if (Current == GS_Lose || Current == GS_Pass || Current == GS_Win || Current == GS_Menu)
		return OK;
	if (KeyPressed[KeyR] == TRUE)
	{
		Next = GS_Restart;
		return FLAG_IMPORTANTKEY;
	}
	if (KeyPressed[Key6] == TRUE)
	{
		Next = GS_Pass;
		return FLAG_IMPORTANTKEY;
	}
	if (KeyPressed[Key7] == TRUE)
	{
		Next = GS_Win;
		return FLAG_IMPORTANTKEY;
	}
	if (KeyPressed[Key8] == TRUE)
	{
		Next = GS_Lose;
		return FLAG_IMPORTANTKEY;
	}

	if (KeyPressed[KeyM] == TRUE)
	{
		Next = GS_Menu;
		return FLAG_IMPORTANTKEY;
	}
	if (KeyPressed[Key0] == TRUE)
	{
		Next = GS_L0;
		return FLAG_IMPORTANTKEY;
	}
	if (KeyPressed[Key1] == TRUE)
	{
		Next = GS_L1;
		return FLAG_IMPORTANTKEY;
	}
	if (KeyPressed[Key2] == TRUE)
	{
		Next = GS_L2;
		return FLAG_IMPORTANTKEY;
	}
	if (KeyPressed[Key3] == TRUE)
	{
		Next = GS_L3;
		return FLAG_IMPORTANTKEY;
	}
	if (KeyPressed[Key4] == TRUE)
	{
		Next = GS_L4;
		return FLAG_IMPORTANTKEY;
	}
	if (KeyPressed[KeyVolumeStop] == TRUE)
	{
		int sound = Current - GS_L0;
		SoundPausePlay(sound);
		return FLAG_IMPORTANTKEY;
	}
	if (KeyPressed[KeyVolumeUp] == TRUE)
	{
		int sound = Current - GS_L0;
		SetVolume(sound, GetVolume(sound) + 0.1f);
		return FLAG_IMPORTANTKEY;
	}
	if (KeyPressed[KeyVolumeDown] == TRUE)
	{
		int sound = Current - GS_L0;
		SetVolume(sound, GetVolume(sound) - 0.1f);
		return FLAG_IMPORTANTKEY;
	}
	if (KeyPressed[KeyP] == TRUE)
	{
		isPaused = !isPaused;
		if (isPaused == TRUE)
			// 记录暂停开始时间
			pauseStartTime = clock();
		else
		{
			// 记录暂停结束时间
			pauseEndTime = clock();
			endPause = TRUE;
		}
		return FLAG_IMPORTANTKEY;
	}

	// 画面播放完毕/空格键 进入Level1
	if (Current == GS_L0)
	{
		if (KeyPressed[KeySpace] == TRUE || xcurrentFrame>10)
		{
			Next = GS_L1;
			return FLAG_IMPORTANTKEY;
		}
	}

	if (Current == GS_Help)
	{
		if (KeyPressed[KeySpace] == TRUE || xcurrentFrame>5)
		{
			Next = GS_Staff;
			return FLAG_IMPORTANTKEY;
		}
	}
	return OK;
}

//更新对象
Status ObjUpdate()
{
	baseNode *pBaseNode;
	GameObjList *pL;
	frameTime = (float)AEFrameRateControllerGetFrameTime();
	for (pBaseNode = theBaseList->head->next; pBaseNode != theBaseList->tail; pBaseNode = pBaseNode->next)
	{
		pL = &(pBaseNode->gameobj_list);
		switch (pBaseNode->gameobj_base.type)
		{
			case OTYPE_PLAYER:
				ListTraverse(pL, PlayerUpdate);
				break;
			case OTYPE_BACKGROUND:
				ListTraverse(pL, BackGroundUpdate);
				break;
			case OTYPE_PLATFORM:
				ListTraverse(pL, PlatformUpdate);
				break;
			case OTYPE_MONSTER:
				ListTraverse(pL, MonsterUpdate);
				break;
			case OTYPE_AIMONSTER:
				ListTraverse(pL, AIMonsterUpdate);
				break;
			case OTYPE_BLOCK:
				ListTraverse(pL, BlockUpdate);
				break;
			case OTYPE_BULLET:
				ListTraverse(pL, BulletUpdate);
				break;
			case OTYPE_BOSSBULLET:
				ListTraverse(pL, BossBulletUpdate);
				break;
			case OTYPE_BOSS2:
				ListTraverse(pL, Boss2Update);
				break;
			default:
			break;
		}
	}
	if (Current <= GS_L4 && Current >= GS_L1)
		UIStatusUpdate();
	if (Current == GS_Calculate)
		UICalculateUpdate();
	return OK;
}

//对象碰撞检测
static Status Visit_CollisionDetectAnother(insNode* pinsNode)
{
	GameObj* pInstOther = &(pinsNode->gameobj);
	// 跳过非活动对象和主对象自身
	if (pInstOther->flag == FLAG_INACTIVE || (pInstOther->pObject->type == pInstForCollisionDetect->pObject->type))
		return OK;
	switch (pInstForCollisionDetect->pObject->type)
	{
		case OTYPE_PLAYER:
			PlayerCollision(pinsNode);
			break;
		case OTYPE_BULLET:
			BulletCollision(pinsNode);
			break;
		case OTYPE_BOSSBULLET:
			BossBulletCollision(pinsNode);
			break;
		
		default:
			break;
	}

	return OK;
}

Status Visit_CollisionDetect(insNode* pinsNode)
{
	pInstForCollisionDetect = &(pinsNode->gameobj);
	// 不处理非活动对象
	if (pInstForCollisionDetect->flag == FLAG_INACTIVE)
		return OK;

	// Player 与 background / block 的碰撞检测
	BaseListTraverse(Visit_CollisionDetectAnother);
	return OK;
}
 
Status Visit_Matrix2DCount(insNode* pinsNode)
{
	GameObj* pInst = &(pinsNode->gameobj);
	Matrix2D		 trans, rot, scale;

	// 不处理非活动对象
	if ((pInst->flag & FLAG_ACTIVE) == 0)
		return OK;

	// 缩放矩阵
	if (pInst->pObject->type == OTYPE_PLAYER)
		Matrix2DScale(&scale, pInst->scale, pInst->scale * pInst->properties->value);
	else
		Matrix2DScale(&scale, pInst->scale, pInst->scale);
	// 旋转矩阵
	Matrix2DRotDeg(&rot, pInst->dirCurr);
	// 平移矩阵
	Matrix2DTranslate(&trans, pInst->posCurr.x, pInst->posCurr.y);
	// 以正确的顺序连乘以上3个矩阵形成2维变换矩阵
	Matrix2DConcat(&(pInst->transform), &trans, &rot);
	Matrix2DConcat(&(pInst->transform), &(pInst->transform), &scale);
	return OK;
}


Status Visit_DestroyObj(insNode* pinsNode)
{
	GameObj* pInst = &(pinsNode->gameobj);
	if (pInst->flag == FLAG_ACTIVE)
		GameObjDelete(pInst);
	return OK;
}

Status Visit_DrawObj(insNode* pinsNode)
{
	GameObj* pInst = &(pinsNode->gameobj);

	// 跳过非活动对象
	if (pInst->flag == FLAG_INACTIVE)
		return OK;
	// 制造一闪一闪的效果
	if (pInst->pObject->type == OTYPE_PLAYER && isProtected)
	{
		ProtectCur += 1;
		if (ProtectCur >= MaxProtectCur)
		{
			ProtectCur = 0;
			isProtected = 0;
		}
		else if (ProtectCur % 10 <= 5)
			return OK;
	}
	// 设置纹理
	AEGfxTextureSet(pInst->pObject->pTex, 0, 0);
	// 设置对象的2D变换矩阵，使用函数：AEGfxSetTransform
	AEGfxSetTransform(pInst->transform.m);
	// 绘制当前对象，使用函数：AEGfxMeshDraw
	AEGfxMeshDraw(pInst->pObject->pMesh, AE_GFX_MDM_TRIANGLES);
	return OK;
}
