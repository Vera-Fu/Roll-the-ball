//=============================================================================
//
// ポリゴン表示処理 [enemy.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "enemy.h"
#include "texture.h"
#include "model.h"
#include "light.h"
#include "shadow.h"
#include "level.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	VALUE_MOVE		(4.0f)						// 移動量
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)			// 回転量


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static DX11_MODEL	g_Model;			// モデル読み込み
static ENEMY		g_Enemy[ENEMY_MAX];	// エネミー情報		
static float        g_Rot;				// キャラクターの向き

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemy(void)
{
	// 位置・回転・スケールの初期設定
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		g_Enemy[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[i].rot = D3DXVECTOR3(frand()*D3DX_PI, 0.0f, frand()*D3DX_PI);
		g_Enemy[i].scl = D3DXVECTOR3(4.0f, 4.0f, 4.0f);
		g_Enemy[i].spd = VALUE_MOVE;
		g_Enemy[i].use = false;

		g_Enemy[i].size = D3DXVECTOR3(80.0f, 80.0f, 80.0f);

		for (int j = 0; j < ENEMYMOVEWAY_MAX; j++)
		{
			g_Enemy[i].moveway[j].dir = ENEMY_FRONT;
			g_Enemy[i].moveway[j].distance = 0;
			g_Enemy[i].moveway[j].set = false;
		}
		g_Enemy[i].movewayIndex = 0;
		g_Enemy[i].targetPos = 0.0f;	
		g_Enemy[i].reach = false;	
	}

	LevelEnemy();

	//objモデルの読み込み
	LoadModel((char*)"data/MODEL/Enemy.obj", &g_Model);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy(void)
{
	//objモデルの解放
	UnloadModel(&g_Model);
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemy(void)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		//useフラグがオフの場合はスキップする
		if (g_Enemy[i].use == false)
		{
			ReleaseShadow(g_Enemy[i].idxShadow);
			continue;
		}
			

		//影の位置の更新
		D3DXVECTOR3 sPos = g_Enemy[i].pos;
		sPos.y = 0.0f;
		SetPositionShadow(g_Enemy[i].idxShadow, sPos);

		if (g_Enemy[i].moveway[0].set)
		{
			if (!g_Enemy[i].reach)
			{
				switch (g_Enemy[i].moveway[g_Enemy[i].movewayIndex].dir)
				{
				case ENEMY_FRONT:
					g_Enemy[i].pos.z += g_Enemy[i].spd;
					if (g_Enemy[i].pos.z > g_Enemy[i].targetPos)
					{
						g_Enemy[i].pos.z = g_Enemy[i].targetPos;
						g_Enemy[i].reach = true;
					}
					break;
				case ENEMY_BACK:
					g_Enemy[i].pos.z -= g_Enemy[i].spd;
					if (g_Enemy[i].pos.z < g_Enemy[i].targetPos)
					{
						g_Enemy[i].pos.z = g_Enemy[i].targetPos;
						g_Enemy[i].reach = true;
					}
					break;
				case ENEMY_LEFT:
					g_Enemy[i].pos.x -= g_Enemy[i].spd;
					if (g_Enemy[i].pos.x < g_Enemy[i].targetPos)
					{
						g_Enemy[i].pos.x = g_Enemy[i].targetPos;
						g_Enemy[i].reach = true;
					}
					break;
				case ENEMY_RIGHT:
					g_Enemy[i].pos.x += g_Enemy[i].spd;
					if (g_Enemy[i].pos.x > g_Enemy[i].targetPos)
					{
						g_Enemy[i].pos.x = g_Enemy[i].targetPos;
						g_Enemy[i].reach = true;
					}
					break;
				default:
					break;
				}
			}
			else
			{
				if (g_Enemy[i].moveway[g_Enemy[i].movewayIndex + 1].set)
				{
					g_Enemy[i].movewayIndex++;
				}
				else
				{
					g_Enemy[i].movewayIndex = 0;
				}
				switch (g_Enemy[i].moveway[g_Enemy[i].movewayIndex].dir)
				{
				case ENEMY_FRONT:
					g_Enemy[i].targetPos = g_Enemy[i].pos.z + g_Enemy[i].moveway[g_Enemy[i].movewayIndex].distance * FIELD_SIZE;
					break;
				case ENEMY_BACK:
					g_Enemy[i].targetPos = g_Enemy[i].pos.z - g_Enemy[i].moveway[g_Enemy[i].movewayIndex].distance * FIELD_SIZE;
					break;
				case ENEMY_LEFT:
					g_Enemy[i].targetPos = g_Enemy[i].pos.x - g_Enemy[i].moveway[g_Enemy[i].movewayIndex].distance * FIELD_SIZE;
					break;
				case ENEMY_RIGHT:
					g_Enemy[i].targetPos = g_Enemy[i].pos.x + g_Enemy[i].moveway[g_Enemy[i].movewayIndex].distance * FIELD_SIZE;
					break;
				default:
					break;
				}

				g_Enemy[i].reach = false;
			}
		}			
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemy(void)
{
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		//useフラグがオフの場合はスキップする
		if (g_Enemy[i].use == false)
			continue;

		// ワールドマトリックスの初期化（単位行列を作る関数）
		D3DXMatrixIdentity(&g_Enemy[i].mtxWorld);

		// スケールを反映
		D3DXMatrixScaling(&mtxScl, g_Enemy[i].scl.x, g_Enemy[i].scl.y, g_Enemy[i].scl.z);
		D3DXMatrixMultiply(&g_Enemy[i].mtxWorld, &g_Enemy[i].mtxWorld, &mtxScl);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy[i].rot.y, g_Enemy[i].rot.x, g_Enemy[i].rot.z);
		D3DXMatrixMultiply(&g_Enemy[i].mtxWorld, &g_Enemy[i].mtxWorld, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, g_Enemy[i].pos.x, g_Enemy[i].pos.y, g_Enemy[i].pos.z);
		D3DXMatrixMultiply(&g_Enemy[i].mtxWorld, &g_Enemy[i].mtxWorld, &mtxTranslate);

		// ワールドマトリックスの設定
		SetWorldMatrix(&g_Enemy[i].mtxWorld);

		//objモデルの描画
		DrawModel(&g_Model);
	}
}


