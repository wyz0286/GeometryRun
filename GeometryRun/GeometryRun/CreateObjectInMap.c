/**
 * Project:		GeometryRun
 * File Name:	CreateObjectInMap.c
 * Author:		闷声发大财
 * Date:		2017-5-28
 * Purpose:		障碍物创建模型素材库
 */

#include "CreateObjectInMap.h"

float(*CreateObjInMapRamdom[CreateMethods])(float);

Status IniCreateRandomArrays()
{
	CreateObjInMapRamdom[0] = CreateObjInMap0;
	CreateObjInMapRamdom[1] = CreateObjInMap1;
	CreateObjInMapRamdom[2] = CreateObjInMap2;
	CreateObjInMapRamdom[3] = CreateObjInMap3;
	CreateObjInMapRamdom[4] = CreateObjInMap4;
	CreateObjInMapRamdom[5] = CreateObjInMap5;
	CreateObjInMapRamdom[6] = CreateObjInMap6;
	CreateObjInMapRamdom[7] = CreateObjInMap7;
	CreateObjInMapRamdom[8] = CreateObjInMap8;
	CreateObjInMapRamdom[9] = CreateObjInMap9;
	return OK;
}

/*
 * By WJ
 * 从上至下再至上依次出现小怪物
 * startTime：开始时间
 * 返回占用时间：6s
 */

float CreateObjInMap0(float startTime)
{
	int i;
	Vector2D pos[7];
	for (i = 0; i < 7; i++)
	{
		Vector2DSet(&(pos[i]), winMaxX, 245 - 70 * i);
		CreateMonsterAtTimeWithPos(startTime + 0.5f * i, pos[i]);
	}
	for (i = 0; i < 6; i++)
		CreateMonsterAtTimeWithPos(startTime + 0.5f * i + 3.5f, pos[5 - i]);
	return 6.0f;
}

/*
 * By WJ
 * 从上至下再至上依次出现障碍物
 * 占用时间：6s
 */
float CreateObjInMap1(float startTime)
{
	int i;
	Vector2D pos[7];
	for (i = 0; i < 7; i++)
	{
		Vector2DSet(&(pos[i]), winMaxX, 245 - 70 * i);
		CreateBlockAtTimeWithPos(startTime + 0.5f * i, pos[i]);
	}
	for (i = 0; i < 6; i++)
		CreateBlockAtTimeWithPos(startTime + 0.5f * i + 3.5f, pos[5 - i]);
	return 6.0f;
}

/*
 * By WYZ
 * 障碍物+小怪（混搭较复杂）
 * 占用时间2.3s
 */
float CreateObjInMap2(float startTime)
{
	float CurPlatformHeight = PlatformHeightGet();
	float CurBlockScale = BlockScaleGet();
	Vector2D pos1 = { winMaxX, CurBlockScale + 70.0f };
	Vector2D pos2 = { winMaxX, -CurBlockScale - CurPlatformHeight };
	Vector2D pos3 = { winMaxX, CurBlockScale + CurPlatformHeight };

	CreateMonsterAtTimeWithPos(startTime, pos1);
	CreateBlockAtTimeWithPos(startTime, pos2);
	CreateMonsterAtTimeWithPos(startTime + 0.5f, pos3);
	CreateBlockAtTimeWithPos(startTime + 0.5f, pos2);
	CreateBlockAtTimeWithPos(startTime + 1.1f, pos3);
	CreateMonsterAtTimeWithPos(startTime + 1.8f, pos1);
	CreateBlockAtTimeWithPos(startTime + 2.3f, pos2);
	return 2.3f;
}

/*
 * By WYZ
 * 障碍物+小怪（上、下）
 * 占用时间：0s
 */
float CreateObjInMap3(float startTime)
{
	float CurBlockScale = BlockScaleGet();
	float CurPlatformHeight = PlatformHeightGet();
	Vector2D pos1 = { winMaxX, CurBlockScale + 20.0f };
	Vector2D pos2 = { winMaxX, - CurBlockScale - CurPlatformHeight };

	CreateMonsterAtTimeWithPos(startTime, pos1);
	CreateBlockAtTimeWithPos(startTime, pos2);
	return 0.0f;
}


/*
 * By WYZ
 * 障碍物（2个叠在一起）
 * 占用时间：0s
 */
float CreateObjInMap4(float startTime)
{
	float CurBlockScale = BlockScaleGet();
	float CurPlatformHeight = PlatformHeightGet();
	Vector2D pos1 = { winMaxX, CurBlockScale + CurPlatformHeight };
	Vector2D pos2 = { winMaxX, CurBlockScale + 70.0f };
	CreateBlockAtTimeWithPos(startTime, pos1);
	CreateBlockAtTimeWithPos(startTime, pos2);
	return 0.0f;
}

