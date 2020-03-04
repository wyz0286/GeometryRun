#include "KeyAndObjUpdate.h"

// ��ײ��������󣬷������ʱʹ��
GameObj *pInstForCollisionDetect;

float winMaxX, winMaxY, winMinX, winMinY;

// ======================
// ֡ʱ�䣺Unity�е�dt
// ======================
float frameTime;

Status GetWinMaxMinXY()
{
	// ==========================================================================================
	// ��ȡ���������ߵ����꣬�����ڷ����ƶ������ţ�����ֵ�ᷢ���仯
	// ==========================================================================================
	winMaxX = AEGfxGetWinMaxX();
	winMaxY = AEGfxGetWinMaxY();
	winMinX = AEGfxGetWinMinX();
	winMinY = AEGfxGetWinMinY();
	return OK;
}

Status KeyUpdate()
{
	// ״̬�л�
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
			// ��¼��ͣ��ʼʱ��
			pauseStartTime = clock();
		else
		{
			// ��¼��ͣ����ʱ��
			pauseEndTime = clock();
			endPause = TRUE;
		}
		return FLAG_IMPORTANTKEY;
	}

	// ���沥�����/�ո�� ����Level1
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

//���¶���
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

//������ײ���
static Status Visit_CollisionDetectAnother(insNode* pinsNode)
{
	GameObj* pInstOther = &(pinsNode->gameobj);
	// �����ǻ���������������
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
	// ������ǻ����
	if (pInstForCollisionDetect->flag == FLAG_INACTIVE)
		return OK;

	// Player �� background / block ����ײ���
	BaseListTraverse(Visit_CollisionDetectAnother);
	return OK;
}
 
Status Visit_Matrix2DCount(insNode* pinsNode)
{
	GameObj* pInst = &(pinsNode->gameobj);
	Matrix2D		 trans, rot, scale;

	// ������ǻ����
	if ((pInst->flag & FLAG_ACTIVE) == 0)
		return OK;

	// ���ž���
	if (pInst->pObject->type == OTYPE_PLAYER)
		Matrix2DScale(&scale, pInst->scale, pInst->scale * pInst->properties->value);
	else
		Matrix2DScale(&scale, pInst->scale, pInst->scale);
	// ��ת����
	Matrix2DRotDeg(&rot, pInst->dirCurr);
	// ƽ�ƾ���
	Matrix2DTranslate(&trans, pInst->posCurr.x, pInst->posCurr.y);
	// ����ȷ��˳����������3�������γ�2ά�任����
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

	// �����ǻ����
	if (pInst->flag == FLAG_INACTIVE)
		return OK;
	// ����һ��һ����Ч��
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
	// ��������
	AEGfxTextureSet(pInst->pObject->pTex, 0, 0);
	// ���ö����2D�任����ʹ�ú�����AEGfxSetTransform
	AEGfxSetTransform(pInst->transform.m);
	// ���Ƶ�ǰ����ʹ�ú�����AEGfxMeshDraw
	AEGfxMeshDraw(pInst->pObject->pMesh, AE_GFX_MDM_TRIANGLES);
	return OK;
}
