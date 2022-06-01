#pragma once

#include "main.h"
#include "renderer.h"

HRESULT InitPause(void);
void UninitPause(void);
void UpdatePause(void);
void DrawPause(void);

bool GetIsPause(void);