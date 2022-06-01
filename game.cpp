/*==============================================================================

   ゲーム処理 [game.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/

#include "game.h"
#include "main.h"
#include "input.h"
#include "fade.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "meshfield.h"
#include "collision.h"
#include "sound.h"
#include "score.h"
#include "camera.h"
#include "light.h"
#include "shadow.h"
#include "goal.h"
#include "level.h"
#include "skyball.h"
#include "diearea.h"
#include "enemyfollow.h"
#include "pause.h"


/*------------------------------------------------------------------------------
   定数定義
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   構造体宣言
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   プロトタイプ宣言
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
   グローバル変数の定義
------------------------------------------------------------------------------*/
static int g_BGMNo = 0;


/*------------------------------------------------------------------------------
   初期化関数
------------------------------------------------------------------------------*/
void InitGame(void)
{
	// カメラの初期化
	InitCamera();

	// ライトの初期化
	InitLight();

	// 影の初期化
	InitShadow();

	//
	InitGameLevel();

	//// 地面の初期化
	//InitMeshField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10, 10, 100.0f, 100.0f);

	//// 
	//InitGoal(D3DXVECTOR3(450.0f, 50.0f, 450.0f));

	//// プレイヤーの初期化
	//InitPlayer(D3DXVECTOR3(0.0f, 50.0f, 0.0f));

	//
	InitDiearea();

	//
	InitSkyball();

	// エネミーの初期化
	InitEnemy();
	InitEnemyfollow();

	// 弾の初期化
	InitBullet();

	// スコアの初期化
	InitScore();

	//
	InitPause();

	SetLightEnable(true);
}

/*------------------------------------------------------------------------------
   終了処理をする関数
------------------------------------------------------------------------------*/
void UninitGame()
{
	//初期化とは逆順に終了処理を行う
	UninitScore();
	UninitShadow();
	UninitBullet();
	UninitEnemy();
	UninitEnemyfollow();
	UninitPlayer();
	UninitMeshField();
	UninitDiearea();
	UninitGoal();
	UninitSkyball();
	UninitPause();
}

/*------------------------------------------------------------------------------
   更新処理をする関数
------------------------------------------------------------------------------*/
void UpdateGame(void)
{
	if (!GetIsPause())
	{
		// カメラ更新
		UpdateCamera();

		// 地面の更新処理
		UpdateMeshField();

		//
		UpdateDiearea();

		//
		UpdateGoal();

		// プレイヤーの更新処理
		UpdatePlayer();

		//
		UpdateSkyball();

		// エネミーの更新処理
		UpdateEnemy();
		UpdateEnemyfollow();

		// 弾の更新処理
		UpdateBullet();

		// 影の更新処理
		UpdateShadow();

		// スコアの更新処理
		UpdateScore();

		// 当たり判定の更新処理
		UpdateCollision();
	}
	
	UpdatePause();
}

/*------------------------------------------------------------------------------
   描画処理をする関数
------------------------------------------------------------------------------*/
void DrawGame(void)
{
	// プレイヤー視点
	D3DXVECTOR3 pos = GetPlayer()->pos;
	pos.y = 0.0f;			// カメラ酔いを防ぐためにクリアしている
	SetCameraAT(pos);
	SetCamera();

	// 深度テスト有効
	SetDepthEnable(true);

	// ライティング有効
	SetLightEnable(true);

	if (GetPlayer()->isFreezing)
	{
		// 影の描画処理
		DrawShadow();

		// 地面の描画処理
		DrawMeshField();
	}
	else
	{
		// 地面の描画処理
		DrawMeshField();

		// 影の描画処理
		DrawShadow();
	}

	//
	DrawDiearea();

	//
	DrawGoal();

	// エネミーの描画処理
	DrawEnemy();
	DrawEnemyfollow();

	// プレイヤーの描画処理
	DrawPlayer();

	//
	DrawSkyball();

	// 弾の描画処理
	DrawBullet();

	// マトリクス設定
	SetWorldViewProjection2D();//座標の2D変換

	// 2D描画なので深度無効
	SetDepthEnable(false);

	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);

	// スコアの描画処理
	DrawScore();

	//
	DrawPause();
}

void InitGameLevel(void)
{

	if (GetCurrentLevel() == LEVEL_01)
	{
		// 地面の初期化
		InitMeshField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3, 3);

		// 
		InitGoal(D3DXVECTOR3(100.0f, 50.0f, 100.0f));

		// プレイヤーの初期化
		InitPlayer(D3DXVECTOR3(-100.0f, 40.0f, -100.0f), 0);
	}

	if (GetCurrentLevel() == LEVEL_02 || GetCurrentLevel() == LEVEL_03 || GetCurrentLevel() == LEVEL_04 || GetCurrentLevel() == LEVEL_05)
	{
		// 地面の初期化
		InitMeshField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 5, 5);

		// 
		InitGoal(D3DXVECTOR3(200.0f, 50.0f, 200.0f));

		// プレイヤーの初期化
		InitPlayer(D3DXVECTOR3(-200.0f, 40.0f, -200.0f), 0);
	}

	if (GetCurrentLevel() == LEVEL_06 || GetCurrentLevel() == LEVEL_07 || GetCurrentLevel() == LEVEL_08)
	{
		// 地面の初期化
		InitMeshField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 7, 7);

		// 
		InitGoal(D3DXVECTOR3(300.0f, 50.0f, 300.0f));

		// プレイヤーの初期化
		if (GetCurrentLevel() == LEVEL_06)
		{
			InitPlayer(D3DXVECTOR3(-300.0f, 40.0f, -300.0f), 1);
		}
		else
		{
			InitPlayer(D3DXVECTOR3(-300.0f, 40.0f, -300.0f), 0);
		}
		
	}

	if (GetCurrentLevel() == LEVEL_09)
	{
		// 地面の初期化
		InitMeshField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 9, 9);

		// 
		InitGoal(D3DXVECTOR3(400.0f, 50.0f, 400.0f));

		// プレイヤーの初期化
		InitPlayer(D3DXVECTOR3(-400.0f, 40.0f, -400.0f), 0);
	}
	
}