//=============================================================================
// エネミー情報を取得
//=============================================================================
ENEMY *GetEnemy(void)
{
	return g_Enemy;
}

void SetEnemy(D3DXVECTOR3 pos)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (!g_Enemy[i].use)
		{
			g_Enemy[i].pos = pos;
			g_Enemy[i].use = true;
			D3DXVECTOR3 sPos = g_Enemy[i].pos;
			sPos.y = 0.0f;
			g_Enemy[i].idxShadow = CreateShadow(sPos, 100.0f, 100.0f);
			break;
		}
	}
}

void SetEnemyMoveway(int enemyIndex, ENEMYDIRECTION dir, int distance)
{
	for (int i = 0; i < ENEMYMOVEWAY_MAX; i++)
	{
		if (!g_Enemy[enemyIndex].moveway[i].set)
		{
			if (i == 0)
			{
				switch (dir)
				{
				case ENEMY_FRONT:
					g_Enemy[enemyIndex].targetPos = g_Enemy[enemyIndex].pos.z + distance * FIELD_SIZE;
					break;
				case ENEMY_BACK:
					g_Enemy[enemyIndex].targetPos = g_Enemy[enemyIndex].pos.z - distance * FIELD_SIZE;
					break;
				case ENEMY_LEFT:
					g_Enemy[enemyIndex].targetPos = g_Enemy[enemyIndex].pos.x - distance * FIELD_SIZE;
					break;
				case ENEMY_RIGHT:
					g_Enemy[enemyIndex].targetPos = g_Enemy[enemyIndex].pos.x + distance * FIELD_SIZE;
					break;
				default:
					break;
				}
			}
			g_Enemy[enemyIndex].moveway[i].dir = dir;
			g_Enemy[enemyIndex].moveway[i].distance = distance;
			g_Enemy[enemyIndex].moveway[i].set = true;
			break;
		}
	}
}

