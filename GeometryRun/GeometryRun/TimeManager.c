#include "TimeManager.h"

static Timer Timers[MaxTimers];
static int timerCount;

// 关卡过去的时间
float passTime;


Status TimerIni(clock_t* LevelTime)
{
	int i;
	for (i = 0; i < MaxTimers; i++)
		Timers[i].flag = FLAG_INACTIVE;
	timerCount = 0;
	srand(time(0));
	return OK;
}

static Status SetTDRandom(TDataRandom *theTD_random, float theIniMinX, float theIniMaxX, float theIniMinY, float theIniMaxY, float theIniMinVx, float theIniMaxVx, float theIniMinVy, float theIniMaxVy, float theIniMinDir, float theIniMaxDir)
{
	(*theTD_random).iniMinX = theIniMinX;
	(*theTD_random).iniMaxX = theIniMaxX;
	(*theTD_random).iniMinY = theIniMinY;
	(*theTD_random).iniMaxY = theIniMaxY;
	(*theTD_random).iniMinVx = theIniMinVx;
	(*theTD_random).iniMaxVx = theIniMaxVx;
	(*theTD_random).iniMinVy = theIniMinVy;
	(*theTD_random).iniMaxVy = theIniMaxVy;
	(*theTD_random).iniMinDir = theIniMinDir;
	(*theTD_random).iniMaxDir = theIniMaxDir;
	return OK;
}

static Status SetTDObj(TDataObj *theTD_obj, unsigned long theType, float scale, GameObjBaseList L, int thePropertyCount, Property* theProperties)
{
	int i;
	(*theTD_obj).t_Type = theType;
	(*theTD_obj).t_Scale = scale;
	(*theTD_obj).t_L = L;
	(*theTD_obj).t_PropertyCount = thePropertyCount;
	for (i = 0; i < thePropertyCount; i++)
		(*theTD_obj).t_Properties[i] = theProperties[i];
	return OK;
}

static Status SetTDStatic(TDataStatic *theTD_static, Vector2D thePos, Vector2D theVel, float theDir)
{
	(*theTD_static).t_Pos = thePos;
	(*theTD_static).t_Vel = theVel;
	(*theTD_static).t_Dir = theDir;
	return OK;
}

static float GetRanFloatFromTo(float min, float max)
{
	float f;
	int i;
	i = rand() % 1000;
	f = min + (max - min) * ((float)i / 1000.0f);
	return f;
}

static Status GetRandomPosVelAndDir(Vector2D* thePos, Vector2D* theVel, float *theDir, float theIniMinX, float theIniMaxX, float theIniMinY, float theIniMaxY, float theIniMinVx, float theIniMaxVx, float theIniMinVy, float theIniMaxVy, float theIniMinDir, float theIniMaxDir)
{
	thePos->x = GetRanFloatFromTo(theIniMinX, theIniMaxX);
	thePos->y = GetRanFloatFromTo(theIniMinY, theIniMaxY);
	theVel->x = GetRanFloatFromTo(theIniMinVx, theIniMaxVx);
	theVel->y = GetRanFloatFromTo(theIniMinVy, theIniMaxVy);
	*theDir = GetRanFloatFromTo(theIniMinDir, theIniMaxDir);
	printf("test 1 iniMaxX: %.2f\n", theIniMaxX);
	printf("test 1 iniMinx: %.2f\n", theIniMinX);
	printf("x: %.2f\n", thePos->x);
	
	return OK;
}

Status CreateOneObjAtTime(float theTime, unsigned long theType, float scale, Vector2D Pos, Vector2D Vel, float dir, GameObjBaseList L, int thePropertyCount, Property* theProperties)
{
	int i;
	for (i = 0; i < MaxTimers; i++)
	{
		if (Timers[i].flag == FLAG_INACTIVE)
		{
			timerCount++;
			Timers[i].flag = FLAG_ACTIVE;
			Timers[i].type = TTYPE_OBJ;
			Timers[i].time = theTime;
			SetTDStatic(&Timers[i].data.TDCreateOneObj.TD_static, Pos, Vel, dir);
			SetTDObj(&Timers[i].data.TDCreateOneObj.TD_obj, theType, scale, L, thePropertyCount, theProperties);
			return OK;
		}
	}
	return ERROR;
}

