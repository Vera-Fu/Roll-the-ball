//=============================================================================
//
// �n�ʏ��� [SKYBALL.h]
// Author : 
//
//=============================================================================
#pragma once
#include <d3dx9.h>
#include "renderer.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
struct SKYBALL
{
	D3DXVECTOR3		pos;		// �ʒu
	D3DXVECTOR3		rot;		// ����(��])
	D3DXVECTOR3		scl;		// �傫��(�X�P�[��)
	bool			use;		// �\���t���O

	int				idxShadow;	// �e�̎��ʎq

	D3DXVECTOR3     size;		// �����蔻��p�T�C�Y

	D3DXMATRIX		mtxWorld;	// ���[���h�}�g���b�N�X
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSkyball(void);
void UninitSkyball(void);
void UpdateSkyball(void);
void DrawSkyball(void);

SKYBALL* GetSkyball(void);