void LevelEnemy(void)
{
	switch (GetCurrentLevel())
	{
	case LEVEL_02:
		SetEnemy(D3DXVECTOR3(0.0f, 50.0f, 200.0f));
		SetEnemyMoveway(0, ENEMY_BACK, 4);
		SetEnemyMoveway(0, ENEMY_FRONT, 4);
		break;
	case LEVEL_03:
		SetEnemy(D3DXVECTOR3(0.0f, 50.0f, 200.0f));
		SetEnemyMoveway(0, ENEMY_BACK, 4);
		SetEnemyMoveway(0, ENEMY_FRONT, 4);
		break;
	case LEVEL_04:
		SetEnemy(D3DXVECTOR3(-200.0f, 50.0f, 100.0f));
		SetEnemyMoveway(0, ENEMY_RIGHT, 4);
		SetEnemyMoveway(0, ENEMY_LEFT, 4);
		break;
	case LEVEL_05:
		SetEnemy(D3DXVECTOR3(-200.0f, 50.0f, -100.0f));
		SetEnemyMoveway(0, ENEMY_RIGHT, 4);
		SetEnemyMoveway(0, ENEMY_LEFT, 4);
		SetEnemy(D3DXVECTOR3(100.0f, 50.0f, 200.0f));
		SetEnemyMoveway(1, ENEMY_BACK, 2);
		SetEnemyMoveway(1, ENEMY_LEFT, 3);
		SetEnemyMoveway(1, ENEMY_RIGHT, 3);
		SetEnemyMoveway(1, ENEMY_FRONT, 2);
		break;
	case LEVEL_06:
		SetEnemy(D3DXVECTOR3(-100.0f, 50.0f, -300.0f));
		SetEnemy(D3DXVECTOR3(-100.0f, 50.0f, -200.0f));
		SetEnemy(D3DXVECTOR3(-100.0f, 50.0f, -100.0f));
		SetEnemy(D3DXVECTOR3(-100.0f, 50.0f, 0.0f));
		SetEnemy(D3DXVECTOR3(-100.0f, 50.0f, 300.0f));
		SetEnemy(D3DXVECTOR3(-100.0f, 50.0f, 200.0f));
		SetEnemy(D3DXVECTOR3(-100.0f, 50.0f, 100.0f));
		SetEnemy(D3DXVECTOR3(200.0f, 50.0f, 200.0f));
		SetEnemy(D3DXVECTOR3(200.0f, 50.0f, 300.0f));
		SetEnemy(D3DXVECTOR3(300.0f, 50.0f, 200.0f));
		break;
	case LEVEL_07:
		SetEnemy(D3DXVECTOR3(-100.0f, 50.0f, 300.0f));
		SetEnemyMoveway(0, ENEMY_BACK, 2);
		SetEnemyMoveway(0, ENEMY_LEFT, 2);
		SetEnemyMoveway(0, ENEMY_RIGHT, 2);
		SetEnemyMoveway(0, ENEMY_FRONT, 2);
		SetEnemy(D3DXVECTOR3(0.0f, 50.0f, 300.0f));
		SetEnemyMoveway(1, ENEMY_BACK, 2);
		SetEnemyMoveway(1, ENEMY_FRONT, 2);
		SetEnemy(D3DXVECTOR3(100.0f, 50.0f, 300.0f));
		SetEnemyMoveway(2, ENEMY_BACK, 1);
		SetEnemyMoveway(2, ENEMY_RIGHT, 2);
		SetEnemyMoveway(2, ENEMY_LEFT, 2);
		SetEnemyMoveway(2, ENEMY_FRONT, 1);
		SetEnemy(D3DXVECTOR3(0.0f, 50.0f, -100.0f));
		SetEnemyMoveway(3, ENEMY_BACK, 2);
		SetEnemyMoveway(3, ENEMY_FRONT, 2);
		SetEnemy(D3DXVECTOR3(200.0f, 50.0f, -200.0f));
		SetEnemy(D3DXVECTOR3(200.0f, 50.0f, -300.0f));
		break;
	case LEVEL_08:
		SetEnemy(D3DXVECTOR3(-100.0f, 50.0f, 300.0f));
		SetEnemyMoveway(0, ENEMY_BACK, 2);
		SetEnemyMoveway(0, ENEMY_LEFT, 2);
		SetEnemyMoveway(0, ENEMY_RIGHT, 2);
		SetEnemyMoveway(0, ENEMY_FRONT, 2);
		SetEnemy(D3DXVECTOR3(0.0f, 50.0f, 300.0f));
		SetEnemyMoveway(1, ENEMY_BACK, 2);
		SetEnemyMoveway(1, ENEMY_FRONT, 2);
		SetEnemy(D3DXVECTOR3(-300.0f, 50.0f, 0.0f));
		SetEnemyMoveway(2, ENEMY_RIGHT, 6);
		SetEnemyMoveway(2, ENEMY_LEFT, 6);
		SetEnemy(D3DXVECTOR3(0.0f, 50.0f, -300.0f));
		SetEnemyMoveway(3, ENEMY_FRONT, 2);
		SetEnemyMoveway(3, ENEMY_BACK, 2);
		SetEnemy(D3DXVECTOR3(200.0f, 50.0f, 200.0f));
		SetEnemy(D3DXVECTOR3(200.0f, 50.0f, 300.0f));
		SetEnemy(D3DXVECTOR3(300.0f, 50.0f, 200.0f));
		SetEnemy(D3DXVECTOR3(200.0f, 50.0f, -200.0f));
		SetEnemy(D3DXVECTOR3(200.0f, 50.0f, -300.0f));		
		break;
	case LEVEL_09:
		SetEnemy(D3DXVECTOR3(400.0f, 50.0f, 0.0f));
		SetEnemyMoveway(0, ENEMY_LEFT, 8);
		SetEnemyMoveway(0, ENEMY_RIGHT, 8);
		SetEnemy(D3DXVECTOR3(0.0f, 50.0f, 400.0f));
		SetEnemyMoveway(1, ENEMY_BACK, 8);
		SetEnemyMoveway(1, ENEMY_FRONT, 8);
		SetEnemy(D3DXVECTOR3(-400.0f, 50.0f, 200.0f));
		SetEnemy(D3DXVECTOR3(-400.0f, 50.0f, 100.0f));

		SetEnemy(D3DXVECTOR3(400.0f, 50.0f, 300.0f));
		SetEnemy(D3DXVECTOR3(400.0f, 50.0f, 200.0f));
		SetEnemy(D3DXVECTOR3(400.0f, 50.0f, 100.0f));

		SetEnemy(D3DXVECTOR3(400.0f, 50.0f, -200.0f));
		SetEnemy(D3DXVECTOR3(300.0f, 50.0f, -200.0f));
		SetEnemy(D3DXVECTOR3(300.0f, 50.0f, -300.0f));
		SetEnemy(D3DXVECTOR3(300.0f, 50.0f, -400.0f));		
		break;
	case LEVEL_MAX:
		break;
	default:
		break;
	}
}
