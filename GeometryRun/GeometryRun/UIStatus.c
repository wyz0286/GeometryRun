#include "UIStatus.h"

float defaultUIStatusScale, defaultUINumber;	// ³ß´ç

static GameObj *pUINumber_HP, *pUINumber_Bullet, *pUINumber_Clear, *pUINumber_Stage[2];

static Vector2D UIStatusPos;
static Vector2D UINumberPos_Level_HP, UINumberPos_Level_Bullet,UINumberPos_Level_Clear;
static Vector2D UINumberPos_Unlimited_HP, UINumberPos_Unlimited_Bullet, UINumberPos_Unlimited_Stage[2],UINumberPos_Unlimited_Clear;

static float iniY, HP_Level_iniX, Bullet_Level_iniX, offX, Clear_Level_iniX;
static float HP_Unlimited_iniX, Bullet_Unlimited_iniX, Stage_Unlimited_iniX, Clear_Unlimited_iniX;
static int UIStage[SIZE_STAGE];

Status UIStatusLoad()
{
	// ========================
	// UIStatus
	// ========================
	AEGfxMeshStart();
	AEGfxTriAdd(
		-1.0f, -0.08f, COLOR_DEFAULT, 0.0f, 1.0f,
		1.0f, -0.08f, COLOR_DEFAULT, 1.0f, 1.0f,
		-1.0f, 0.08f, COLOR_DEFAULT, 0.0f, 0.0f);
	AEGfxTriAdd(
		1.0f, -0.08f, COLOR_DEFAULT, 1.0f, 1.0f,
		1.0f, 0.08f, COLOR_DEFAULT, 1.0f, 0.0f,
		-1.0f, 0.08f, COLOR_DEFAULT, 0.0f, 0.0f);
	if (Current == GS_L4)
		CreateGameObjBase(OTYPE_UI_STATUS, AEGfxMeshEnd(), AEGfxTextureLoad("source/image/background/status_unlimited.png"), theBaseList);
	else
		CreateGameObjBase(OTYPE_UI_STATUS, AEGfxMeshEnd(), AEGfxTextureLoad("source/image/background/status_level.png"), theBaseList);
	AEGfxMeshStart();
	AEGfxTriAdd(
		-1.0f, -1.0f, COLOR_DEFAULT, 0.0f, 1.0f,
		1.0f, -1.0f, COLOR_DEFAULT, 1.0f, 1.0f,
		-1.0f, 1.0f, COLOR_DEFAULT, 0.0f, 0.0f);
	AEGfxTriAdd(
		1.0f, -1.0f, COLOR_DEFAULT, 1.0f, 1.0f,
		1.0f, 1.0f, COLOR_DEFAULT, 1.0f, 0.0f,
		-1.0f, 1.0f, COLOR_DEFAULT, 0.0f, 0.0f);
	CreateGameObjBase(OTYPE_UI_NUMBER_0, AEGfxMeshEnd(), AEGfxTextureLoad("source/image/number/number0.png"), theBaseList);
	AEGfxMeshStart();
	AEGfxTriAdd(
		-1.0f, -1.0f, COLOR_DEFAULT, 0.0f, 1.0f,
		1.0f, -1.0f, COLOR_DEFAULT, 1.0f, 1.0f,
		-1.0f, 1.0f, COLOR_DEFAULT, 0.0f, 0.0f);
	AEGfxTriAdd(
		1.0f, -1.0f, COLOR_DEFAULT, 1.0f, 1.0f,
		1.0f, 1.0f, COLOR_DEFAULT, 1.0f, 0.0f,
		-1.0f, 1.0f, COLOR_DEFAULT, 0.0f, 0.0f);
	CreateGameObjBase(OTYPE_UI_NUMBER_1, AEGfxMeshEnd(), AEGfxTextureLoad("source/image/number/number1.png"), theBaseList);
	AEGfxMeshStart();
	AEGfxTriAdd(
		-1.0f, -1.0f, COLOR_DEFAULT, 0.0f, 1.0f,
		1.0f, -1.0f, COLOR_DEFAULT, 1.0f, 1.0f,
		-1.0f, 1.0f, COLOR_DEFAULT, 0.0f, 0.0f);
	AEGfxTriAdd(
		1.0f, -1.0f, COLOR_DEFAULT, 1.0f, 1.0f,
		1.0f, 1.0f, COLOR_DEFAULT, 1.0f, 0.0f,
		-1.0f, 1.0f, COLOR_DEFAULT, 0.0f, 0.0f);
	CreateGameObjBase(OTYPE_UI_NUMBER_2, AEGfxMeshEnd(), AEGfxTextureLoad("source/image/number/number2.png"), theBaseList);
	AEGfxMeshStart();
	AEGfxTriAdd(
		-1.0f, -1.0f, COLOR_DEFAULT, 0.0f, 1.0f,
		1.0f, -1.0f, COLOR_DEFAULT, 1.0f, 1.0f,
		-1.0f, 1.0f, COLOR_DEFAULT, 0.0f, 0.0f);
	AEGfxTriAdd(
		1.0f, -1.0f, COLOR_DEFAULT, 1.0f, 1.0f,
		1.0f, 1.0f, COLOR_DEFAULT, 1.0f, 0.0f,
		-1.0f, 1.0f, COLOR_DEFAULT, 0.0f, 0.0f);
	CreateGameObjBase(OTYPE_UI_NUMBER_3, AEGfxMeshEnd(), AEGfxTextureLoad("source/image/number/number3.png"), theBaseList);
	AEGfxMeshStart();
	AEGfxTriAdd(
		-1.0f, -1.0f, COLOR_DEFAULT, 0.0f, 1.0f,
		1.0f, -1.0f, COLOR_DEFAULT, 1.0f, 1.0f,
		-1.0f, 1.0f, COLOR_DEFAULT, 0.0f, 0.0f);
	AEGfxTriAdd(
		1.0f, -1.0f, COLOR_DEFAULT, 1.0f, 1.0f,
		1.0f, 1.0f, COLOR_DEFAULT, 1.0f, 0.0f,
		-1.0f, 1.0f, COLOR_DEFAULT, 0.0f, 0.0f);
	CreateGameObjBase(OTYPE_UI_NUMBER_4, AEGfxMeshEnd(), AEGfxTextureLoad("source/image/number/number4.png"), theBaseList);
	AEGfxMeshStart();
	AEGfxTriAdd(
		-1.0f, -1.0f, COLOR_DEFAULT, 0.0f, 1.0f,
		1.0f, -1.0f, COLOR_DEFAULT, 1.0f, 1.0f,
		-1.0f, 1.0f, COLOR_DEFAULT, 0.0f, 0.0f);
	AEGfxTriAdd(
		1.0f, -1.0f, COLOR_DEFAULT, 1.0f, 1.0f,
		1.0f, 1.0f, COLOR_DEFAULT, 1.0f, 0.0f,
		-1.0f, 1.0f, COLOR_DEFAULT, 0.0f, 0.0f);
	CreateGameObjBase(OTYPE_UI_NUMBER_5, AEGfxMeshEnd(), AEGfxTextureLoad("source/image/number/number5.png"), theBaseList);
	AEGfxMeshStart();
	AEGfxTriAdd(
		-1.0f, -1.0f, COLOR_DEFAULT, 0.0f, 1.0f,
		1.0f, -1.0f, COLOR_DEFAULT, 1.0f, 1.0f,
		-1.0f, 1.0f, COLOR_DEFAULT, 0.0f, 0.0f);
	AEGfxTriAdd(
		1.0f, -1.0f, COLOR_DEFAULT, 1.0f, 1.0f,
		1.0f, 1.0f, COLOR_DEFAULT, 1.0f, 0.0f,
		-1.0f, 1.0f, COLOR_DEFAULT, 0.0f, 0.0f);
	CreateGameObjBase(OTYPE_UI_NUMBER_6, AEGfxMeshEnd(), AEGfxTextureLoad("source/image/number/number6.png"), theBaseList);
	AEGfxMeshStart();
	AEGfxTriAdd(
		-1.0f, -1.0f, COLOR_DEFAULT, 0.0f, 1.0f,
		1.0f, -1.0f, COLOR_DEFAULT, 1.0f, 1.0f,
		-1.0f, 1.0f, COLOR_DEFAULT, 0.0f, 0.0f);
	AEGfxTriAdd(
		1.0f, -1.0f, COLOR_DEFAULT, 1.0f, 1.0f,
		1.0f, 1.0f, COLOR_DEFAULT, 1.0f, 0.0f,
		-1.0f, 1.0f, COLOR_DEFAULT, 0.0f, 0.0f);
	CreateGameObjBase(OTYPE_UI_NUMBER_7, AEGfxMeshEnd(), AEGfxTextureLoad("source/image/number/number7.png"), theBaseList);
	AEGfxMeshStart();
	AEGfxTriAdd(
		-1.0f, -1.0f, COLOR_DEFAULT, 0.0f, 1.0f,
		1.0f, -1.0f, COLOR_DEFAULT, 1.0f, 1.0f,
		-1.0f, 1.0f, COLOR_DEFAULT, 0.0f, 0.0f);
	AEGfxTriAdd(
		1.0f, -1.0f, COLOR_DEFAULT, 1.0f, 1.0f,
		1.0f, 1.0f, COLOR_DEFAULT, 1.0f, 0.0f,
		-1.0f, 1.0f, COLOR_DEFAULT, 0.0f, 0.0f);
	CreateGameObjBase(OTYPE_UI_NUMBER_8, AEGfxMeshEnd(), AEGfxTextureLoad("source/image/number/number8.png"), theBaseList);
	AEGfxMeshStart();
	AEGfxTriAdd(
		-1.0f, -1.0f, COLOR_DEFAULT, 0.0f, 1.0f,
		1.0f, -1.0f, COLOR_DEFAULT, 1.0f, 1.0f,
		-1.0f, 1.0f, COLOR_DEFAULT, 0.0f, 0.0f);
	AEGfxTriAdd(
		1.0f, -1.0f, COLOR_DEFAULT, 1.0f, 1.0f,
		1.0f, 1.0f, COLOR_DEFAULT, 1.0f, 0.0f,
		-1.0f, 1.0f, COLOR_DEFAULT, 0.0f, 0.0f);
	CreateGameObjBase(OTYPE_UI_NUMBER_9, AEGfxMeshEnd(), AEGfxTextureLoad("source/image/number/number9.png"), theBaseList);

	return OK;
}

