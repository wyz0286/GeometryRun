/**
 * Project:		GeometryRun
 * File Name:	SoundSystem.h
 * Author:		wyz
 * Date:        2017-06-08
 * Purpose:		add background music
 */


#pragma once
#include "fmod.h"
#include <Windows.h>

enum SOUND_LIST
{
	SOUND_BUTTON_CLICK = 0,
	SOUND_1,
	SOUND_2,
	SOUND_3,
	SOUND_4,
	SOUND_Win,
	SOUND_Lose,
	SOUND_Pass,
	SOUND_SPLASH,
	SOUND_SPLASH_DROP,
	SOUND_GUN,
	SOUND_BUTTON_HOVER,
	SOUND_MAINMENU_MUSIC,
	SOUND_PLACING_BARRICADE,
	SOUND_PLACING_SPIKE,
	SOUND_PLACING_ERROR,
	SOUND_PLACING_DELETE,
	SOUND_GAME_MUSIC,
	SOUND_END
};

FMOD_RESULT  Result;
FMOD_SYSTEM  *System;
FMOD_SOUND   *Sound[SOUND_END];
FMOD_CHANNEL *Channel[SOUND_END];
FMOD_BOOL    Playing[SOUND_END];
FMOD_BOOL    Paused[SOUND_END];
float        Volume[SOUND_END];

void SoundSystemLoad(void);
int SoundAdd(const char* filePath, const int loopStyle, const unsigned int soundList);
void SoundPlay(const unsigned int soundList);
void SoundPausePlay(const unsigned int soundList);
void SoundStop(const unsigned int soundList);
int SoundIsPlaying(const unsigned int soundList);
void SetVolume(const unsigned int soundList, float volume);
float GetVolume(const unsigned int soundList);
void SoundSystemExit(void);
void SoundUpdate(void);
