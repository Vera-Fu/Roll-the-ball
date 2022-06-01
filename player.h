//=============================================================================
//
// 地面処理 [player.h]
// Author : 
//
//=============================================================================
#pragma once

#include <d3dx9.h>
#include "renderer.h"

enum PLAYERORIENTATION
{
	PLAYER_UP,
	PLAYER_DOWN,
	PLAYER_LEFT,
	PLAYER_RIGHT,
	PLAYERORIENTATION_MAX
};

//*****************************************************************************
// マクロ定義
//*****************************************************************************
struct PLAYER
{
	D3DXVECTOR3		pos;		// 位置
	D3DXVECTOR3		rot;		// 向き(回転)
	D3DXVECTOR3		scl;		// 大きさ(スケール)
	float			spd;		// 移動スピード
	float			rotSpd;
	float			spdCoefficient;
	bool			use;		// 表示フラグ
	bool			isFreezing;

	int				bulletNum;

	int				idxShadow;	// 影の識別子

	D3DXVECTOR3     size;		// 当たり判定用サイズ

	D3DXMATRIX		mtxWorld;	// ワールドマトリックス
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayer(D3DXVECTOR3 startPos, int bulletNum);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

PLAYER *GetPlayer(void);
