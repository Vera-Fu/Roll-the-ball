/*==============================================================================

   �Q�[������ [game.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/

#include "game.h"
#include "main.h"
#include "input.h"
#include "fade.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "meshfield.h"
#include "collision.h"
#include "sound.h"
#include "score.h"
#include "camera.h"
#include "light.h"
#include "shadow.h"
#include "goal.h"
#include "level.h"
#include "skyball.h"
#include "diearea.h"
#include "enemyfollow.h"
#include "pause.h"


/*------------------------------------------------------------------------------
   �萔��`
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   �\���̐錾
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   �v���g�^�C�v�錾
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
   �O���[�o���ϐ��̒�`
------------------------------------------------------------------------------*/
static int g_BGMNo = 0;


/*------------------------------------------------------------------------------
   �������֐�
------------------------------------------------------------------------------*/
void InitGame(void)
{
	// �J�����̏�����
	InitCamera();

	// ���C�g�̏�����
	InitLight();

	// �e�̏�����
	InitShadow();

	//
	InitGameLevel();

	//// �n�ʂ̏�����
	//InitMeshField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10, 10, 100.0f, 100.0f);

	//// 
	//InitGoal(D3DXVECTOR3(450.0f, 50.0f, 450.0f));

	//// �v���C���[�̏�����
	//InitPlayer(D3DXVECTOR3(0.0f, 50.0f, 0.0f));

	//
	InitDiearea();

	//
	InitSkyball();

	// �G�l�~�[�̏�����
	InitEnemy();
	InitEnemyfollow();

	// �e�̏�����
	InitBullet();

	// �X�R�A�̏�����
	InitScore();

	//
	InitPause();

	SetLightEnable(true);
}

/*------------------------------------------------------------------------------
   �I������������֐�
------------------------------------------------------------------------------*/
void UninitGame()
{
	//�������Ƃ͋t���ɏI���������s��
	UninitScore();
	UninitShadow();
	UninitBullet();
	UninitEnemy();
	UninitEnemyfollow();
	UninitPlayer();
	UninitMeshField();
	UninitDiearea();
	UninitGoal();
	UninitSkyball();
	UninitPause();
}

/*------------------------------------------------------------------------------
   �X�V����������֐�
------------------------------------------------------------------------------*/
void UpdateGame(void)
{
	if (!GetIsPause())
	{
		// �J�����X�V
		UpdateCamera();

		// �n�ʂ̍X�V����
		UpdateMeshField();

		//
		UpdateDiearea();

		//
		UpdateGoal();

		// �v���C���[�̍X�V����
		UpdatePlayer();

		//
		UpdateSkyball();

		// �G�l�~�[�̍X�V����
		UpdateEnemy();
		UpdateEnemyfollow();

		// �e�̍X�V����
		UpdateBullet();

		// �e�̍X�V����
		UpdateShadow();

		// �X�R�A�̍X�V����
		UpdateScore();

		// �����蔻��̍X�V����
		UpdateCollision();
	}
	
	UpdatePause();
}

/*------------------------------------------------------------------------------
   �`�揈��������֐�
------------------------------------------------------------------------------*/
void DrawGame(void)
{
	// �v���C���[���_
	D3DXVECTOR3 pos = GetPlayer()->pos;
	pos.y = 0.0f;			// �J����������h�����߂ɃN���A���Ă���
	SetCameraAT(pos);
	SetCamera();

	// �[�x�e�X�g�L��
	SetDepthEnable(true);

	// ���C�e�B���O�L��
	SetLightEnable(true);

	if (GetPlayer()->isFreezing)
	{
		// �e�̕`�揈��
		DrawShadow();

		// �n�ʂ̕`�揈��
		DrawMeshField();
	}
	else
	{
		// �n�ʂ̕`�揈��
		DrawMeshField();

		// �e�̕`�揈��
		DrawShadow();
	}

	//
	DrawDiearea();

	//
	DrawGoal();

	// �G�l�~�[�̕`�揈��
	DrawEnemy();
	DrawEnemyfollow();

	// �v���C���[�̕`�揈��
	DrawPlayer();

	//
	DrawSkyball();

	// �e�̕`�揈��
	DrawBullet();

	// �}�g���N�X�ݒ�
	SetWorldViewProjection2D();//���W��2D�ϊ�

	// 2D�`��Ȃ̂Ő[�x����
	SetDepthEnable(false);

	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);

	// �X�R�A�̕`�揈��
	DrawScore();

	//
	DrawPause();
}

void InitGameLevel(void)
{

	if (GetCurrentLevel() == LEVEL_01)
	{
		// �n�ʂ̏�����
		InitMeshField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3, 3);

		// 
		InitGoal(D3DXVECTOR3(100.0f, 50.0f, 100.0f));

		// �v���C���[�̏�����
		InitPlayer(D3DXVECTOR3(-100.0f, 40.0f, -100.0f), 0);
	}

	if (GetCurrentLevel() == LEVEL_02 || GetCurrentLevel() == LEVEL_03 || GetCurrentLevel() == LEVEL_04 || GetCurrentLevel() == LEVEL_05)
	{
		// �n�ʂ̏�����
		InitMeshField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 5, 5);

		// 
		InitGoal(D3DXVECTOR3(200.0f, 50.0f, 200.0f));

		// �v���C���[�̏�����
		InitPlayer(D3DXVECTOR3(-200.0f, 40.0f, -200.0f), 0);
	}

	if (GetCurrentLevel() == LEVEL_06 || GetCurrentLevel() == LEVEL_07 || GetCurrentLevel() == LEVEL_08)
	{
		// �n�ʂ̏�����
		InitMeshField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 7, 7);

		// 
		InitGoal(D3DXVECTOR3(300.0f, 50.0f, 300.0f));

		// �v���C���[�̏�����
		if (GetCurrentLevel() == LEVEL_06)
		{
			InitPlayer(D3DXVECTOR3(-300.0f, 40.0f, -300.0f), 1);
		}
		else
		{
			InitPlayer(D3DXVECTOR3(-300.0f, 40.0f, -300.0f), 0);
		}
		
	}

	if (GetCurrentLevel() == LEVEL_09)
	{
		// �n�ʂ̏�����
		InitMeshField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 9, 9);

		// 
		InitGoal(D3DXVECTOR3(400.0f, 50.0f, 400.0f));

		// �v���C���[�̏�����
		InitPlayer(D3DXVECTOR3(-400.0f, 40.0f, -400.0f), 0);
	}
	
}

