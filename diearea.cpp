//=============================================================================
//
// ポリゴン表示処理 [diearea.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "diearea.h"
#include "texture.h"
#include "model.h"
#include "bullet.h"
#include "level.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static DX11_MODEL	g_Model;	// モデル読み込み
static DIEAREA		g_Diearea[DIEAREA_MAX];	// プレイヤー情報		
//static float        g_Rot;	// キャラクターの向き	

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitDiearea()
{
	// 位置・回転・スケールの初期設定
	for (int i = 0; i < DIEAREA_MAX; i++)
	{
		g_Diearea[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Diearea[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Diearea[i].scl = D3DXVECTOR3(5.0f, 5.0f, 5.0f);
		g_Diearea[i].use = false;

		//当たり判定用サイズの初期設定
		g_Diearea[i].size = D3DXVECTOR3(30.0f, 1.0f, 30.0f);
	}
	
	//objモデルの読み込み
	LoadModel((char*)"data/MODEL/Diearea.obj", &g_Model);

	LevelDiearea();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitDiearea(void)
{
	//objモデルの解放
	UnloadModel(&g_Model);
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateDiearea(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawDiearea(void)
{
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ワールドマトリックスの初期化（単位行列を作る関数）
	for (int i = 0; i < DIEAREA_MAX; i++)
	{
		if (g_Diearea[i].use)
		{
			D3DXMatrixIdentity(&g_Diearea[i].mtxWorld);

			// スケールを反映
			D3DXMatrixScaling(&mtxScl, g_Diearea[i].scl.x, g_Diearea[i].scl.y, g_Diearea[i].scl.z);

			//第1引数 ＝          第2引数      ＊    第3引数
			D3DXMatrixMultiply(&g_Diearea[i].mtxWorld, &g_Diearea[i].mtxWorld, &mtxScl);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Diearea[i].rot.y, g_Diearea[i].rot.x, g_Diearea[i].rot.z);
			D3DXMatrixMultiply(&g_Diearea[i].mtxWorld, &g_Diearea[i].mtxWorld, &mtxRot);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, g_Diearea[i].pos.x, g_Diearea[i].pos.y, g_Diearea[i].pos.z);
			D3DXMatrixMultiply(&g_Diearea[i].mtxWorld, &g_Diearea[i].mtxWorld, &mtxTranslate);

			// ワールドマトリックスの設定
			SetWorldMatrix(&g_Diearea[i].mtxWorld);

			//objモデルの描画
			DrawModel(&g_Model);
		}
	}	
}

void SetDiearea(D3DXVECTOR3 pos)
{
	for (int i = 0; i < DIEAREA_MAX; i++)
	{
		if (!g_Diearea[i].use)
		{
			g_Diearea[i].pos = pos;
			g_Diearea[i].use = true;
			break;
		}
	}
	
}
//=============================================================================
// プレイヤー情報を取得
//=============================================================================
DIEAREA* GetDiearea(void)
{
	return g_Diearea;
}

void LevelDiearea(void)
{
	switch (GetCurrentLevel())
	{
	case LEVEL_03:
		SetDiearea(D3DXVECTOR3(0.0f, 0.5f, 200.0f));
		SetDiearea(D3DXVECTOR3(0.0f, 0.5f, 100.0f));
		SetDiearea(D3DXVECTOR3(0.0f, 0.5f, -100.0f));
		SetDiearea(D3DXVECTOR3(0.0f, 0.5f, -200.0f));
		break;
	case LEVEL_04:
		SetDiearea(D3DXVECTOR3(-100.0f, 0.5f, 200.0f));
		break;
	case LEVEL_05:
		SetDiearea(D3DXVECTOR3(-200.0f, 0.5f, 0.0f));
		SetDiearea(D3DXVECTOR3(0.0f, 0.5f, 200.0f));
		break;
	case LEVEL_06:
		SetDiearea(D3DXVECTOR3(-200.0f, 0.5f, 0.0f));
		SetDiearea(D3DXVECTOR3(100.0f, 0.5f, 100.0f));
		break;
	case LEVEL_07:
		SetDiearea(D3DXVECTOR3(300.0f, 0.5f, -100.0f));
		SetDiearea(D3DXVECTOR3(300.0f, 0.5f, -200.0f));
		break;
	case LEVEL_08:
		SetDiearea(D3DXVECTOR3(300.0f, 0.5f, -100.0f));
		SetDiearea(D3DXVECTOR3(300.0f, 0.5f, -200.0f));
		break;
	case LEVEL_09:
		for (int i = 1; i < 5; i++)
		{
			for (int j = -2; j < 4; j++)
			{
				SetDiearea(D3DXVECTOR3(100.0f * j, 0.5f, 100.0f * i));
			}
			SetDiearea(D3DXVECTOR3(-300.0f, 0.5f, 100.0f));
			SetDiearea(D3DXVECTOR3(-300.0f, 0.5f, 200.0f));
			SetDiearea(D3DXVECTOR3(-300.0f, 0.5f, 300.0f));
			SetDiearea(D3DXVECTOR3(0.0f, 0.5f, -100.0f));
			SetDiearea(D3DXVECTOR3(0.0f, 0.5f, -200.0f));
			SetDiearea(D3DXVECTOR3(0.0f, 0.5f, -300.0f));
			SetDiearea(D3DXVECTOR3(0.0f, 0.5f, -400.0f));

		}
		break;
	case LEVEL_MAX:
		break;
	default:
		break;
	}
}