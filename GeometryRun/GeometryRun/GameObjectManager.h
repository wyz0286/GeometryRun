/* Project:		GeometryRun
File Name:	GameObjectManager.h
Author:		黄嘉维
Date:
Purpose:		游戏对象管理 */
#pragma once

#define OK 1
#define FLAG_ACTIVE 1
#define FLAG_INACTIVE 0
#define MAXPROPERTIES 5
#define COLOR_DEFAULT 0xFFFFFFFF

#include <stdio.h>
#include "GameStateList.h"
#include "System.h"
#include "AEEngine.h"
#include "Vector2D.h"
#include "Matrix2D.h"
#include "Math2D.h"
#include <time.h>

typedef int Status;

enum objType
{
	OTYPE_PLAYER = 0,
	OTYPE_PLATFORM,
	OTYPE_BACKGROUND,
	OTYPE_PAUSE,
	OTYPE_MONSTER,
	OTYPE_AIMONSTER,
	OTYPE_BLOCK,
	OTYPE_BULLET,
	OTYPE_BOSSBULLET,
	OTYPE_BOSS1,
	OTYPE_BOSS2,
	OTYPE_UI_STATUS,
	OTYPE_UI_NUMBER_0,
	OTYPE_UI_NUMBER_1,
	OTYPE_UI_NUMBER_2,
	OTYPE_UI_NUMBER_3,
	OTYPE_UI_NUMBER_4,
	OTYPE_UI_NUMBER_5,
	OTYPE_UI_NUMBER_6,
	OTYPE_UI_NUMBER_7,
	OTYPE_UI_NUMBER_8,
	OTYPE_UI_NUMBER_9,
	OTYPE_COUNT
};

enum visitType
{
	VTYPE_WITH_INSNODE = 0,
	VTYPE_WITH_INSNODE_OBJLIST,
	VTYPE_WITH_INSNODE_INSNODE,
	VTYPE_COUNT
};

// 可考虑去掉名字
typedef struct
{
	char name[10];
	int value;
}Property;

// 游戏对象基类/结构
typedef struct
{
	unsigned long		type;		// 游戏对象类型
	AEGfxVertexList*	pMesh;		// 形状
	AEGfxTexture*		pTex;		// 纹理
}GameObjBase;

// 游戏对象类/结构
typedef struct
{
	GameObjBase*		pObject;	// 指向基类（原始形状和类型）
	unsigned long		flag;		// 活动标志
	float				scale;		// 尺寸
	Vector2D			posCurr;	// 当前位置
	Vector2D			velCurr;	// 当前速度
	float				dirCurr;	// 当前方向
	Matrix2D			transform;	// 变换矩阵：每一帧都需要为每一个对象计算
	Property			properties[MAXPROPERTIES]; // 该对象的属性
	int					propertyCount;			   // 该对象属性的个数
}GameObj;

typedef struct INSNODE
{
	GameObj gameobj;
	struct INSNODE *next;
	struct INSNODE *pre;
}insNode;

typedef struct
{
	int count;
	insNode *head;
	insNode *tail;
}GameObjNode, *GameObjList;

typedef struct BASENODE
{
	GameObjBase gameobj_base;
	struct BASENODE *next;
	struct BASENODE *pre;
	GameObjList gameobj_list;
}baseNode;

typedef struct
{
	int count;
	baseNode *head;
	baseNode *tail;
}GameObjBaseNode, *GameObjBaseList;

// 游戏对象链表
extern GameObjBaseList theBaseList;
extern Vector2D zero;
// 用于调试输出对象类型名称
extern char ObjTypeName[OTYPE_COUNT][20];
void SetConstants();

Status InitialGameObjList(GameObjList *L);

Status InitialGameObjBaseList(GameObjBaseList *L);

Status DestroyGameObjList(GameObjList *L);

Status DestroyGameObjBaseList(GameObjBaseList *L);

Status ClearGameObjList(GameObjList L);

Status ClearGameObjBaseList(GameObjBaseList L);

Status ListIsEmpty(GameObjList L);

Status BaseListIsEmpty(GameObjBaseList L);

GameObj* CreateGameObj(unsigned long theType, float scale, Vector2D Pos, Vector2D Vel, float dir, GameObjBaseList L, int thePropertyCount, Property* theProperties);

Status CreateGameObjBase(unsigned long theType, AEGfxVertexList* theMesh, AEGfxTexture* theTexture, GameObjBaseList L);

Status GameObjDelete(GameObj* theGameObj);

Status ListTraverse(GameObjList * L, Status(*Visit)(insNode* pinsNode));

Status BaseListTraverse(Status(*Visit)(insNode* pinsNode));

Status SetProperty(Property* theProperty, char* name, int value);

Status SetObjSpeed(GameObj* theObj, Vector2D theVel);

Status AddObjSpeed(GameObj* theObj, Vector2D theVel);
