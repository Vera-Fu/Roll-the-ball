//=============================================================================
//
// ポリゴン表示処理 [player.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "player.h"
#include "texture.h"
#include "model.h"
#include "bullet.h"
#include "shadow.h"
#include "fade.h"
#include "sound.h"
#include "level.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	VALUE_MOVE		(6.0f)						// 移動量
#define	VALUE_ROTATE	(D3DX_PI * 0.04f)			// 回転量
#define VALUE_SPDCOEFFICIENT	(0.03f)


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static DX11_MODEL	g_Model;	// モデル読み込み
static PLAYER		g_Player;	// プレイヤー情報
//static float        g_Rot;	// キャラクターの向き	
static int			g_BulletSE = 0;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayer(D3DXVECTOR3 startPos, int bulletNum)
{
	// 位置・回転・スケールの初期設定
	g_Player.pos = startPos;
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.scl = D3DXVECTOR3(4.0f, 4.0f, 4.0f);
	g_Player.use = true;
	g_Player.isFreezing = false;

	//当たり判定用サイズの初期設定
	g_Player.size = D3DXVECTOR3(80.0f, 80.0f, 80.0f);

	g_Player.spd = VALUE_MOVE;
	g_Player.rotSpd = VALUE_ROTATE;
	g_Player.spdCoefficient = 0.0f;

	g_Player.bulletNum = bulletNum;

	g_BulletSE = LoadSound("data/SE/Bullet.wav");

	//objモデルの読み込み
	if (GetIsLevelFinished(LEVEL(LEVEL_MAX - 1)))
	{
		LoadModel((char*)"data/MODEL/Ball_03.obj", &g_Model);
	}
	else
	{
		LoadModel((char*)"data/MODEL/Ball_01.obj", &g_Model);
	}
	

	//影の設定
	D3DXVECTOR3 sPos = g_Player.pos;
	sPos.y = 0.0f;
	g_Player.idxShadow = CreateShadow(sPos, 100.0f, 100.0f);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	//objモデルの解放
	UnloadModel(&g_Model);
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	//影の位置の更新
	D3DXVECTOR3 sPos = g_Player.pos;
	sPos.y = g_Player.pos.y - g_Player.size.y / 2;
	SetPositionShadow(g_Player.idxShadow, sPos);

	if (g_Player.isFreezing)
	{	
		if (g_Player.pos.y <= -100.0f)
		{
			SceneTransition(SCENE_GAME);
		}
		return;
	}

	CAMERA *cam = GetCamera();

	//移動速度の減衰処理
	if (!GetKeyboardPress(DIK_UP) && !GetKeyboardPress(DIK_DOWN) && !GetKeyboardPress(DIK_W) && !GetKeyboardPress(DIK_S))
	{
		if (g_Player.spdCoefficient > 0.0f)
		{
			g_Player.spdCoefficient -= 0.01f;
			if (g_Player.spdCoefficient < 0.0f)
			{
				g_Player.spdCoefficient = 0.0f;
			}
		}
		if (g_Player.spdCoefficient < 0.0f)
		{
			g_Player.spdCoefficient += 0.01f;
			if (g_Player.spdCoefficient > 0.0f)
			{
				g_Player.spdCoefficient = 0.0f;
			}
		}
	}	

	if (GetKeyboardPress(DIK_UP) || GetKeyboardPress(DIK_W))
	{
		g_Player.spdCoefficient += VALUE_SPDCOEFFICIENT;
	}
	if (GetKeyboardPress(DIK_DOWN) || GetKeyboardPress(DIK_S))
	{
		g_Player.spdCoefficient -= VALUE_SPDCOEFFICIENT;
	}

	if (g_Player.spdCoefficient > 1.0f)
	{
		g_Player.spdCoefficient = 1.0f;
	}
	if (g_Player.spdCoefficient < -1.0f)
	{
		g_Player.spdCoefficient = -1.0f;
	}

	{	// 押した方向にプレイヤーを移動させる
		// 押した方向にプレイヤーを向かせている所
		g_Player.rot.y = cam->rot.y;

		g_Player.rot.x += g_Player.rotSpd * g_Player.spdCoefficient;

		g_Player.pos.x += sinf(g_Player.rot.y) * g_Player.spd * g_Player.spdCoefficient;
		g_Player.pos.z += cosf(g_Player.rot.y) * g_Player.spd * g_Player.spdCoefficient;

	}


	// 弾を撃つ
	if (GetKeyboardTrigger(DIK_SPACE) && g_Player.bulletNum > 0)
	{
		PlaySound(g_BulletSE, 0);
		SetBullet(g_Player.pos, false);
		g_Player.bulletNum--;
	}	

#ifdef _DEBUG	// デバッグ情報を表示する
	char* str = GetDebugStr();
	sprintf(&str[strlen(str)], " rotX:%.2f rotY:%.2f", g_Player.rot.x, g_Player.rot.y);

#endif
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ワールドマトリックスの初期化（単位行列を作る関数）
	D3DXMatrixIdentity(&g_Player.mtxWorld);

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, g_Player.scl.x, g_Player.scl.y, g_Player.scl.z);

	                   //第1引数 ＝          第2引数      ＊    第3引数
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTranslate);

	// ワールドマトリックスの設定
	SetWorldMatrix(&g_Player.mtxWorld);

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
PLAYER *GetPlayer(void)
{
	return &g_Player;
}

