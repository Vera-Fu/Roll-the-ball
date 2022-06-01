//=============================================================================
//
// 地面処理 [GOAL.h]
// Author : 
//
//=============================================================================
#pragma once
#include <d3dx9.h>
#include "renderer.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
struct GOAL
{
	D3DXVECTOR3		pos;		// 位置
	D3DXVECTOR3		rot;		// 向き(回転)
	D3DXVECTOR3		scl;		// 大きさ(スケール)
	bool			use;		// 表示フラグ

	int				idxShadow;	// 影の識別子

	D3DXVECTOR3     size;		// 当たり判定用サイズ

	D3DXMATRIX		mtxWorld;	// ワールドマトリックス
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitGoal(D3DXVECTOR3 startPos);
void UninitGoal(void);
void UpdateGoal(void);
void DrawGoal(void);

GOAL* GetGoal(void);


