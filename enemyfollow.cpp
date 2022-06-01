//=============================================================================
//
// �|���S���\������ [enemyfollow.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "enemyfollow.h"
#include "texture.h"
#include "model.h"
#include "light.h"
#include "player.h"
#include "shadow.h"
#include "level.h"
#include "fade.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)			// ��]��


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static DX11_MODEL		g_Model;			// ���f���ǂݍ���
static ENEMYFOLLOW		g_Enemyfollow[ENEMYFOLLOW_MAX];	// �G�l�~�[���		
static float			g_Rot;				// �L�����N�^�[�̌���

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemyfollow(void)
{
	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	for (int i = 0; i < ENEMYFOLLOW_MAX; i++)
	{
		g_Enemyfollow[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemyfollow[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemyfollow[i].scl = D3DXVECTOR3(4.0f, 4.0f, 4.0f);
		g_Enemyfollow[i].use = false;

		g_Enemyfollow[i].size = D3DXVECTOR3(80.0f, 80.0f, 80.0f);

	}

	LevelEnemyfollow();

	//obj���f���̓ǂݍ���
	LoadModel((char*)"data/MODEL/Enemyfollow.obj", &g_Model);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemyfollow(void)
{
	//obj���f���̉��
	UnloadModel(&g_Model);
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemyfollow(void)
{
	for (int i = 0; i < ENEMYFOLLOW_MAX; i++)
	{
		//use�t���O���I�t�̏ꍇ�̓X�L�b�v����
		if (g_Enemyfollow[i].use == false)
		{
			ReleaseShadow(g_Enemyfollow[i].idxShadow);
			continue;
		}

		//�e�̈ʒu�̍X�V
		D3DXVECTOR3 sPos = g_Enemyfollow[i].pos;
		sPos.y = 0.0f;
		SetPositionShadow(g_Enemyfollow[i].idxShadow, sPos);

		if (!GetPlayer()->isFreezing)
		{
			g_Enemyfollow[i].pos = GetPlayer()->pos + g_Enemyfollow[i].relativePos;
			g_Enemyfollow[i].rot = GetPlayer()->rot;
		}	

		if (g_Enemyfollow[i].pos.y <= -100.0f)
		{
			SceneTransition(SCENE_GAME);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemyfollow(void)
{
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	for (int i = 0; i < ENEMYFOLLOW_MAX; i++)
	{
		//use�t���O���I�t�̏ꍇ�̓X�L�b�v����
		if (g_Enemyfollow[i].use == false)
			continue;

		// ���[���h�}�g���b�N�X�̏������i�P�ʍs������֐��j
		D3DXMatrixIdentity(&g_Enemyfollow[i].mtxWorld);

		// �X�P�[���𔽉f
		D3DXMatrixScaling(&mtxScl, g_Enemyfollow[i].scl.x, g_Enemyfollow[i].scl.y, g_Enemyfollow[i].scl.z);
		D3DXMatrixMultiply(&g_Enemyfollow[i].mtxWorld, &g_Enemyfollow[i].mtxWorld, &mtxScl);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemyfollow[i].rot.y, g_Enemyfollow[i].rot.x, g_Enemyfollow[i].rot.z);
		D3DXMatrixMultiply(&g_Enemyfollow[i].mtxWorld, &g_Enemyfollow[i].mtxWorld, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, g_Enemyfollow[i].pos.x, g_Enemyfollow[i].pos.y, g_Enemyfollow[i].pos.z);
		D3DXMatrixMultiply(&g_Enemyfollow[i].mtxWorld, &g_Enemyfollow[i].mtxWorld, &mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		SetWorldMatrix(&g_Enemyfollow[i].mtxWorld);

		//obj���f���̕`��
		DrawModel(&g_Model);
	}
}


//=============================================================================
// �G�l�~�[�����擾
//=============================================================================
ENEMYFOLLOW* GetEnemyfollow(void)
{
	return g_Enemyfollow;
}

void SetEnemyfollow(D3DXVECTOR3 relativePos)
{
	for (int i = 0; i < ENEMYFOLLOW_MAX; i++)
	{
		if (!g_Enemyfollow[i].use)
		{
			g_Enemyfollow[i].relativePos = relativePos;
			g_Enemyfollow[i].pos = GetPlayer()->pos + g_Enemyfollow[i].relativePos;
			g_Enemyfollow[i].use = true;
			D3DXVECTOR3 sPos = g_Enemyfollow[i].pos;
			sPos.y = 0.0f;
			g_Enemyfollow[i].idxShadow = CreateShadow(sPos, 100.0f, 100.0f);
			break;
		}
	}
}

void LevelEnemyfollow(void)
{
	switch (GetCurrentLevel())
	{
	case LEVEL_04:
		SetEnemyfollow(D3DXVECTOR3(100.0f, 0.0f, 100.0f));
		break;
	case LEVEL_05:
		SetEnemyfollow(D3DXVECTOR3(200.0f, 0.0f, 0.0f));
		break;
	case LEVEL_06:
		SetEnemyfollow(D3DXVECTOR3(100.0f, 0.0f, 0.0f));
		SetEnemyfollow(D3DXVECTOR3(0.0f, 0.0f, 100.0f));
		SetEnemyfollow(D3DXVECTOR3(100.0f, 0.0f, 100.0f));
		break;
	case LEVEL_07:
		SetEnemyfollow(D3DXVECTOR3(100.0f, 0.0f, 100.0f));
		break;
	case LEVEL_08:
		SetEnemyfollow(D3DXVECTOR3(100.0f, 0.0f, 100.0f));
		SetEnemyfollow(D3DXVECTOR3(200.0f, 0.0f, 200.0f));
		break;
	case LEVEL_09:
		//SetEnemyfollow(D3DXVECTOR3(0.0f, 0.0f, 100.0f));
		SetEnemyfollow(D3DXVECTOR3(100.0f, 0.0f, 0.0f));
		break;
	case LEVEL_MAX:
		break;
	default:
		break;
	}
}