Status CreateBlockAtTimeWithPos(float theTime, Vector2D Pos)
{
	int i;
	for (i = 0; i < MaxTimers; i++)
	{
		if (Timers[i].flag == FLAG_INACTIVE)
		{
			timerCount++;
			Timers[i].flag = FLAG_ACTIVE;
			Timers[i].type = TTYPE_BLOCK_WITHPOS;
			Timers[i].time = theTime;
			Timers[i].data.iniPos = Pos;
			return OK;
		}
	}
	return OK;
}

Status CreateMonsterAtTimeWithPos(float theTime, Vector2D Pos)
{
	int i;
	for (i = 0; i < MaxTimers; i++)
	{
		if (Timers[i].flag == FLAG_INACTIVE)
		{
			timerCount++;
			Timers[i].flag = FLAG_ACTIVE;
			Timers[i].type = TTYPE_MONSTER_WITHPOS;
			Timers[i].time = theTime;
			Timers[i].data.iniPos = Pos;
			return OK;
		}
	}
	return OK;
}

Status CreateAIMonsterAtTimeWithPos(float theTime, Vector2D Pos)
{
	int i;
	for (i = 0; i < MaxTimers; i++)
	{
		if (Timers[i].flag == FLAG_INACTIVE)
		{
			timerCount++;
			Timers[i].flag = FLAG_ACTIVE;
			Timers[i].type = TTYPE_AIMONSTER_WITHPOS;
			Timers[i].time = theTime;
			Timers[i].data.iniPos = Pos;
			return OK;
		}
	}
	return OK;
}

Status CreateBoss2AtTime(float theTime)
{
	int i;
	for (i = 0; i < MaxTimers; i++)
	{
		if (Timers[i].flag == FLAG_INACTIVE)
		{
			timerCount++;
			Timers[i].flag = FLAG_ACTIVE;
			Timers[i].type = TTYPE_BOSS2;
			Timers[i].time = theTime;
			return OK;
		}
	}
	return OK;
}

Status CreateOneObjAtTimeWithRange(float theTime, unsigned long theType, float scale, GameObjBaseList L, int thePropertyCount, Property* theProperties, float theIniMinX, float theIniMaxX, float theIniMinY, float theIniMaxY, float theIniMinVx, float theIniMaxVx, float theIniMinVy, float theIniMaxVy, float theIniMinDir, float theIniMaxDir)
{
	int i;
	for (i = 0; i < MaxTimers; i++)
	{
		if (Timers[i].flag == FLAG_INACTIVE)
		{
			timerCount++;
			Timers[i].flag = FLAG_ACTIVE;
			Timers[i].type = TTYPE_OBJ_RANDOM;
			Timers[i].time = theTime;
			SetTDRandom(&Timers[i].data.TDCreateOneObjRandomly.TD_random, theIniMinX, theIniMaxX, theIniMinY, theIniMaxY, theIniMinVx, theIniMaxVx, theIniMinVy, theIniMaxVy, theIniMinDir, theIniMaxDir);
			SetTDObj(&Timers[i].data.TDCreateOneObjRandomly.TD_obj, theType, scale, L, thePropertyCount, theProperties);
			return OK;
		}
	}
	return ERROR;
}

