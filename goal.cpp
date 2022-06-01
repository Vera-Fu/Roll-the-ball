//=============================================================================
//
// ポリゴン表示処理 [goal.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "goal.h"
#include "texture.h"
#include "model.h"
#include "bullet.h"
#include "shadow.h"

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
static GOAL			g_Goal;	// プレイヤー情報		
//static float        g_Rot;	// キャラクターの向き	

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitGoal(D3DXVECTOR3 startPos)
{
	// 位置・回転・スケールの初期設定
	g_Goal.pos = startPos;
	g_Goal.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Goal.scl = D3DXVECTOR3(4.0f, 3.0f, 4.0f);
	g_Goal.use = true;

	//当たり判定用サイズの初期設定
	g_Goal.size = D3DXVECTOR3(50.0f, 50.0f, 50.0f);

	//objモデルの読み込み
	LoadModel((char*)"data/MODEL/Goal.obj", &g_Model);

	//影の設定
	D3DXVECTOR3 sPos = g_Goal.pos;
	sPos.y = 0.0f;
	g_Goal.idxShadow = CreateShadow(sPos, 50.0f, 50.0f);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitGoal(void)
{
	//objモデルの解放
	UnloadModel(&g_Model);
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGoal(void)
{
	//影の位置の更新
	D3DXVECTOR3 sPos = g_Goal.pos;
	sPos.y = g_Goal.pos.y - g_Goal.size.y / 2;
	SetPositionShadow(g_Goal.idxShadow, sPos);


#ifdef _DEBUG	// デバッグ情報を表示する
	char* str = GetDebugStr();
	sprintf(&str[strlen(str)], " rotX:%.2f rotY:%.2f", g_Goal.rot.x, g_Goal.rot.y);

#endif
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawGoal(void)
{
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ワールドマトリックスの初期化（単位行列を作る関数）
	D3DXMatrixIdentity(&g_Goal.mtxWorld);

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, g_Goal.scl.x, g_Goal.scl.y, g_Goal.scl.z);

	//第1引数 ＝          第2引数      ＊    第3引数
	D3DXMatrixMultiply(&g_Goal.mtxWorld, &g_Goal.mtxWorld, &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Goal.rot.y, g_Goal.rot.x, g_Goal.rot.z);
	D3DXMatrixMultiply(&g_Goal.mtxWorld, &g_Goal.mtxWorld, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, g_Goal.pos.x, g_Goal.pos.y, g_Goal.pos.z);
	D3DXMatrixMultiply(&g_Goal.mtxWorld, &g_Goal.mtxWorld, &mtxTranslate);

	// ワールドマトリックスの設定
	SetWorldMatrix(&g_Goal.mtxWorld);

	//objモデルの描画
	DrawModel(&g_Model);
}


//=============================================================================
// プレイヤー情報を取得
//=============================================================================
GOAL* GetGoal(void)
{
	return &g_Goal;
}