Status UIStatusStart()
{
	int i = 0;
	defaultUIStatusScale =400.0f, defaultUINumber = 30.0f;
	iniY = -250.0f, HP_Level_iniX = -280.0f, Bullet_Level_iniX = -25.0f, offX = 40.0f,Clear_Level_iniX=250.0f;
	HP_Unlimited_iniX = -280.0f, Bullet_Unlimited_iniX = -100.0f, Stage_Unlimited_iniX = 280.0f,Clear_Unlimited_iniX=100.0f;
	memset(UIStage, 0, sizeof(int) * SIZE_STAGE);
	Vector2DSet(&UIStatusPos, 0.0f, iniY);
	Vector2DSet(&UINumberPos_Level_HP, HP_Level_iniX, iniY);
	Vector2DSet(&UINumberPos_Level_Bullet, Bullet_Level_iniX, iniY);
	Vector2DSet(&UINumberPos_Level_Clear, Clear_Level_iniX, iniY);
	Vector2DSet(&UINumberPos_Unlimited_HP, HP_Unlimited_iniX, iniY);
	Vector2DSet(&UINumberPos_Unlimited_Bullet, Bullet_Unlimited_iniX, iniY);
	Vector2DSet(&UINumberPos_Unlimited_Clear, Clear_Unlimited_iniX, iniY);
	for (i = 0; i < SIZE_STAGE; i++)
		Vector2DSet(&UINumberPos_Unlimited_Stage[i], Stage_Unlimited_iniX + offX * i, iniY);
	CreateGameObj(OTYPE_UI_STATUS, defaultUIStatusScale, UIStatusPos, zero, 0, theBaseList, 0, NULL);
	if (Current == GS_L4)
	{
		pUINumber_HP = CreateGameObj(OTYPE_UI_NUMBER_0, defaultUINumber, UINumberPos_Unlimited_HP, zero, 0, theBaseList, 0, NULL);
		pUINumber_Bullet = CreateGameObj(OTYPE_UI_NUMBER_0, defaultUINumber, UINumberPos_Unlimited_Bullet, zero, 0, theBaseList, 0, NULL);
		pUINumber_Clear = CreateGameObj(OTYPE_UI_NUMBER_1, defaultUINumber, UINumberPos_Unlimited_Clear, zero, 0, theBaseList, 0, NULL);
		for (i = 0; i < SIZE_STAGE; i++)
			pUINumber_Stage[i] = CreateGameObj(OTYPE_UI_NUMBER_0, defaultUINumber, UINumberPos_Unlimited_Stage[i], zero, 0, theBaseList, 0, NULL);
	}
	else
	{
		pUINumber_HP = CreateGameObj(OTYPE_UI_NUMBER_0, defaultUINumber, UINumberPos_Level_HP, zero, 0, theBaseList, 0, NULL);
		pUINumber_Bullet = CreateGameObj(OTYPE_UI_NUMBER_0, defaultUINumber, UINumberPos_Level_Bullet, zero, 0, theBaseList, 0, NULL);
		pUINumber_Clear = CreateGameObj(OTYPE_UI_NUMBER_1, defaultUINumber, UINumberPos_Level_Clear, zero, 0, theBaseList, 0, NULL);
	}

	return OK;
}

