//=============================================================================
//
// �|���S���\������ [skyball.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "skyball.h"
#include "texture.h"
#include "model.h"
#include "light.h"
#include "bullet.h"
#include "shadow.h"
#include "player.h"

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
static SKYBALL			g_Skyball;	// �v���C���[���		
//static float        g_Rot;	// �L�����N�^�[�̌���	

//=============================================================================
// ����������
//=============================================================================
HRESULT InitSkyball(void)
{
	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	g_Skyball.pos = GetPlayer()->pos;
	g_Skyball.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Skyball.scl = D3DXVECTOR3(100.0f, 100.0f, 100.0f);
	g_Skyball.use = true;

	//�����蔻��p�T�C�Y�̏����ݒ�
	g_Skyball.size = D3DXVECTOR3(100.0f, 100.0f, 100.0f);

	//obj���f���̓ǂݍ���
	LoadModel((char*)"data/MODEL/Skyball_01.obj", &g_Model);

	// ���s�����̐ݒ�i���E���Ƃ炷���j
	LIGHT* pLight = NULL;
	pLight = GetLightData(0);
	pLight->Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);// ���̌���
	pLight->Diffuse = D3DXCOLOR(5.0f, 5.0f, 5.0f, 5.0f);	// ���̐F
	pLight->Attenuation = 10.0f;
	pLight->Type = LIGHT_TYPE_DIRECTIONAL;					// ���s����
	pLight->Enable = true;									// ���̃��C�g��ON
	SetLightData(0, pLight);									// ����Őݒ肵�Ă���

	// �_�����̐ݒ�
	pLight = GetLightData(1);
	pLight->Position = D3DXVECTOR4(0.0f, 500.0f, 0.0f, 0.0f);
	pLight->Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);// ���̌���
	pLight->Diffuse = D3DXCOLOR(5.0f, 5.0f, 5.0f, 5.0f);	// ���̐F
	pLight->Attenuation = 10.0f;							// ��������
	pLight->Type = LIGHT_TYPE_POINT;						// ���s����
	pLight->Enable = true;									// ���̃��C�g��ON
	SetLightData(1, pLight);								// ����Őݒ肵�Ă���

	pLight = GetLightData(2);
	pLight->Direction = D3DXVECTOR4(-1.0f, 1.0f, -1.0f, 0.0f);// ���̌���
	pLight->Diffuse = D3DXCOLOR(5.0f, 5.0f, 5.0f, 5.0f);	// ���̐F
	pLight->Attenuation = 10.0f;
	pLight->Type = LIGHT_TYPE_DIRECTIONAL;					// ���s����
	pLight->Enable = true;									// ���̃��C�g��ON
	SetLightData(2, pLight);									// ����Őݒ肵�Ă���

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitSkyball(void)
{
	//obj���f���̉��
	UnloadModel(&g_Model);
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateSkyball(void)
{
	g_Skyball.pos.x = GetPlayer()->pos.x;
	g_Skyball.pos.z = GetPlayer()->pos.z;
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawSkyball(void)
{
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ���[���h�}�g���b�N�X�̏������i�P�ʍs������֐��j
	D3DXMatrixIdentity(&g_Skyball.mtxWorld);

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, g_Skyball.scl.x, g_Skyball.scl.y, g_Skyball.scl.z);

	//��1���� ��          ��2����      ��    ��3����
	D3DXMatrixMultiply(&g_Skyball.mtxWorld, &g_Skyball.mtxWorld, &mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Skyball.rot.y, g_Skyball.rot.x, g_Skyball.rot.z);
	D3DXMatrixMultiply(&g_Skyball.mtxWorld, &g_Skyball.mtxWorld, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, g_Skyball.pos.x, g_Skyball.pos.y, g_Skyball.pos.z);
	D3DXMatrixMultiply(&g_Skyball.mtxWorld, &g_Skyball.mtxWorld, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(&g_Skyball.mtxWorld);

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
SKYBALL* GetSkyball(void)
{
	return &g_Skyball;
}

