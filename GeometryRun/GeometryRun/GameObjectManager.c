/* Project:		GeometryRun
File Name:	GameObjectManager.c
Author:		黄嘉维
Date:
Purpose:		游戏对象管理 */

#include "GameObjectManager.h"

// 游戏对象链表
GameObjBaseList theBaseList;
Vector2D zero;
// 用于调试输出对象类型名称
char ObjTypeName[OTYPE_COUNT][20];


static Status GetpBaseNodeWithType(unsigned long theType, GameObjBaseList L, baseNode** ppBaseNode);

static Status GetpBaseNodeWithType(unsigned long theType, GameObjBaseList L, baseNode** ppBaseNode)
{
	baseNode *pBaseNode = NULL;
	for (pBaseNode = L->head->next; pBaseNode != L->tail; pBaseNode = pBaseNode->next)
		if (pBaseNode->gameobj_base.type == theType)
		{
			*ppBaseNode = pBaseNode;
			return OK;
		}
	return ERROR;
}

void SetConstants()
{
	strcpy(ObjTypeName[OTYPE_PLAYER], "TYPE_PLAYER");
	strcpy(ObjTypeName[OTYPE_PLATFORM], "TYPE_PLATFORM");
	strcpy(ObjTypeName[OTYPE_BACKGROUND], "TYPE_BACKGROUND");
	strcpy(ObjTypeName[OTYPE_PAUSE], "TYPE_PAUSE");
	strcpy(ObjTypeName[OTYPE_MONSTER], "TYPE_MONSTER");
	strcpy(ObjTypeName[OTYPE_AIMONSTER], "TYPE_AIMONSTER");
	strcpy(ObjTypeName[OTYPE_BLOCK], "TYPE_BLOCK");
	strcpy(ObjTypeName[OTYPE_BULLET], "TYPE_BULLET");
	strcpy(ObjTypeName[OTYPE_BOSSBULLET], "TYPE_BOSSBULLET");
	strcpy(ObjTypeName[OTYPE_BOSS1], "TYPE_BOSS1");
	strcpy(ObjTypeName[OTYPE_BOSS2], "TYPE_BOSS2");
	strcpy(ObjTypeName[OTYPE_UI_STATUS], "OTYPE_UI_STATUS");
	strcpy(ObjTypeName[OTYPE_UI_NUMBER_0], "OTYPE_UI_NUMBER_0");
	strcpy(ObjTypeName[OTYPE_UI_NUMBER_1], "OTYPE_UI_NUMBER_1");
	strcpy(ObjTypeName[OTYPE_UI_NUMBER_2], "OTYPE_UI_NUMBER_2");
	strcpy(ObjTypeName[OTYPE_UI_NUMBER_3], "OTYPE_UI_NUMBER_3");
	strcpy(ObjTypeName[OTYPE_UI_NUMBER_4], "OTYPE_UI_NUMBER_4");
	strcpy(ObjTypeName[OTYPE_UI_NUMBER_5], "OTYPE_UI_NUMBER_5");
	strcpy(ObjTypeName[OTYPE_UI_NUMBER_6], "OTYPE_UI_NUMBER_6");
	strcpy(ObjTypeName[OTYPE_UI_NUMBER_7], "OTYPE_UI_NUMBER_7");
	strcpy(ObjTypeName[OTYPE_UI_NUMBER_8], "OTYPE_UI_NUMBER_8");
	strcpy(ObjTypeName[OTYPE_UI_NUMBER_9], "OTYPE_UI_NUMBER_9");
	zero.x = 0, zero.y = 0;
}


Status InitialGameObjList(GameObjList *L)
{
	*L = (GameObjList)malloc(sizeof(GameObjNode));
	if (!*L)
		return ERROR;
	(*L)->head = (insNode *)malloc(sizeof(insNode));
	(*L)->tail = (insNode *)malloc(sizeof(insNode));
	AE_ASSERT_MESG((*L)->head, "Fail to malloc");
	AE_ASSERT_MESG((*L)->tail, "Fail to malloc");
	(*L)->head->next = (*L)->tail;
	(*L)->head->pre = (*L)->tail;
	(*L)->tail->next = (*L)->head;
	(*L)->tail->pre = (*L)->head;
	(*L)->count = 0;
	printf("InitialGameObjList\n");
	return OK;
}

