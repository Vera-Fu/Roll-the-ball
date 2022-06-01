//=============================================================================
//
// 地面処理 [DIEAREA.h]
// Author : 
//
//=============================================================================
#pragma once
#include <d3dx9.h>
#include "renderer.h"

#define DIEAREA_MAX (50)

//*****************************************************************************
// マクロ定義
//*****************************************************************************
struct DIEAREA
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
HRESULT InitDiearea(void);
void UninitDiearea(void);
void UpdateDiearea(void);
void DrawDiearea(void);

void SetDiearea(D3DXVECTOR3 pos);
DIEAREA* GetDiearea(void);

void LevelDiearea(void);
