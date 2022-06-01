//=============================================================================
//
// �e���� [bullet.cpp]
// Author : 
//
//=============================================================================
#include "bullet.h"
#include "camera.h"
#include "texture.h"
#include "level.h"
#include "player.h"
#include "sprite.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer		*g_VertexBuffer = NULL;	// ���_�o�b�t�@

static BULLET		g_Bullet[BULLET_MAX];	// �e�f�[�^
static MATERIAL		g_Material;
static int			g_texNo = 0;
static int			g_BulletTutorialTimer;
static int			g_BulletTutorialTex = 0;


//=============================================================================
// ����������
//=============================================================================
void InitBullet(void)
{
	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);


	// ���_�o�b�t�@�ɒl���Z�b�g����
	{
		D3D11_MAPPED_SUBRESOURCE msr;
		GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		// ���_���W�̐ݒ�
		vertex[0].Position = D3DXVECTOR3(-BULLET_SIZE / 2.0f, 0.0f, 0.0f);
		vertex[1].Position = D3DXVECTOR3(-BULLET_SIZE / 2.0f, BULLET_SIZE, 0.0f);
		vertex[2].Position = D3DXVECTOR3(BULLET_SIZE / 2.0f, 0.0f, 0.0f);
		vertex[3].Position = D3DXVECTOR3(BULLET_SIZE / 2.0f, BULLET_SIZE, 0.0f);

		// ���_�J���[�̐ݒ�
		vertex[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		vertex[0].TexCoord = D3DXVECTOR2(0.0f, 1.0f);
		vertex[1].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
		vertex[2].TexCoord = D3DXVECTOR2(1.0f, 1.0f);
		vertex[3].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

		GetDeviceContext()->Unmap(g_VertexBuffer, 0);
	}

	// �e�N�X�`������
	g_texNo = LoadTexture("data/TEXTURE/Bullet.png");
	g_BulletTutorialTex = LoadTexture("data/TEXTURE/Bullet_Tutorial.png");

	// �}�e���A��������
	ZeroMemory(&g_Material, sizeof(g_Material));
	g_Material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ������
	for(int i = 0; i < BULLET_MAX; i++)
	{
		g_Bullet[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bullet[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bullet[i].size = D3DXVECTOR3(BULLET_SIZE, BULLET_SIZE, BULLET_SIZE);
		g_Bullet[i].use = false;
		g_Bullet[i].getable = false;
	}

	g_BulletTutorialTimer = 0;

	SetGetableBullet();
}

//=============================================================================
// �I������
//=============================================================================
void UninitBullet(void)
{
	if(g_VertexBuffer != NULL)
	{// ���_�o�b�t�@�̉��
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBullet(void)
{
	for(int i = 0; i < BULLET_MAX; i++)
	{
		if(g_Bullet[i].use && !g_Bullet[i].getable)
		{
			//���ŏ���
			if (g_Bullet[i].frame > 100.0f)
			{
				g_Bullet[i].use = false;
			}

			//���W�̍X�V
			g_Bullet[i].pos += g_Bullet[i].move;

			//���Ԍo��
			g_Bullet[i].frame += 1.0f;

		}
	}
	g_BulletTutorialTimer++;
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBullet(void)
{
	// ���e�X�g��L����
	SetAlphaTestEnable(true);

	// ���C�e�B���O�𖳌�
	SetLightEnable(false);

	D3DXMATRIX mtxView, mtxScale, mtxTranslate;

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	for(int i = 0; i < BULLET_MAX; i++)
	{
		if(g_Bullet[i].use)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Bullet[i].mtxWorld);

			CAMERA *cam = GetCamera();

			// �|���S���𐳖ʂɌ�����
#if 0
			// �r���[�}�g���b�N�X�̋t�s����擾
			g_Bullet[i].mtxWorld = cam->mtxInvView;
			g_Bullet[i].mtxWorld._41 = 0.0f;
			g_Bullet[i].mtxWorld._42 = 0.0f;
			g_Bullet[i].mtxWorld._43 = 0.0f;
#else
			// �r���[�}�g���b�N�X���擾
			D3DXMATRIX mtxView = cam->mtxView;

			g_Bullet[i].mtxWorld._11 = mtxView._11;
			g_Bullet[i].mtxWorld._12 = mtxView._21;
			g_Bullet[i].mtxWorld._13 = mtxView._31;
			g_Bullet[i].mtxWorld._21 = mtxView._12;
			g_Bullet[i].mtxWorld._22 = mtxView._22;
			g_Bullet[i].mtxWorld._23 = mtxView._32;
			g_Bullet[i].mtxWorld._31 = mtxView._13;
			g_Bullet[i].mtxWorld._32 = mtxView._23;
			g_Bullet[i].mtxWorld._33 = mtxView._33;
#endif


			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, g_Bullet[i].pos.x,
												 g_Bullet[i].pos.y,
												 g_Bullet[i].pos.z);
			D3DXMatrixMultiply(&g_Bullet[i].mtxWorld, &g_Bullet[i].mtxWorld, &mtxTranslate);


			// ���[���h�}�g���b�N�X�̐ݒ�
			SetWorldMatrix(&g_Bullet[i].mtxWorld);

			// �}�e���A���ݒ�
			SetMaterial(g_Material);

			// �e�N�X�`���ݒ�
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_texNo));

			// �|���S���̕`��
			GetDeviceContext()->Draw(4, 0);
		}
	}

	// ���C�e�B���O��L����
	SetLightEnable(true);

	// ���e�X�g�𖳌���
	SetAlphaTestEnable(false);

	for (int i = 0; i < GetPlayer()->bulletNum; i++)
	{
		DrawSprite(g_texNo, 1200.0f - 50.0f * i, SCREEN_HEIGHT - 50.0f, 50.0f, 50.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	}
	if (g_BulletTutorialTimer < 300 && GetCurrentLevel() == LEVEL_06)
	{
		DrawSpriteLeftTop(g_BulletTutorialTex, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);
	}
}


//=============================================================================
// �e�̃p�����[�^���Z�b�g
//=============================================================================
void SetBullet(D3DXVECTOR3 pos, bool getable)
{
	for(int i = 0; i < BULLET_MAX; i++)
	{
		//�܂��\������Ă��Ȃ��ꏊ��T��
		if(g_Bullet[i].use == false)
		{
			g_Bullet[i].pos = pos;
			g_Bullet[i].move = D3DXVECTOR3(sinf(GetCamera()->rot.y) * BULLET_SPEED, 0.0f, cosf(GetCamera()->rot.y) * BULLET_SPEED);
			g_Bullet[i].frame = 0.0f;	   
			g_Bullet[i].use = true;
			g_Bullet[i].getable = getable;

			break;
		}
	}
}

BULLET* GetBullet(void)
{
	return &g_Bullet[0];
}

void SetGetableBullet(void)
{
	switch (GetCurrentLevel())
	{
	case LEVEL_06:
		SetBullet(D3DXVECTOR3(100.0f, 25.0f, 0.0f), true);
		break;
	case LEVEL_07:
		SetBullet(D3DXVECTOR3(-300.0f, 25.0f, 200.0f), true);
		SetBullet(D3DXVECTOR3(300.0f, 25.0f, -300.0f), true);
		break;
	case LEVEL_08:
		SetBullet(D3DXVECTOR3(-300.0f, 25.0f, 200.0f), true);
		SetBullet(D3DXVECTOR3(300.0f, 25.0f, -300.0f), true);
		break;
	case LEVEL_09:
		SetBullet(D3DXVECTOR3(-400.0f, 25.0f, 400.0f), true);
		SetBullet(D3DXVECTOR3(-400.0f, 25.0f, 300.0f), true);
		SetBullet(D3DXVECTOR3(-300.0f, 25.0f, 400.0f), true);
		SetBullet(D3DXVECTOR3(-400.0f, 25.0f,  0.0f), true);
		SetBullet(D3DXVECTOR3(400.0f, 25.0f, -400.0f), true);
		SetBullet(D3DXVECTOR3(400.0f, 25.0f, -300.0f), true);
		break;
	case LEVEL_MAX:
		break;
	default:
		break;
	}
}