//=============================================================================
//
// �^�C�g����ʏ��� [title.cpp]
// Author : 
//
//=============================================================================
#include "title.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "fade.h"
#include "sound.h"
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
static int	g_TitleBGTex = 0;	// �e�N�X�`�����
BUTTON g_TitleStartButton;
BUTTON g_TitleQuitButton;
static int	g_BGMNo = 0;		// BGM���ʎq
static bool g_TitleBGMIsPlaying = false;


								//=============================================================================
// ����������
//=============================================================================
HRESULT InitTitle(void)
{
	//�e�N�X�`������
	g_TitleBGTex = LoadTexture("data/TEXTURE/Title_BG.png");
	g_TitleStartButton.texNo = LoadTexture("data/TEXTURE/Title_Start.png");
	g_TitleQuitButton.texNo = LoadTexture("data/TEXTURE/Title_Quit.png");

	g_TitleStartButton.pos = D3DXVECTOR3(SCREEN_WIDTH / 2, 400.0f, 0.0f);
	g_TitleQuitButton.pos = D3DXVECTOR3(SCREEN_WIDTH / 2, 600.0f, 0.0f);

	g_TitleStartButton.size = D3DXVECTOR3(320.0f, 80.0f, 0.0f);
	g_TitleQuitButton.size = D3DXVECTOR3(320.0f, 80.0f, 0.0f);

	g_BGMNo = LoadSound("data/BGM/BGM_01.wav");

	if (!g_TitleBGMIsPlaying)
	{
		PlaySound(g_BGMNo, -1);
		g_TitleBGMIsPlaying = true;
	}
	
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTitle(void)
{
	
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTitle(void)
{
	if (IsMouseLeftTriggered())
	{
		if (CheckIsOnButton(&g_TitleStartButton))
		{			
			SceneTransition(SCENE_LEVEL);		
		}
		if (CheckIsOnButton(&g_TitleQuitButton))
		{
			PostQuitMessage(0);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTitle(void)
{
	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	DrawSpriteLeftTop(g_TitleBGTex, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);


	if (CheckIsOnButton(&g_TitleStartButton))
	{
		DrawSpriteColor(g_TitleStartButton.texNo, g_TitleStartButton.pos.x, g_TitleStartButton.pos.y,
			g_TitleStartButton.size.x, g_TitleStartButton.size.y, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f));
	}
	else
	{
		DrawSpriteColor(g_TitleStartButton.texNo, g_TitleStartButton.pos.x, g_TitleStartButton.pos.y,
			g_TitleStartButton.size.x, g_TitleStartButton.size.y, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	
	if (CheckIsOnButton(&g_TitleQuitButton))
	{
		DrawSpriteColor(g_TitleQuitButton.texNo, g_TitleQuitButton.pos.x, g_TitleQuitButton.pos.y,
			g_TitleQuitButton.size.x, g_TitleQuitButton.size.y, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f));
	}
	else
	{
		DrawSpriteColor(g_TitleQuitButton.texNo, g_TitleQuitButton.pos.x, g_TitleQuitButton.pos.y,
			g_TitleQuitButton.size.x, g_TitleQuitButton.size.y, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

}