Status InitialGameObjBaseList(GameObjBaseList *L)
{
	*L = (GameObjBaseList )malloc(sizeof(GameObjBaseNode));
	if (!*L)
		return ERROR;
	(*L)->head = (baseNode *)malloc(sizeof(baseNode));
	(*L)->tail = (baseNode *)malloc(sizeof(baseNode));
	AE_ASSERT_MESG((*L)->head, "Fail to malloc");
	AE_ASSERT_MESG((*L)->tail, "Fail to malloc");
	(*L)->head->next = (*L)->tail;
	(*L)->head->pre = (*L)->tail;
	(*L)->tail->next = (*L)->head;
	(*L)->tail->pre = (*L)->head;
	(*L)->count = 0;
	printf("InitialGameObjBaseList\n");
	return OK;
}

Status DestroyGameObjList(GameObjList *L)
{
	insNode *pt1 = (*L)->head, *pt2 = pt1;
	while (pt2 != (*L)->tail)
	{
		pt2 = pt1->next;
		free(pt1);
		pt1 = pt2;
	}
	free(pt2);
	free(*L);
	return OK;
}

Status DestroyGameObjBaseList(GameObjBaseList *L)
{
	baseNode *pt1 = (*L)->head, *pt2 = pt1;
	while (pt2 != (*L)->tail)
	{
		pt2 = pt1->next;
		if ((pt1 != (*L)->head) && (pt1 != (*L)->tail))
		{
			DestroyGameObjList(&(pt1->gameobj_list));
			printf("DestroyGameObjList:type: %-16s\n", ObjTypeName[pt1->gameobj_base.type]);
			// 卸载对象形状定义资源，使用函数：AEGfxMeshFree
			AEGfxMeshFree(pt1->gameobj_base.pMesh);
		}
		free(pt1);
		pt1 = pt2;
	}
	free(pt2);
	free(*L);
	printf("DestroyGameObjBaseList\n");
	return OK;
}

Status ClearGameObjList(GameObjList L)
{
	insNode *pt1 = L->head->next, *pt2 = pt1;
	while (pt2 != L->tail)
	{
		pt2 = pt1->next;
		free(pt1);
		pt1 = pt2;
	}
	L->head->next = L->tail;
	L->count = 0;
	return OK;
}

Status ClearGameObjBaseList(GameObjBaseList L)
{
	baseNode *pt1 = L->head->next, *pt2 = pt1;
	while (pt2 != L->tail)
	{
		pt2 = pt1->next;
		if ((pt1 != L->head) && (pt1 != L->tail))
			DestroyGameObjList(&(pt1->gameobj_list));
		free(pt1);
		pt1 = pt2;
	}
	L->head->next = L->tail;
	L->count = 0;
	return OK;
}

Status ListIsEmpty(GameObjList L)
{
	if (L->head->next == L->tail)
		return TRUE;
	else
		return FALSE;
}

Status BaseListIsEmpty(GameObjBaseList L)
{
	if (L->head->next == L->tail)
		return TRUE;
	else
		return FALSE;
}

Status GameObjDelete(GameObj* theGameObj)
{
	int i;
	if (theGameObj->flag == FLAG_INACTIVE)
		printf("Warn: trying to delete an inactive gameobj.\n");
	theGameObj->flag = FLAG_INACTIVE;
	printf("DeleteGameObj:type: %-16s scale:%.2f pos: (%.1f, %.1f) vel: (%.1f, %.1f) dir: %.1f\n", ObjTypeName[theGameObj->pObject->type], theGameObj->scale, theGameObj->posCurr.x, theGameObj->posCurr.y, theGameObj->velCurr.x, theGameObj->velCurr.y, theGameObj->dirCurr);
	if (theGameObj->propertyCount)
	for (i = 0; i < theGameObj->propertyCount; i++)
		printf("Property %-10s: %d", theGameObj->properties[i].name, theGameObj->properties[i].value);
	return OK;
}

//遍历函数，可能无用
Status ListTraverse(GameObjList * L, Status(*Visit)(insNode* pinsNode))
{
	insNode *pt;
	for (pt = (*L)->head->next; pt != (*L)->tail; pt = pt->next)
		if (pt->gameobj.flag == FLAG_ACTIVE)
			Visit(pt);

	return OK;
}

