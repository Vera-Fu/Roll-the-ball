//=============================================================================
//
// �^�C�g����ʏ��� [tutorial.cpp]
// Author : 
//
//=============================================================================
#include "tutorial.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "fade.h"
#include "button.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static int	g_TutorialBGTex = 0;	// �e�N�X�`�����
BUTTON		g_TutorialButton;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitTutorial(void)
{
	//�e�N�X�`������
	g_TutorialBGTex = LoadTexture("data/TEXTURE/Tutorial.png");

	g_TutorialButton.texNo = LoadTexture("data/TEXTURE/Tutorial_Button.png");
	g_TutorialButton.pos = D3DXVECTOR3(SCREEN_WIDTH / 2, 600.0f, 0.0f);
	g_TutorialButton.size = D3DXVECTOR3(320.0f, 80.0f, 0.0f);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTutorial(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTutorial(void)
{
	if (IsMouseLeftTriggered())
	{
		if (CheckIsOnButton(&g_TutorialButton))
		{
			SceneTransition(SCENE_TITLE);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTutorial(void)
{
	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	DrawSpriteLeftTop(g_TutorialBGTex, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);

	if (CheckIsOnButton(&g_TutorialButton))
	{
		DrawSpriteColor(g_TutorialButton.texNo, g_TutorialButton.pos.x, g_TutorialButton.pos.y,
			g_TutorialButton.size.x, g_TutorialButton.size.y, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f));
	}
	else
	{
		DrawSpriteColor(g_TutorialButton.texNo, g_TutorialButton.pos.x, g_TutorialButton.pos.y,
			g_TutorialButton.size.x, g_TutorialButton.size.y, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

