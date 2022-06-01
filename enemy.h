//=============================================================================
//
// 地面処理 [enemy.h]
// Author : 
//
//=============================================================================
#pragma once

#include <d3dx9.h>
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ENEMY_MAX 20
#define ENEMYMOVEWAY_MAX 20

enum ENEMYDIRECTION
{
	ENEMY_FRONT,
	ENEMY_BACK,
	ENEMY_LEFT,
	ENEMY_RIGHT
};

struct ENEMYMOVEWAY
{
	ENEMYDIRECTION	dir;
	int		distance;
	bool			set;
};

struct ENEMY
{
	D3DXVECTOR3		pos;		// 位置
	D3DXVECTOR3		rot;		// 向き(回転)
	D3DXVECTOR3		scl;		// 大きさ(スケール)
	ENEMYMOVEWAY	moveway[ENEMYMOVEWAY_MAX];
	int				movewayIndex;
	float			targetPos;
	bool			reach;

	float			spd;		// 移動スピード
	bool			use;		// 表示フラグ

	int				idxShadow;	// 影の識別子

	D3DXVECTOR3     size;		// 当たり判定用サイズ

	D3DXMATRIX		mtxWorld;	// ワールドマトリックス
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);

ENEMY *GetEnemy(void);
void SetEnemy(D3DXVECTOR3 pos);
void SetEnemyMoveway(int enemyIndex, ENEMYDIRECTION dir, int distance);

void LevelEnemy(void);