//遍历函数，可能无用
Status BaseListTraverse(Status(*Visit)(insNode* pinsNode))
{
	baseNode *pt;
	for (pt = theBaseList->head->next; pt != theBaseList->tail; pt = pt->next)
		ListTraverse(&pt->gameobj_list, Visit);
	return OK;
}

//static Status Visit_SearchInactiveObj(insNode** ppInsNode, int *pflag);

//创建新实例对象
GameObj* CreateGameObj(unsigned long theType, float scale, Vector2D Pos, Vector2D Vel, float dir, GameObjBaseList L, int thePropertyCount, Property* theProperties)
{
	baseNode *pBaseNode;
	GetpBaseNodeWithType(theType, L, &pBaseNode);

	insNode *pt1, *pt2, *pInstNode = NULL;
	int flag = 0, i;

	// 找非活动对象的位置
	for (pt1 = pBaseNode->gameobj_list->head->next; pt1 != pBaseNode->gameobj_list->tail; pt1 = pt1->next)
	{
		if (pt1->gameobj.flag == FLAG_INACTIVE)
		{
			flag = 1;
			break;
		}
	}
	if (flag)
		pInstNode = pt1;
	else
	{
		pt1 = pBaseNode->gameobj_list->head;
		pInstNode = (insNode *)malloc(sizeof(insNode));
		AE_ASSERT_MESG(pInstNode, "Fail to malloc");
		pt2 = pt1->next;
		pt1->next = pInstNode;
		pInstNode->next = pt2;
		pInstNode->pre = pt1;
		pt2->pre = pInstNode;
	}
	pInstNode->gameobj.pObject = &(pBaseNode->gameobj_base);
	pInstNode->gameobj.flag = FLAG_ACTIVE;
	pInstNode->gameobj.scale = scale;
	pInstNode->gameobj.posCurr = Pos;
	pInstNode->gameobj.velCurr = Vel;
	pInstNode->gameobj.dirCurr = dir;
	pInstNode->gameobj.propertyCount = thePropertyCount;
	for (i = 0; i < thePropertyCount; i++)
		pInstNode->gameobj.properties[i] = theProperties[i];
	pBaseNode->gameobj_list->count++;
	printf("CreateGameObj:type: %-16s scale: %.2f Pos: (%.1f, %.1f) Vel: (%.1f, %.1f) dir: %.1f\n", ObjTypeName[theType], scale, Pos.x, Pos.y, Vel.x, Vel.y, dir);
	if (thePropertyCount != 0)
	for (i = 0; i < thePropertyCount; i++)
		printf("Property %s: %d", theProperties[i].name, theProperties[i].value);
	// 返回新创建的对象实例
	return &(pInstNode->gameobj);
}

//创建新基类
Status CreateGameObjBase(unsigned long theType, AEGfxVertexList* theMesh, AEGfxTexture* theTexture, GameObjBaseList L)
{
	baseNode *pBaseNode = (baseNode *)malloc(sizeof(baseNode));
	baseNode *pt1 = L->head, *pt2 = pt1->next;
	AE_ASSERT_MESG(pBaseNode, "Fail to malloc");

	pt1->next = pBaseNode;
	pBaseNode->pre = pt1;
	pBaseNode->next = pt2;
	pt2->pre = pBaseNode;
	InitialGameObjList(&(pBaseNode->gameobj_list));

	pBaseNode->gameobj_base.type = theType;
	pBaseNode->gameobj_base.pMesh = theMesh;
	pBaseNode->gameobj_base.pTex = theTexture;
	L->count++;
	printf("CreateGameObjBase:type: %-16s\n", ObjTypeName[theType]);
	return OK;
}

Status SetProperty(Property* theProperty, char* theName, int theValue)
{
	strcpy((*theProperty).name, theName);
	(*theProperty).value = theValue;
	return OK;
}

Status SetObjSpeed(GameObj* theObj, Vector2D theVel)
{
	theObj->velCurr = theVel;
	return OK;
}

Status AddObjSpeed(GameObj* theObj, Vector2D theVel)
{
	theObj->velCurr.x += theVel.x;
	theObj->velCurr.y += theVel.y;
	return OK;
}
