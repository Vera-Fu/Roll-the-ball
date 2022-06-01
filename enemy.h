//=============================================================================
//
// �n�ʏ��� [enemy.h]
// Author : 
//
//=============================================================================
#pragma once

#include <d3dx9.h>
#include "renderer.h"

//*****************************************************************************
// �}�N����`
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
	D3DXVECTOR3		pos;		// �ʒu
	D3DXVECTOR3		rot;		// ����(��])
	D3DXVECTOR3		scl;		// �傫��(�X�P�[��)
	ENEMYMOVEWAY	moveway[ENEMYMOVEWAY_MAX];
	int				movewayIndex;
	float			targetPos;
	bool			reach;

	float			spd;		// �ړ��X�s�[�h
	bool			use;		// �\���t���O

	int				idxShadow;	// �e�̎��ʎq

	D3DXVECTOR3     size;		// �����蔻��p�T�C�Y

	D3DXMATRIX		mtxWorld;	// ���[���h�}�g���b�N�X
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);

ENEMY *GetEnemy(void);
void SetEnemy(D3DXVECTOR3 pos);
void SetEnemyMoveway(int enemyIndex, ENEMYDIRECTION dir, int distance);

void LevelEnemy(void);