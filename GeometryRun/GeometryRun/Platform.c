#include "Platform.h"

static float defaultPlatformScale = 1000.0f;
static Vector2D iniPosition_Platform;
static Vector2D iniVelocity_Platform;

Status PlatformLoad()
{
	// =======================
	// ƽ̨
	// =======================
	AEGfxMeshStart();
	AEGfxTriAdd(
		-1.0f, -0.05f, COLOR_DEFAULT, 0.0f, 1.0f,
		1.0f, -0.05f, COLOR_DEFAULT, 1.0f, 1.0f,
		-1.0f, 0.05f, COLOR_DEFAULT, 0.0f, 0.0f);
	AEGfxTriAdd(
		1.0f, -0.05f, COLOR_DEFAULT, 1.0f, 1.0f,
		1.0f, 0.05f, COLOR_DEFAULT, 1.0f, 0.0f,
		-1.0f, 0.05f, COLOR_DEFAULT, 0.0f, 0.0f);

	CreateGameObjBase(OTYPE_PLATFORM, AEGfxMeshEnd(), AEGfxTextureLoad("source/image/background/thePlatForm.png"), theBaseList);
	return OK;
}

Status PlatformStart()
{
	defaultPlatformScale = 1000.0f;
	iniPosition_Platform = zero;
	Vector2DSet(&iniVelocity_Platform, -180.0f, 0.0f);
	CreateGameObj(OTYPE_PLATFORM, defaultPlatformScale, iniPosition_Platform, iniVelocity_Platform, 0, theBaseList, 0, NULL);
	return OK;
}

Status PlatformUpdate(GameObj* pInst)
{
	pInst->posCurr.x += pInst->velCurr.x * frameTime;
	pInst->posCurr.y += pInst->velCurr.y * frameTime;
	if (pInst->posCurr.x <= winMinX)
		pInst->posCurr.x = 0.0f;
	return OK;
}

float PlatformHeightGet()
{
	return defaultPlatformScale / 100.0f;
}
