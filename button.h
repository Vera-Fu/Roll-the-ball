#pragma once

#include "main.h"

struct BUTTON
{
	int texNo;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 size;
};

bool CheckIsOnButton(BUTTON* button);
