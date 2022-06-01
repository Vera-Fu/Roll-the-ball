//=============================================================================
//
// �|���S���\������ [diearea.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "diearea.h"
#include "texture.h"
#include "model.h"
#include "bullet.h"
#include "level.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static DX11_MODEL	g_Model;	// ���f���ǂݍ���
static DIEAREA		g_Diearea[DIEAREA_MAX];	// �v���C���[���		
//static float        g_Rot;	// �L�����N�^�[�̌���	

//=============================================================================
// ����������
//=============================================================================
HRESULT InitDiearea()
{
	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	for (int i = 0; i < DIEAREA_MAX; i++)
	{
		g_Diearea[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Diearea[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Diearea[i].scl = D3DXVECTOR3(5.0f, 5.0f, 5.0f);
		g_Diearea[i].use = false;

		//�����蔻��p�T�C�Y�̏����ݒ�
		g_Diearea[i].size = D3DXVECTOR3(30.0f, 1.0f, 30.0f);
	}
	
	//obj���f���̓ǂݍ���
	LoadModel((char*)"data/MODEL/Diearea.obj", &g_Model);

	LevelDiearea();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitDiearea(void)
{
	//obj���f���̉��
	UnloadModel(&g_Model);
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateDiearea(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawDiearea(void)
{
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ���[���h�}�g���b�N�X�̏������i�P�ʍs������֐��j
	for (int i = 0; i < DIEAREA_MAX; i++)
	{
		if (g_Diearea[i].use)
		{
			D3DXMatrixIdentity(&g_Diearea[i].mtxWorld);

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScl, g_Diearea[i].scl.x, g_Diearea[i].scl.y, g_Diearea[i].scl.z);

			//��1���� ��          ��2����      ��    ��3����
			D3DXMatrixMultiply(&g_Diearea[i].mtxWorld, &g_Diearea[i].mtxWorld, &mtxScl);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Diearea[i].rot.y, g_Diearea[i].rot.x, g_Diearea[i].rot.z);
			D3DXMatrixMultiply(&g_Diearea[i].mtxWorld, &g_Diearea[i].mtxWorld, &mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, g_Diearea[i].pos.x, g_Diearea[i].pos.y, g_Diearea[i].pos.z);
			D3DXMatrixMultiply(&g_Diearea[i].mtxWorld, &g_Diearea[i].mtxWorld, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			SetWorldMatrix(&g_Diearea[i].mtxWorld);

			//obj���f���̕`��
			DrawModel(&g_Model);
		}
	}	
}

void SetDiearea(D3DXVECTOR3 pos)
{
	for (int i = 0; i < DIEAREA_MAX; i++)
	{
		if (!g_Diearea[i].use)
		{
			g_Diearea[i].pos = pos;
			g_Diearea[i].use = true;
			break;
		}
	}
	
}
//=============================================================================
// �v���C���[�����擾
//=============================================================================
DIEAREA* GetDiearea(void)
{
	return g_Diearea;
}

void LevelDiearea(void)
{
	switch (GetCurrentLevel())
	{
	case LEVEL_03:
		SetDiearea(D3DXVECTOR3(0.0f, 0.5f, 200.0f));
		SetDiearea(D3DXVECTOR3(0.0f, 0.5f, 100.0f));
		SetDiearea(D3DXVECTOR3(0.0f, 0.5f, -100.0f));
		SetDiearea(D3DXVECTOR3(0.0f, 0.5f, -200.0f));
		break;
	case LEVEL_04:
		SetDiearea(D3DXVECTOR3(-100.0f, 0.5f, 200.0f));
		break;
	case LEVEL_05:
		SetDiearea(D3DXVECTOR3(-200.0f, 0.5f, 0.0f));
		SetDiearea(D3DXVECTOR3(0.0f, 0.5f, 200.0f));
		break;
	case LEVEL_06:
		SetDiearea(D3DXVECTOR3(-200.0f, 0.5f, 0.0f));
		SetDiearea(D3DXVECTOR3(100.0f, 0.5f, 100.0f));
		break;
	case LEVEL_07:
		SetDiearea(D3DXVECTOR3(300.0f, 0.5f, -100.0f));
		SetDiearea(D3DXVECTOR3(300.0f, 0.5f, -200.0f));
		break;
	case LEVEL_08:
		SetDiearea(D3DXVECTOR3(300.0f, 0.5f, -100.0f));
		SetDiearea(D3DXVECTOR3(300.0f, 0.5f, -200.0f));
		break;
	case LEVEL_09:
		for (int i = 1; i < 5; i++)
		{
			for (int j = -2; j < 4; j++)
			{
				SetDiearea(D3DXVECTOR3(100.0f * j, 0.5f, 100.0f * i));
			}
			SetDiearea(D3DXVECTOR3(-300.0f, 0.5f, 100.0f));
			SetDiearea(D3DXVECTOR3(-300.0f, 0.5f, 200.0f));
			SetDiearea(D3DXVECTOR3(-300.0f, 0.5f, 300.0f));
			SetDiearea(D3DXVECTOR3(0.0f, 0.5f, -100.0f));
			SetDiearea(D3DXVECTOR3(0.0f, 0.5f, -200.0f));
			SetDiearea(D3DXVECTOR3(0.0f, 0.5f, -300.0f));
			SetDiearea(D3DXVECTOR3(0.0f, 0.5f, -400.0f));

		}
		break;
	case LEVEL_MAX:
		break;
	default:
		break;
	}
}