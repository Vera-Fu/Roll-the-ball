//=============================================================================
//
// �n�ʏ��� [enemyfollow.h]
// Author : 
//
//=============================================================================
#pragma once

#include <d3dx9.h>
#include "renderer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ENEMYFOLLOW_MAX 10

struct ENEMYFOLLOW
{
	D3DXVECTOR3		pos;		// �ʒu
	D3DXVECTOR3		rot;		// ����(��])
	D3DXVECTOR3		scl;		// �傫��(�X�P�[��)
	D3DXVECTOR3		relativePos;

	float			spd;		// �ړ��X�s�[�h
	bool			use;		// �\���t���O

	int				idxShadow;	// �e�̎��ʎq

	D3DXVECTOR3     size;		// �����蔻��p�T�C�Y

	D3DXMATRIX		mtxWorld;	// ���[���h�}�g���b�N�X
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEnemyfollow(void);
void UninitEnemyfollow(void);
void UpdateEnemyfollow(void);
void DrawEnemyfollow(void);

ENEMYFOLLOW* GetEnemyfollow(void);
void SetEnemyfollow(D3DXVECTOR3 pos);

void LevelEnemyfollow(void);