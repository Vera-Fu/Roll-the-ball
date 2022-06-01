//=============================================================================
//
// 地面処理 [enemyfollow.h]
// Author : 
//
//=============================================================================
#pragma once

#include <d3dx9.h>
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ENEMYFOLLOW_MAX 10

struct ENEMYFOLLOW
{
	D3DXVECTOR3		pos;		// 位置
	D3DXVECTOR3		rot;		// 向き(回転)
	D3DXVECTOR3		scl;		// 大きさ(スケール)
	D3DXVECTOR3		relativePos;

	float			spd;		// 移動スピード
	bool			use;		// 表示フラグ

	int				idxShadow;	// 影の識別子

	D3DXVECTOR3     size;		// 当たり判定用サイズ

	D3DXMATRIX		mtxWorld;	// ワールドマトリックス
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEnemyfollow(void);
void UninitEnemyfollow(void);
void UpdateEnemyfollow(void);
void DrawEnemyfollow(void);

ENEMYFOLLOW* GetEnemyfollow(void);
void SetEnemyfollow(D3DXVECTOR3 pos);

void LevelEnemyfollow(void);