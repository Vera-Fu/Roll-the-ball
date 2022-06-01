//=============================================================================
//
// �|���S���\������ [player.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "player.h"
#include "texture.h"
#include "model.h"
#include "bullet.h"
#include "shadow.h"
#include "fade.h"
#include "sound.h"
#include "level.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	VALUE_MOVE		(6.0f)						// �ړ���
#define	VALUE_ROTATE	(D3DX_PI * 0.04f)			// ��]��
#define VALUE_SPDCOEFFICIENT	(0.03f)


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static DX11_MODEL	g_Model;	// ���f���ǂݍ���
static PLAYER		g_Player;	// �v���C���[���
//static float        g_Rot;	// �L�����N�^�[�̌���	
static int			g_BulletSE = 0;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayer(D3DXVECTOR3 startPos, int bulletNum)
{
	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	g_Player.pos = startPos;
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.scl = D3DXVECTOR3(4.0f, 4.0f, 4.0f);
	g_Player.use = true;
	g_Player.isFreezing = false;

	//�����蔻��p�T�C�Y�̏����ݒ�
	g_Player.size = D3DXVECTOR3(80.0f, 80.0f, 80.0f);

	g_Player.spd = VALUE_MOVE;
	g_Player.rotSpd = VALUE_ROTATE;
	g_Player.spdCoefficient = 0.0f;

	g_Player.bulletNum = bulletNum;

	g_BulletSE = LoadSound("data/SE/Bullet.wav");

	//obj���f���̓ǂݍ���
	if (GetIsLevelFinished(LEVEL(LEVEL_MAX - 1)))
	{
		LoadModel((char*)"data/MODEL/Ball_03.obj", &g_Model);
	}
	else
	{
		LoadModel((char*)"data/MODEL/Ball_01.obj", &g_Model);
	}
	

	//�e�̐ݒ�
	D3DXVECTOR3 sPos = g_Player.pos;
	sPos.y = 0.0f;
	g_Player.idxShadow = CreateShadow(sPos, 100.0f, 100.0f);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
	//obj���f���̉��
	UnloadModel(&g_Model);
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	//�e�̈ʒu�̍X�V
	D3DXVECTOR3 sPos = g_Player.pos;
	sPos.y = g_Player.pos.y - g_Player.size.y / 2;
	SetPositionShadow(g_Player.idxShadow, sPos);

	if (g_Player.isFreezing)
	{	
		if (g_Player.pos.y <= -100.0f)
		{
			SceneTransition(SCENE_GAME);
		}
		return;
	}

	CAMERA *cam = GetCamera();

	//�ړ����x�̌�������
	if (!GetKeyboardPress(DIK_UP) && !GetKeyboardPress(DIK_DOWN) && !GetKeyboardPress(DIK_W) && !GetKeyboardPress(DIK_S))
	{
		if (g_Player.spdCoefficient > 0.0f)
		{
			g_Player.spdCoefficient -= 0.01f;
			if (g_Player.spdCoefficient < 0.0f)
			{
				g_Player.spdCoefficient = 0.0f;
			}
		}
		if (g_Player.spdCoefficient < 0.0f)
		{
			g_Player.spdCoefficient += 0.01f;
			if (g_Player.spdCoefficient > 0.0f)
			{
				g_Player.spdCoefficient = 0.0f;
			}
		}
	}	

	if (GetKeyboardPress(DIK_UP) || GetKeyboardPress(DIK_W))
	{
		g_Player.spdCoefficient += VALUE_SPDCOEFFICIENT;
	}
	if (GetKeyboardPress(DIK_DOWN) || GetKeyboardPress(DIK_S))
	{
		g_Player.spdCoefficient -= VALUE_SPDCOEFFICIENT;
	}

	if (g_Player.spdCoefficient > 1.0f)
	{
		g_Player.spdCoefficient = 1.0f;
	}
	if (g_Player.spdCoefficient < -1.0f)
	{
		g_Player.spdCoefficient = -1.0f;
	}

	{	// �����������Ƀv���C���[���ړ�������
		// �����������Ƀv���C���[���������Ă��鏊
		g_Player.rot.y = cam->rot.y;

		g_Player.rot.x += g_Player.rotSpd * g_Player.spdCoefficient;

		g_Player.pos.x += sinf(g_Player.rot.y) * g_Player.spd * g_Player.spdCoefficient;
		g_Player.pos.z += cosf(g_Player.rot.y) * g_Player.spd * g_Player.spdCoefficient;

	}


	// �e������
	if (GetKeyboardTrigger(DIK_SPACE) && g_Player.bulletNum > 0)
	{
		PlaySound(g_BulletSE, 0);
		SetBullet(g_Player.pos, false);
		g_Player.bulletNum--;
	}	

#ifdef _DEBUG	// �f�o�b�O����\������
	char* str = GetDebugStr();
	sprintf(&str[strlen(str)], " rotX:%.2f rotY:%.2f", g_Player.rot.x, g_Player.rot.y);

#endif
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ���[���h�}�g���b�N�X�̏������i�P�ʍs������֐��j
	D3DXMatrixIdentity(&g_Player.mtxWorld);

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, g_Player.scl.x, g_Player.scl.y, g_Player.scl.z);

	                   //��1���� ��          ��2����      ��    ��3����
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(&g_Player.mtxWorld);

	//�J�����O�Ȃ�
	SetCullingMode(CULL_MODE_NONE);

	//obj���f���̕`��
	DrawModel(&g_Model);

	//�J�����O�����ɖ߂�
	SetCullingMode(CULL_MODE_BACK);	
}


//=============================================================================
// �v���C���[�����擾
//=============================================================================
PLAYER *GetPlayer(void)
{
	return &g_Player;
}