Status CreateSomeObjAtSameTimeWithRange(float theTime, int theAmountToCreate, unsigned long theType, float scale, GameObjBaseList L, int thePropertyCount, Property* theProperties, float theIniMinX, float theIniMaxX, float theIniMinY, float theIniMaxY, float theIniMinVx, float theIniMaxVx, float theIniMinVy, float theIniMaxVy, float theIniMinDir, float theIniMaxDir)
{
	int i;
	for (i = 0; i < MaxTimers; i++)
	{
		if (Timers[i].flag == FLAG_INACTIVE)
		{
			timerCount++;
			Timers[i].flag = FLAG_ACTIVE;
			Timers[i].type = TTYPE_SOMEOBJ;
			Timers[i].time = theTime;
			Timers[i].data.TDCreateSomeObjRandomly.amountToCreate = theAmountToCreate;
			SetTDRandom(&Timers[i].data.TDCreateSomeObjRandomly.TD_random, theIniMinX, theIniMaxX, theIniMinY, theIniMaxY, theIniMinVx, theIniMaxVx, theIniMinVy, theIniMaxVy, theIniMinDir, theIniMaxDir);
			SetTDObj(&Timers[i].data.TDCreateSomeObjRandomly.TD_obj, theType, scale, L, thePropertyCount, theProperties);
			return OK;
		}
	}
	return ERROR;
}

Status AddSpeedForObjAtTime(float theTime, GameObj* theObj, float theOffset_Vx, float theOffset_Vy)
{
	int i;
	for (i = 0; i < MaxTimers; i++)
	{
		if (Timers[i].flag == FLAG_INACTIVE)
		{
			timerCount++;
			Timers[i].flag = FLAG_ACTIVE;
			Timers[i].type = TTYPE_ADDSPEED;
			Timers[i].time = theTime;
			Timers[i].data.TDChangeSpeed.t_obj = theObj;
			Timers[i].data.TDChangeSpeed.Offset_Vx = theOffset_Vx;
			Timers[i].data.TDChangeSpeed.Offset_Vy = theOffset_Vy;
			return OK;
		}
	}
	return ERROR;
}

Status SwithSceneAtTime(float theTime, int theScene)
{
	int i;
	for (i = 0; i < MaxTimers; i++)
	{
		if (Timers[i].flag == FLAG_INACTIVE)
		{
			timerCount++;
			Timers[i].flag = FLAG_ACTIVE;
			Timers[i].type = TTYPE_SWITCHSCENE;
			Timers[i].time = theTime;
			Timers[i].data.nextScene = theScene;
			return OK;
		}
	}
	return ERROR;
}

