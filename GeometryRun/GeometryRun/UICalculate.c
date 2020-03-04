#include "UICalculate.h"

float defaultUINumber;	// ³ß´ç

static GameObj *pCalculate_Stage[2];

static Vector2D UICalculate_Stage[2];

static float iniY;
static float UICalculate_Stage_iniX,offX;
static int UIStage[SIZE_STAGE];

Status UICalculateLoad()
{
	// ========================
	// UICalculateNumber
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

Status UICalculateStart()
{
	int i = 0;
	defaultUINumber = 80.0f;
	iniY = 0.0f, UICalculate_Stage_iniX = -50.0f,offX=100.0f;
	memset(UIStage, 0, sizeof(int) * SIZE_STAGE);
	for (i = 0; i < SIZE_STAGE; i++)
		Vector2DSet(&UICalculate_Stage[i], UICalculate_Stage_iniX+ offX * i, iniY);
    for (i = 0; i < SIZE_STAGE; i++)
		pCalculate_Stage[i] = CreateGameObj(OTYPE_UI_NUMBER_0, defaultUINumber, UICalculate_Stage[i], zero, 0, theBaseList, 0, NULL);


	return OK;
}

Status UICalculateUpdate()
{
	int i;
	UIStage[0] = stage / 10 % 10;
	UIStage[1] = stage % 10;

	for (i = 0; i < SIZE_STAGE; i++)
		if (UIStage[i] != pCalculate_Stage[i]->pObject->type - OTYPE_UI_NUMBER_0)
		{
			GameObjDelete(pCalculate_Stage[i]);
			pCalculate_Stage[i] = CreateGameObj(OTYPE_UI_NUMBER_0 + UIStage[i], defaultUINumber, UICalculate_Stage[i], zero, 0, theBaseList, 0, NULL);
		}
	return OK;
}




