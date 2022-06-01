//=============================================================================
//
// �n�ʏ��� [player.h]
// Author : 
//
//=============================================================================
#pragma once

#include <d3dx9.h>
#include "renderer.h"

enum PLAYERORIENTATION
{
	PLAYER_UP,
	PLAYER_DOWN,
	PLAYER_LEFT,
	PLAYER_RIGHT,
	PLAYERORIENTATION_MAX
};

//*****************************************************************************
// �}�N����`
//*****************************************************************************
struct PLAYER
{
	D3DXVECTOR3		pos;		// �ʒu
	D3DXVECTOR3		rot;		// ����(��])
	D3DXVECTOR3		scl;		// �傫��(�X�P�[��)
	float			spd;		// �ړ��X�s�[�h
	float			rotSpd;
	float			spdCoefficient;
	bool			use;		// �\���t���O
	bool			isFreezing;

	int				bulletNum;

	int				idxShadow;	// �e�̎��ʎq

	D3DXVECTOR3     size;		// �����蔻��p�T�C�Y

	D3DXMATRIX		mtxWorld;	// ���[���h�}�g���b�N�X
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayer(D3DXVECTOR3 startPos, int bulletNum);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

PLAYER *GetPlayer(void);