Status TimerUpdate(clock_t LevelTime)
{
	int i, j, dealTimers = 0;
	Vector2D iniPos, iniVel;
	float iniDir;
	TDataObj theTD_obj;
	TDataStatic theTD_static;
	TDataRandom theTD_random;
	GameObj *theObj;
	clock_t poiTime = clock();
	passTime = (poiTime - LevelTime) / 1000.0f;

	for (i = 0; i < MaxTimers && dealTimers < timerCount; i++)
	{
		if (Timers[i].flag == FLAG_INACTIVE)
			continue;
		else
		{
			dealTimers++;
			if (passTime >= Timers[i].time)
			{
				switch (Timers[i].type)
				{
					case TTYPE_OBJ:
					{
						theTD_obj = Timers[i].data.TDCreateOneObj.TD_obj;
						theTD_static = Timers[i].data.TDCreateOneObj.TD_static;
						if (theTD_obj.t_Type != OTYPE_BOSS2)
							CreateGameObj(theTD_obj.t_Type, theTD_obj.t_Scale, theTD_static.t_Pos, theTD_static.t_Vel, theTD_static.t_Dir, theTD_obj.t_L, theTD_obj.t_PropertyCount, theTD_obj.t_Properties);
						else
							pBoss2 = CreateGameObj(theTD_obj.t_Type, theTD_obj.t_Scale, theTD_static.t_Pos, theTD_static.t_Vel, theTD_static.t_Dir, theTD_obj.t_L, theTD_obj.t_PropertyCount, theTD_obj.t_Properties);
						break;
					}
					case TTYPE_OBJ_RANDOM:
					{
						theTD_obj = Timers[i].data.TDCreateOneObjRandomly.TD_obj;
						theTD_random = Timers[i].data.TDCreateOneObjRandomly.TD_random;
						GetRandomPosVelAndDir(&iniPos, &iniVel, &iniDir, theTD_random.iniMinX, theTD_random.iniMaxX, theTD_random.iniMinY, theTD_random.iniMaxY, theTD_random.iniMinVx, theTD_random.iniMaxVx, theTD_random.iniMinVy, theTD_random.iniMaxVy, theTD_random.iniMinDir, theTD_random.iniMaxDir);
					
						if (theTD_obj.t_Type != OTYPE_BOSS2)
							CreateGameObj(theTD_obj.t_Type, theTD_obj.t_Scale, theTD_static.t_Pos, theTD_static.t_Vel, theTD_static.t_Dir, theTD_obj.t_L, theTD_obj.t_PropertyCount, theTD_obj.t_Properties);
						else
							pBoss2 = CreateGameObj(theTD_obj.t_Type, theTD_obj.t_Scale, theTD_static.t_Pos, theTD_static.t_Vel, theTD_static.t_Dir, theTD_obj.t_L, theTD_obj.t_PropertyCount, theTD_obj.t_Properties);
						break;
					}
					case TTYPE_SOMEOBJ:
					{
						theTD_obj = Timers[i].data.TDCreateSomeObjRandomly.TD_obj;
						theTD_random = Timers[i].data.TDCreateSomeObjRandomly.TD_random;
						for (j = 0; j < Timers[i].data.TDCreateSomeObjRandomly.amountToCreate; j++)
						{
							GetRandomPosVelAndDir(&iniPos, &iniVel, &iniDir, theTD_random.iniMinX, theTD_random.iniMaxX, theTD_random.iniMinY, theTD_random.iniMaxY, theTD_random.iniMinVx, theTD_random.iniMaxVx, theTD_random.iniMinVy, theTD_random.iniMaxVy, theTD_random.iniMinDir, theTD_random.iniMaxDir);
							printf("test 0 iniMaxX: %.2f\n", theTD_random.iniMaxX);
							printf("max x: %.2f\n", iniPos.x);
							CreateGameObj(theTD_obj.t_Type, theTD_obj.t_Scale, iniPos, iniVel, iniDir, theTD_obj.t_L, theTD_obj.t_PropertyCount, theTD_obj.t_Properties);
						}
						break;
					}
					case TTYPE_ADDSPEED:
					{
						theObj = Timers[i].data.TDChangeSpeed.t_obj;
						if (theObj->flag == FLAG_ACTIVE)
						{
							printf("ofvx = %.1f, ofvy = %.1f\n", Timers[i].data.TDChangeSpeed.Offset_Vx, Timers[i].data.TDChangeSpeed.Offset_Vy);
							Timers[i].data.TDChangeSpeed.t_obj->velCurr.x += Timers[i].data.TDChangeSpeed.Offset_Vx;
							Timers[i].data.TDChangeSpeed.t_obj->velCurr.y += Timers[i].data.TDChangeSpeed.Offset_Vy;
						}
						break;
					}
					case TTYPE_SWITCHSCENE:
					{
						Next = Timers[i].data.nextScene;
						break;
					}
					case TTYPE_BLOCK_WITHPOS:
					{
						BlockCreateAtPos(Timers[i].data.iniPos);
						break;
					}
					case TTYPE_MONSTER_WITHPOS:
					{
						MonsterCreateAtPos(Timers[i].data.iniPos);
						break;
					}
					case TTYPE_AIMONSTER_WITHPOS:
					{
						AIMonsterCreateAtPos(Timers[i].data.iniPos);
						break;
					}
					case TTYPE_BOSS2:
					{
						pBoss2 = Boss2Create();
						break;
					}
					default:
						break;
				}
				Timers[i].flag = FLAG_INACTIVE;
			}

		}
	}
	return OK;
}

Status TimerFree()
{
	int i;
	timerCount = 0;
	for (i = 0; i < MaxTimers; i++)
		Timers[i].flag = FLAG_INACTIVE;
	return OK;
}