Status UIStatusUpdate()
{
	int i;
	int CurPlayerHP = PlayerHPGet();
	int CurPlayerCountBullet = PlayerBulletCountGet();
	int CurPlayerCountClear = PlayerClearCountGet();

	if (Current != GS_L4)
	{

		if (CurPlayerHP != pUINumber_HP->pObject->type - OTYPE_UI_NUMBER_0)
		{
			GameObjDelete(pUINumber_HP);
			pUINumber_HP = CreateGameObj(OTYPE_UI_NUMBER_0 + CurPlayerHP, defaultUINumber, UINumberPos_Level_HP, zero, 0, theBaseList, 0, NULL);
		}
		if (CurPlayerCountBullet != pUINumber_Bullet->pObject->type - OTYPE_UI_NUMBER_0)
		{
			GameObjDelete(pUINumber_Bullet);
			pUINumber_Bullet = CreateGameObj(OTYPE_UI_NUMBER_0 + CurPlayerCountBullet, defaultUINumber, UINumberPos_Level_Bullet, zero, 0, theBaseList, 0, NULL);
		}
		if (CurPlayerCountClear != pUINumber_Clear->pObject->type - OTYPE_UI_NUMBER_0)
		{
			GameObjDelete(pUINumber_Clear);
			pUINumber_Clear = CreateGameObj(OTYPE_UI_NUMBER_0 + CurPlayerCountClear, defaultUINumber, UINumberPos_Level_Clear, zero, 0, theBaseList, 0, NULL);
		}
		
	}
	else
	{
		if (CurPlayerHP != pUINumber_HP->pObject->type - OTYPE_UI_NUMBER_0)
		{
			GameObjDelete(pUINumber_HP);
			pUINumber_HP = CreateGameObj(OTYPE_UI_NUMBER_0 + CurPlayerHP, defaultUINumber, UINumberPos_Unlimited_HP, zero, 0, theBaseList, 0, NULL);
		}
		if (CurPlayerCountBullet != pUINumber_Bullet->pObject->type - OTYPE_UI_NUMBER_0)
		{
			GameObjDelete(pUINumber_Bullet);
			pUINumber_Bullet = CreateGameObj(OTYPE_UI_NUMBER_0 + CurPlayerCountBullet, defaultUINumber, UINumberPos_Unlimited_Bullet, zero, 0, theBaseList, 0, NULL);
		}
		if (CurPlayerCountClear != pUINumber_Clear->pObject->type - OTYPE_UI_NUMBER_0)
		{
			GameObjDelete(pUINumber_Clear);
			pUINumber_Clear = CreateGameObj(OTYPE_UI_NUMBER_0 + CurPlayerCountClear, defaultUINumber, UINumberPos_Unlimited_Clear, zero, 0, theBaseList, 0, NULL);
		}

		UIStage[0] = stage / 10 % 10;
		UIStage[1] = stage % 10;

		for (i = 0; i < SIZE_STAGE; i++)
			if (UIStage[i] != pUINumber_Stage[i]->pObject->type - OTYPE_UI_NUMBER_0)
			{
				GameObjDelete(pUINumber_Stage[i]);
				pUINumber_Stage[i] = CreateGameObj(OTYPE_UI_NUMBER_0 + UIStage[i], defaultUINumber, UINumberPos_Unlimited_Stage[i], zero, 0, theBaseList, 0, NULL);
			}
	}

	return OK;
}

float UIStatusScaleGet()
{
	return defaultUIStatusScale;
}
