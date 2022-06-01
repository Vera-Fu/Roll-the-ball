//=============================================================================
//
// 当たり判定処理 [collision.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "collision.h"
#include "player.h"
#include "enemy.h"
#include "score.h"
#include "shadow.h"
#include "meshfield.h"
#include "goal.h"
#include "scene.h"
#include "fade.h"
#include "level.h"
#include "diearea.h"
#include "enemyfollow.h"
#include "bullet.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// 構造体定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
bool CollisionBB(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR3 size1, D3DXVECTOR3 size2);
bool CollisionBS(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static int g_WinSE = 0;
static int g_LoseSE = 0;
static int g_EnemyFollowSE = 0;

//=============================================================================
// 当たり判定処理
//=============================================================================
void UpdateCollision(void)
{
	PLAYER* player = GetPlayer();	// プレイヤーのポインターを初期化
	ENEMY* enemy = GetEnemy();		// エネミーのポインターを初期化
	FIELD* field = GetMeshField();
	GOAL* goal = GetGoal();
	DIEAREA* diearea = GetDiearea();
	ENEMYFOLLOW* enemyFollow = GetEnemyfollow();
	BULLET* bullet = GetBullet();

	g_WinSE = LoadSound("data/SE/Win.wav");
	g_LoseSE = LoadSound("data/SE/Lose.wav");
	g_EnemyFollowSE = LoadSound("data/SE/EnemyFollow.wav");

	// 敵と操作キャラ(BB)
	if (player->use && !player->isFreezing) 
	{
		if (CollisionBS(player->pos, goal->pos, player->size.x / 2, goal->size.x / 2))
		{
			UnlockNextLevel(GetCurrentLevel());
			player->isFreezing = true;
			SceneTransition(SCENE_RESULT);
			PlaySound(g_WinSE, 0);
		}

		for (int i = 0; i < ENEMY_MAX; i++)
		{
			if (enemy[i].use == false)
				continue;

//			if (CollisionBB(player->pos, enemy[i].pos, player->size, enemy[i].size))
			if (CollisionBS(player->pos, enemy[i].pos, player->size.x / 2, enemy[i].size.x / 2))
			{
				player->isFreezing = true;
				PlaySound(g_LoseSE, 0);
				SceneTransition(SCENE_RESULT);
			}
		}
		
		for (int i = 0; i < DIEAREA_MAX; i++)
		{
			if (diearea[i].use)
			{
				if (CollisionBB(player->pos, diearea[i].pos, player->size, diearea[i].size))
				{
					player->isFreezing = true;
					PlaySound(g_LoseSE, 0);
					SceneTransition(SCENE_RESULT);
				}
			}
		}

		for (int i = 0; i < BULLET_MAX; i++)
		{
			if (bullet[i].use && bullet[i].getable)
			{
				if (CollisionBS(bullet[i].pos, player->pos, bullet[i].size.x / 2, player->size.x / 2))
				{
					player->bulletNum++;
					bullet[i].use = false;
				}				
			}
		}
	}	

	if (!CollisionBB(player->pos, field->pos, player->size, field->size))
	{
		player->pos.y -= GRAVITY * 0.5;
		player->isFreezing = true;
	}

	for (int i = 0; i < ENEMYFOLLOW_MAX; i++)
	{
		if (enemyFollow[i].use)
		{
			if (!CollisionBB(enemyFollow[i].pos, field->pos, enemyFollow[i].size, field->size))
			{
				enemyFollow[i].pos.y -= GRAVITY * 0.5;
				player->isFreezing = true;
			}
			if (CollisionBS(enemyFollow[i].pos, goal->pos, enemyFollow[i].size.x / 2, goal->size.x / 2))
			{
				player->isFreezing = true;
				SceneTransition(SCENE_GAME);
			}
			for (int j = 0; j < DIEAREA_MAX; j++)
			{
				if (diearea[j].use)
				{
					if (CollisionBB(enemyFollow[i].pos, diearea[j].pos, enemyFollow[i].size, diearea[j].size))
					{
						enemyFollow[i].use = false;
						PlaySound(g_EnemyFollowSE, 0);
					}
				}
			}
			for (int j = 0; j < BULLET_MAX; j++)
			{
				if (bullet[j].use)
				{
					if (CollisionBS(bullet[j].pos, enemyFollow[i].pos, bullet[j].size.x / 2, enemyFollow[i].size.x / 2))
					{
						enemyFollow[i].use = false;
						bullet[j].use = false;
						PlaySound(g_LoseSE, 0);
						SceneTransition(SCENE_RESULT);
					}
				}
			}
		}
	}

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (!enemy[i].use)
			continue;

		for (int j = 0; j < BULLET_MAX; j++)
		{
			if (bullet[j].use)
			{
				if (CollisionBS(bullet[j].pos, enemy[i].pos, bullet[j].size.x / 2, enemy[i].size.x / 2))
				{
					enemy[i].use = false;
					bullet[j].use = false;
				}
			}			
		}
		
	}
}

//=============================================================================
// 境界箱BBによる当たり判定処理
// 回転は考慮しない
// 戻り値：当たってたらtrue
//=============================================================================
bool CollisionBB(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR3 size1, D3DXVECTOR3 size2)
{
	float Axmax = pos1.x + (size1.x / 2);
	float Axmin = pos1.x - (size1.x / 2);
	float Aymax = pos1.y + (size1.y / 2);
	float Aymin = pos1.y - (size1.y / 2);
	float Azmax = pos1.z + (size1.z / 2);
	float Azmin = pos1.z - (size1.z / 2);

	float Bxmax = pos2.x + (size2.x / 2);
	float Bxmin = pos2.x - (size2.x / 2);
	float Bymax = pos2.y + (size2.y / 2);
	float Bymin = pos2.y - (size2.y / 2);
	float Bzmax = pos2.z + (size2.z / 2);
	float Bzmin = pos2.z - (size2.z / 2);

	if ((Axmax > Bxmin) && (Axmin < Bxmax))
	{
		if ((Aymin < Bymax) && (Aymax > Bymin))
		{
			if ((Azmax > Bzmin) && (Azmin < Bzmax))
			{
				return true;
			}
		}
	}

	return false;
}

//=============================================================================
// 境界球BSによる当たり判定処理
// サイズは半径
// 戻り値：当たってたらtrue
//=============================================================================
bool CollisionBS(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2)
{
	//pos1とpos2をつなぐベクトルを作る
	D3DXVECTOR3 dist = pos2 - pos1;

	//作ったベクトルの大きさを計算する
//	float length = D3DXVec3Length(&dist);

	//Sqがついている関数は平方根の計算をしないバージョン
	float length = D3DXVec3LengthSq(&dist);

	//1と2の半径を足す
	float size = size1 + size2;

	//判定する相手の方を二乗する
	size = size * size;

	//半径の方が大きいとき、二つの円は重なっている
	if (length < size)
		return true;

	return false;
}
