//=============================================================================
//
// �����蔻�菈�� [collision.cpp]
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
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �\���̒�`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
bool CollisionBB(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR3 size1, D3DXVECTOR3 size2);
bool CollisionBS(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static int g_WinSE = 0;
static int g_LoseSE = 0;
static int g_EnemyFollowSE = 0;

//=============================================================================
// �����蔻�菈��
//=============================================================================
void UpdateCollision(void)
{
	PLAYER* player = GetPlayer();	// �v���C���[�̃|�C���^�[��������
	ENEMY* enemy = GetEnemy();		// �G�l�~�[�̃|�C���^�[��������
	FIELD* field = GetMeshField();
	GOAL* goal = GetGoal();
	DIEAREA* diearea = GetDiearea();
	ENEMYFOLLOW* enemyFollow = GetEnemyfollow();
	BULLET* bullet = GetBullet();

	g_WinSE = LoadSound("data/SE/Win.wav");
	g_LoseSE = LoadSound("data/SE/Lose.wav");
	g_EnemyFollowSE = LoadSound("data/SE/EnemyFollow.wav");

	// �G�Ƒ���L����(BB)
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
// ���E��BB�ɂ�铖���蔻�菈��
// ��]�͍l�����Ȃ�
// �߂�l�F�������Ă���true
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
// ���E��BS�ɂ�铖���蔻�菈��
// �T�C�Y�͔��a
// �߂�l�F�������Ă���true
//=============================================================================
bool CollisionBS(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2)
{
	//pos1��pos2���Ȃ��x�N�g�������
	D3DXVECTOR3 dist = pos2 - pos1;

	//������x�N�g���̑傫�����v�Z����
//	float length = D3DXVec3Length(&dist);

	//Sq�����Ă���֐��͕������̌v�Z�����Ȃ��o�[�W����
	float length = D3DXVec3LengthSq(&dist);

	//1��2�̔��a�𑫂�
	float size = size1 + size2;

	//���肷�鑊��̕����悷��
	size = size * size;

	//���a�̕����傫���Ƃ��A��̉~�͏d�Ȃ��Ă���
	if (length < size)
		return true;

	return false;
}
