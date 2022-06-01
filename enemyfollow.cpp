//=============================================================================
//
// ポリゴン表示処理 [enemyfollow.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "enemyfollow.h"
#include "texture.h"
#include "model.h"
#include "light.h"
#include "player.h"
#include "shadow.h"
#include "level.h"
#include "fade.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)			// 回転量


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static DX11_MODEL		g_Model;			// モデル読み込み
static ENEMYFOLLOW		g_Enemyfollow[ENEMYFOLLOW_MAX];	// エネミー情報		
static float			g_Rot;				// キャラクターの向き

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemyfollow(void)
{
	// 位置・回転・スケールの初期設定
	for (int i = 0; i < ENEMYFOLLOW_MAX; i++)
	{
		g_Enemyfollow[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemyfollow[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemyfollow[i].scl = D3DXVECTOR3(4.0f, 4.0f, 4.0f);
		g_Enemyfollow[i].use = false;

		g_Enemyfollow[i].size = D3DXVECTOR3(80.0f, 80.0f, 80.0f);

	}

	LevelEnemyfollow();

	//objモデルの読み込み
	LoadModel((char*)"data/MODEL/Enemyfollow.obj", &g_Model);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemyfollow(void)
{
	//objモデルの解放
	UnloadModel(&g_Model);
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemyfollow(void)
{
	for (int i = 0; i < ENEMYFOLLOW_MAX; i++)
	{
		//useフラグがオフの場合はスキップする
		if (g_Enemyfollow[i].use == false)
		{
			ReleaseShadow(g_Enemyfollow[i].idxShadow);
			continue;
		}

		//影の位置の更新
		D3DXVECTOR3 sPos = g_Enemyfollow[i].pos;
		sPos.y = 0.0f;
		SetPositionShadow(g_Enemyfollow[i].idxShadow, sPos);

		if (!GetPlayer()->isFreezing)
		{
			g_Enemyfollow[i].pos = GetPlayer()->pos + g_Enemyfollow[i].relativePos;
			g_Enemyfollow[i].rot = GetPlayer()->rot;
		}	

		if (g_Enemyfollow[i].pos.y <= -100.0f)
		{
			SceneTransition(SCENE_GAME);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemyfollow(void)
{
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	for (int i = 0; i < ENEMYFOLLOW_MAX; i++)
	{
		//useフラグがオフの場合はスキップする
		if (g_Enemyfollow[i].use == false)
			continue;

		// ワールドマトリックスの初期化（単位行列を作る関数）
		D3DXMatrixIdentity(&g_Enemyfollow[i].mtxWorld);

		// スケールを反映
		D3DXMatrixScaling(&mtxScl, g_Enemyfollow[i].scl.x, g_Enemyfollow[i].scl.y, g_Enemyfollow[i].scl.z);
		D3DXMatrixMultiply(&g_Enemyfollow[i].mtxWorld, &g_Enemyfollow[i].mtxWorld, &mtxScl);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemyfollow[i].rot.y, g_Enemyfollow[i].rot.x, g_Enemyfollow[i].rot.z);
		D3DXMatrixMultiply(&g_Enemyfollow[i].mtxWorld, &g_Enemyfollow[i].mtxWorld, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, g_Enemyfollow[i].pos.x, g_Enemyfollow[i].pos.y, g_Enemyfollow[i].pos.z);
		D3DXMatrixMultiply(&g_Enemyfollow[i].mtxWorld, &g_Enemyfollow[i].mtxWorld, &mtxTranslate);

		// ワールドマトリックスの設定
		SetWorldMatrix(&g_Enemyfollow[i].mtxWorld);

		//objモデルの描画
		DrawModel(&g_Model);
	}
}


//=============================================================================
// エネミー情報を取得
//=============================================================================
ENEMYFOLLOW* GetEnemyfollow(void)
{
	return g_Enemyfollow;
}

void SetEnemyfollow(D3DXVECTOR3 relativePos)
{
	for (int i = 0; i < ENEMYFOLLOW_MAX; i++)
	{
		if (!g_Enemyfollow[i].use)
		{
			g_Enemyfollow[i].relativePos = relativePos;
			g_Enemyfollow[i].pos = GetPlayer()->pos + g_Enemyfollow[i].relativePos;
			g_Enemyfollow[i].use = true;
			D3DXVECTOR3 sPos = g_Enemyfollow[i].pos;
			sPos.y = 0.0f;
			g_Enemyfollow[i].idxShadow = CreateShadow(sPos, 100.0f, 100.0f);
			break;
		}
	}
}

void LevelEnemyfollow(void)
{
	switch (GetCurrentLevel())
	{
	case LEVEL_04:
		SetEnemyfollow(D3DXVECTOR3(100.0f, 0.0f, 100.0f));
		break;
	case LEVEL_05:
		SetEnemyfollow(D3DXVECTOR3(200.0f, 0.0f, 0.0f));
		break;
	case LEVEL_06:
		SetEnemyfollow(D3DXVECTOR3(100.0f, 0.0f, 0.0f));
		SetEnemyfollow(D3DXVECTOR3(0.0f, 0.0f, 100.0f));
		SetEnemyfollow(D3DXVECTOR3(100.0f, 0.0f, 100.0f));
		break;
	case LEVEL_07:
		SetEnemyfollow(D3DXVECTOR3(100.0f, 0.0f, 100.0f));
		break;
	case LEVEL_08:
		SetEnemyfollow(D3DXVECTOR3(100.0f, 0.0f, 100.0f));
		SetEnemyfollow(D3DXVECTOR3(200.0f, 0.0f, 200.0f));
		break;
	case LEVEL_09:
		//SetEnemyfollow(D3DXVECTOR3(0.0f, 0.0f, 100.0f));
		SetEnemyfollow(D3DXVECTOR3(100.0f, 0.0f, 0.0f));
		break;
	case LEVEL_MAX:
		break;
	default:
		break;
	}
}
