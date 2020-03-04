#pragma once

#include "GameObjectManager.h"
#include "Boss2.h"

#define MaxTimers 1000
#define OFFSETTIME 0.1f

enum TimerType{
//	TTYPE_BASEOBJ,	赘余
	TTYPE_OBJ_RANDOM,
	TTYPE_OBJ,
	TTYPE_SOMEOBJ,
	TTYPE_ADDSPEED,
	TTYPE_SWITCHSCENE,
	TTYPE_BLOCK_WITHPOS,
	TTYPE_MONSTER_WITHPOS,
	TTYPE_AIMONSTER_WITHPOS,
	TTYPE_BOSS2
};

typedef struct{
	unsigned long t_Type;
	GameObjBaseList t_L;
	float t_Scale;
	int t_PropertyCount;
	Property t_Properties[MAXPROPERTIES];
}TDataObj;

typedef struct{
	float iniMinX, iniMaxX, iniMinY, iniMaxY, iniMinVx, iniMaxVx, iniMinVy, iniMaxVy, iniMinDir, iniMaxDir;
}TDataRandom;

typedef struct{
	float t_Dir;
	Vector2D t_Pos, t_Vel;
}TDataStatic;

typedef struct{
	GameObj *t_obj;
	float Offset_Vx, Offset_Vy;
}TDataChangeSpeed;

typedef struct{
	int amountToCreate;
	TDataObj TD_obj;
	TDataRandom TD_random;
}TDataCreateSomeObjRandomly;

typedef struct{
	TDataObj TD_obj;
	TDataStatic TD_static;
}TDataCreateOneObj;

typedef struct{
	TDataObj TD_obj;
	TDataRandom TD_random;
}TDataCreateOneObjRandomly;

typedef union{
	TDataCreateSomeObjRandomly TDCreateSomeObjRandomly;
	TDataCreateOneObjRandomly TDCreateOneObjRandomly;
	TDataCreateOneObj TDCreateOneObj;
	TDataChangeSpeed TDChangeSpeed;
	Vector2D iniPos;
	int nextScene;
}TimerData;
// 此处改为联合体,按类型存储所需数据

typedef struct{
	int flag;
	int type;
	float time;
	TimerData data;
}Timer;

extern float passTime;

Status SetCreateRange(Timer *pTimer, float theIniMinX, float theIniMaxX, float theIniMinY, float theIniMaxY, float theIniMinVx, float theIniMaxVx, float theIniMinVy, float theIniMaxVy, float theIniMinDir, float theIniMaxDir);

// Status SetBaseObjToCreate(Timer *pTimer, unsigned long theType, AEGfxVertexList* theMesh, AEGfxTexture* theTexture, GameObjBaseList L);
// 赘余

Status SetObjToCreate(Timer *pTimer, unsigned long theType, float scale, GameObjBaseList L, int thePropertyCount, Property* theProperties);

float GetRanFloatFromTo(float min, float max);

Status GetRandomPosVelAndDir(Vector2D* thePos, Vector2D* theVel, float *theDir, float theIniMinX, float theIniMaxX, float theIniMinY, float theIniMaxY, float theIniMinVx, float theIniMaxVx, float theIniMinVy, float theIniMaxVy, float theIniMinDir, float theIniMaxDir);

Status TimerIni(clock_t* LevelTime);

// Status CreateBaseObjAtTime(unsigned long theType, AEGfxVertexList* theMesh, AEGfxTexture* theTexture, GameObjBaseList L, float theTime);
// 赘余

Status CreateOneObjAtTime(float theTime, unsigned long theType, float scale, Vector2D Pos, Vector2D Vel, float dir, GameObjBaseList L, int thePropertyCount, Property* theProperties);

Status CreateBlockAtTimeWithPos(float theTime, Vector2D Pos);

Status CreateMonsterAtTimeWithPos(float theTime, Vector2D Pos);

Status CreateAIMonsterAtTimeWithPos(float theTime, Vector2D Pos);

Status CreateBoss2AtTime(float theTime);

Status CreateOneObjAtTimeWithRange(float theTime, unsigned long theType, float scale, GameObjBaseList L, int thePropertyCount, Property* theProperties, float theIniMinX, float theIniMaxX, float theIniMinY, float theIniMaxY, float theIniMinVx, float theIniMaxVx, float theIniMinVy, float theIniMaxVy, float theIniMinDir, float theIniMaxDir);

Status CreateSomeObjAtSameTimeWithRange(float theTime, int theAmountToCreate, unsigned long theType, float scale, GameObjBaseList L, int thePropertyCount, Property* theProperties, float theIniMinX, float theIniMaxX, float theIniMinY, float theIniMaxY, float theIniMinVx, float theIniMaxVx, float theIniMinVy, float theIniMaxVy, float theIniMinDir, float theIniMaxDir);

Status AddSpeedForObjAtTime(float theTime, GameObj* theObj, float Offset_Vx, float Offset_Vy);

Status SwithSceneAtTime(float theTime, int theScene);

Status TimerUpdate(clock_t LevelTime);

Status TimerFree();
