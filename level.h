#pragma once

#include "main.h"
#include "renderer.h"

enum LEVEL
{
	LEVEL_01,
	LEVEL_02,
	LEVEL_03,
	LEVEL_04,
	LEVEL_05,
	LEVEL_06,
	LEVEL_07,
	LEVEL_08,
	LEVEL_09,
	LEVEL_MAX
};

HRESULT InitLevel(void);
void UninitLevel(void);
void UpdateLevel(void);
void DrawLevel(void);

LEVEL GetCurrentLevel(void);
void UnlockNextLevel(LEVEL currentlevel);
void SetCurrentLevel(LEVEL level);
bool GetIsLevelFinished(LEVEL level);