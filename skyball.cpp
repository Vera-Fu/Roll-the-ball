//=============================================================================
//
// ポリゴン表示処理 [skyball.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "skyball.h"
#include "texture.h"
#include "model.h"
#include "light.h"
#include "bullet.h"
#include "shadow.h"
#include "player.h"

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
static SKYBALL			g_Skyball;	// プレイヤー情報		
//static float        g_Rot;	// キャラクターの向き	

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitSkyball(void)
{
	// 位置・回転・スケールの初期設定
	g_Skyball.pos = GetPlayer()->pos;
	g_Skyball.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Skyball.scl = D3DXVECTOR3(100.0f, 100.0f, 100.0f);
	g_Skyball.use = true;

	//当たり判定用サイズの初期設定
	g_Skyball.size = D3DXVECTOR3(100.0f, 100.0f, 100.0f);

	//objモデルの読み込み
	LoadModel((char*)"data/MODEL/Skyball_01.obj", &g_Model);

	// 並行光源の設定（世界を照らす光）
	LIGHT* pLight = NULL;
	pLight = GetLightData(0);
	pLight->Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);// 光の向き
	pLight->Diffuse = D3DXCOLOR(5.0f, 5.0f, 5.0f, 5.0f);	// 光の色
	pLight->Attenuation = 10.0f;
	pLight->Type = LIGHT_TYPE_DIRECTIONAL;					// 並行光源
	pLight->Enable = true;									// このライトをON
	SetLightData(0, pLight);									// これで設定している

	// 点光源の設定
	pLight = GetLightData(1);
	pLight->Position = D3DXVECTOR4(0.0f, 500.0f, 0.0f, 0.0f);
	pLight->Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);// 光の向き
	pLight->Diffuse = D3DXCOLOR(5.0f, 5.0f, 5.0f, 5.0f);	// 光の色
	pLight->Attenuation = 10.0f;							// 減衰距離
	pLight->Type = LIGHT_TYPE_POINT;						// 並行光源
	pLight->Enable = true;									// このライトをON
	SetLightData(1, pLight);								// これで設定している

	pLight = GetLightData(2);
	pLight->Direction = D3DXVECTOR4(-1.0f, 1.0f, -1.0f, 0.0f);// 光の向き
	pLight->Diffuse = D3DXCOLOR(5.0f, 5.0f, 5.0f, 5.0f);	// 光の色
	pLight->Attenuation = 10.0f;
	pLight->Type = LIGHT_TYPE_DIRECTIONAL;					// 並行光源
	pLight->Enable = true;									// このライトをON
	SetLightData(2, pLight);									// これで設定している

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitSkyball(void)
{
	//objモデルの解放
	UnloadModel(&g_Model);
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateSkyball(void)
{
	g_Skyball.pos.x = GetPlayer()->pos.x;
	g_Skyball.pos.z = GetPlayer()->pos.z;
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawSkyball(void)
{
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ワールドマトリックスの初期化（単位行列を作る関数）
	D3DXMatrixIdentity(&g_Skyball.mtxWorld);

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, g_Skyball.scl.x, g_Skyball.scl.y, g_Skyball.scl.z);

	//第1引数 ＝          第2引数      ＊    第3引数
	D3DXMatrixMultiply(&g_Skyball.mtxWorld, &g_Skyball.mtxWorld, &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Skyball.rot.y, g_Skyball.rot.x, g_Skyball.rot.z);
	D3DXMatrixMultiply(&g_Skyball.mtxWorld, &g_Skyball.mtxWorld, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, g_Skyball.pos.x, g_Skyball.pos.y, g_Skyball.pos.z);
	D3DXMatrixMultiply(&g_Skyball.mtxWorld, &g_Skyball.mtxWorld, &mtxTranslate);

	// ワールドマトリックスの設定
	SetWorldMatrix(&g_Skyball.mtxWorld);

	//カリングなし
	SetCullingMode(CULL_MODE_NONE);

	//objモデルの描画
	DrawModel(&g_Model);

	//カリングを元に戻す
	SetCullingMode(CULL_MODE_BACK);
}


//=============================================================================
// プレイヤー情報を取得
//=============================================================================
SKYBALL* GetSkyball(void)
{
	return &g_Skyball;
}