/*
 * By WJ
 * 连续三个障碍物（上、下、上）
 * 占用时间：1.2s
 */
float CreateObjInMap5(float startTime)
{
	float CurBlockScale = BlockScaleGet();
	float CurPlatformHeight = PlatformHeightGet();
	Vector2D pos1 = { winMaxX, CurBlockScale + CurPlatformHeight };
	Vector2D pos2 = { winMaxX, -CurBlockScale - CurPlatformHeight };
	CreateBlockAtTimeWithPos(startTime, pos1);
	CreateBlockAtTimeWithPos(startTime + 0.6f, pos2);
	CreateBlockAtTimeWithPos(startTime + 1.2f, pos1);
	return 1.2f;
}

/*
 * By WYZ
 * 用于二段跳之后马上倒挂教学
 * 占用时间：1.0s
 */
float CreateObjInMap6(float startTime)
{
	float CurBlockScale = BlockScaleGet();
	float CurPlatformHeight = PlatformHeightGet();
	Vector2D pos1 = { winMaxX, CurBlockScale + CurPlatformHeight };
	Vector2D pos2 = { winMaxX, CurBlockScale + 70.0f };
	Vector2D pos3 = { winMaxX, -CurBlockScale - CurPlatformHeight };
	CreateBlockAtTimeWithPos(startTime, pos1);
	CreateBlockAtTimeWithPos(startTime, pos2);
	CreateBlockAtTimeWithPos(startTime, pos3);
	CreateBlockAtTimeWithPos(startTime + 1.0f, pos1);
	CreateBlockAtTimeWithPos(startTime + 1.0f, pos2);
	return 1.0f;
}

/*
 * By WJ
 * 连续四个追踪Monster
 * 占用时间：1.2s
 */
float CreateObjInMap7(float startTime)
{
	float maxX = AEGfxGetWinMaxX();
	Vector2D pos1 = { maxX, 200.0f };
	Vector2D pos2 = { maxX, -200.0f };

	CreateAIMonsterAtTimeWithPos(startTime, pos1);
	CreateAIMonsterAtTimeWithPos(startTime + 0.6f, pos2);
	CreateAIMonsterAtTimeWithPos(startTime + 1.2f, pos1);
	CreateAIMonsterAtTimeWithPos(startTime + 1.8f, pos2);
	return 1.8f;
}

/*
 * By WJ
 * 需要二段跳跃
 * 占用时间：1.2s
 */
float CreateObjInMap8(float startTime)
{
	float CurBlockScale = BlockScaleGet();
	float CurPlatformHeight = PlatformHeightGet();
	Vector2D pos1 = { winMaxX, CurBlockScale + CurPlatformHeight };
	Vector2D pos2 = { winMaxX, -CurBlockScale - CurPlatformHeight };
	Vector2D pos3 = { winMaxX, 3 * CurBlockScale + CurPlatformHeight };

	CreateBlockAtTimeWithPos(startTime, pos1);
	CreateBlockAtTimeWithPos(startTime, pos2);
	CreateBlockAtTimeWithPos(startTime + 0.5f, pos1);
	CreateBlockAtTimeWithPos(startTime + 0.5f, pos2);
	CreateBlockAtTimeWithPos(startTime + 0.5f, pos3);
	return 0.5f;
}

/*
 * By WJ
 * 有操作难度
 * 占用时间：1.8s
 */
float CreateObjInMap9(float startTime)
{
	float CurBlockScale = BlockScaleGet();
	float CurPlatformHeight = PlatformHeightGet();
	Vector2D pos1 = { winMaxX, CurBlockScale + CurPlatformHeight };
	Vector2D pos2 = { winMaxX, -CurBlockScale - CurPlatformHeight };
	Vector2D pos3 = { winMaxX, 7 * CurBlockScale + CurPlatformHeight };

	CreateBlockAtTimeWithPos(startTime, pos1);
	CreateBlockAtTimeWithPos(startTime, pos2);
	CreateBlockAtTimeWithPos(startTime, pos3);
	CreateMonsterAtTimeWithPos(startTime + 0.6f, pos3);
	CreateBlockAtTimeWithPos(startTime + 0.6f, pos1);
	CreateBlockAtTimeWithPos(startTime + 1.2f, pos1);
	CreateBlockAtTimeWithPos(startTime + 1.2f, pos2);
	CreateBlockAtTimeWithPos(startTime + 1.2f, pos3);
	CreateMonsterAtTimeWithPos(startTime + 1.8f, pos3);
	CreateBlockAtTimeWithPos(startTime + 1.8f, pos2);
	return 1.8f;
}


/*
 * By HJW
 * 生成BOSS
 */
float CreateBossInMap_Level2(float startTime)
{
	CreateBoss2AtTime(startTime);
	return 0.0f;
}
