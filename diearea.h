//=============================================================================
//
// �n�ʏ��� [DIEAREA.h]
// Author : 
//
//=============================================================================
#pragma once
#include <d3dx9.h>
#include "renderer.h"

#define DIEAREA_MAX (50)

//*****************************************************************************
// �}�N����`
//*****************************************************************************
struct DIEAREA
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
HRESULT InitDiearea(void);
void UninitDiearea(void);
void UpdateDiearea(void);
void DrawDiearea(void);

void SetDiearea(D3DXVECTOR3 pos);
DIEAREA* GetDiearea(void);

void LevelDiearea(void);
