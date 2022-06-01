//=============================================================================
//
// リザルト画面処理 [result.cpp]
// Author : 
//
//=============================================================================
#include "result.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "fade.h"
#include "button.h"
#include "level.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
#define	RESULTBUTTON_SIZE 70.0f

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static int g_ResultBackgroundTex = 0;	// テクスチャ情報
static int g_ResultPanelTex = 0;
static int g_ResultStarONTex = 0;
static int g_ResultStarOFFTex = 0;
static int g_NewBGM = 0;
static bool g_NewBGMIsPlaying = false;
static int g_FinishedBGM = 0;
static bool g_FinishedBGMIsPlaying = false;

BUTTON g_ResultMenuButton;
BUTTON g_ResultRestartButton;
BUTTON g_ResultNextButton;

LEVEL g_ResultLevel;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitResult(void)
{
	g_ResultBackgroundTex = LoadTexture("data/TEXTURE/Result_BG.png");
	g_ResultPanelTex = LoadTexture("data/TEXTURE/PausePanel.png");
	g_ResultStarONTex = LoadTexture("data/TEXTURE/Star_ON.png");
	g_ResultStarOFFTex = LoadTexture("data/TEXTURE/Star_OFF.png");
	
	g_ResultMenuButton.texNo = LoadTexture("data/TEXTURE/Menu.png");
	g_ResultMenuButton.pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 100.0f, SCREEN_HEIGHT / 2 + 30.0f, 0.0f);
	g_ResultMenuButton.size = D3DXVECTOR3(RESULTBUTTON_SIZE, RESULTBUTTON_SIZE, 0.0f);

	g_ResultRestartButton.texNo = LoadTexture("data/TEXTURE/Restart.png");
	g_ResultRestartButton.pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 30.0f, 0.0f);
	g_ResultRestartButton.size = D3DXVECTOR3(RESULTBUTTON_SIZE, RESULTBUTTON_SIZE, 0.0f);

	g_ResultNextButton.texNo = LoadTexture("data/TEXTURE/Next.png");
	g_ResultNextButton.pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 100.0f, SCREEN_HEIGHT / 2 + 30.0f, 0.0f);
	g_ResultNextButton.size = D3DXVECTOR3(RESULTBUTTON_SIZE, RESULTBUTTON_SIZE, 0.0f);
	
	g_ResultLevel = GetCurrentLevel();

	g_NewBGM = LoadSound("data/BGM/BGM_02.wav");
	g_FinishedBGM = LoadSound("data/BGM/BGM_03.wav");

	if (g_ResultLevel == LEVEL_05 && GetIsLevelFinished(g_ResultLevel) && !g_NewBGMIsPlaying)
	{
		StopSoundAll();
		PlaySound(g_NewBGM, -1);
		g_NewBGMIsPlaying = true;
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitResult(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateResult(void)
{
	if (IsMouseLeftTriggered())
	{
		if (CheckIsOnButton(&g_ResultRestartButton))
		{
			SceneTransition(SCENE_GAME);
		}
		if (CheckIsOnButton(&g_ResultMenuButton))
		{
			SceneTransition(SCENE_LEVEL);
		}	
		if (CheckIsOnButton(&g_ResultNextButton) && GetIsLevelFinished(g_ResultLevel))
		{
			if (g_ResultLevel != LEVEL_MAX - 1)
			{
				SetCurrentLevel(LEVEL(g_ResultLevel + 1));
				SceneTransition(SCENE_GAME);
			}
			else
			{
				SceneTransition(SCENE_FINISH);
				if (!g_FinishedBGMIsPlaying)
				{
					StopSoundAll();
					PlaySound(g_FinishedBGM, -1);
					g_FinishedBGMIsPlaying = true;
				}
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawResult(void)
{
	// １枚のポリゴンの頂点とテクスチャ座標を設定
	DrawSpriteLeftTop(g_ResultBackgroundTex, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);

	DrawSprite(g_ResultPanelTex, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 400.0f, 200.0f,
		0.0f, 0.0f, 1.0f, 1.0f);

	if (CheckIsOnButton(&g_ResultMenuButton))
	{
		DrawSpriteColor(g_ResultMenuButton.texNo, g_ResultMenuButton.pos.x, g_ResultMenuButton.pos.y,
			g_ResultMenuButton.size.x, g_ResultMenuButton.size.y, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f));
	}
	else
	{
		DrawSpriteColor(g_ResultMenuButton.texNo, g_ResultMenuButton.pos.x, g_ResultMenuButton.pos.y,
			g_ResultMenuButton.size.x, g_ResultMenuButton.size.y, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	if (CheckIsOnButton(&g_ResultRestartButton))
	{
		DrawSpriteColor(g_ResultRestartButton.texNo, g_ResultRestartButton.pos.x, g_ResultRestartButton.pos.y,
			g_ResultRestartButton.size.x, g_ResultRestartButton.size.y, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f));
	}
	else
	{
		DrawSpriteColor(g_ResultRestartButton.texNo, g_ResultRestartButton.pos.x, g_ResultRestartButton.pos.y,
			g_ResultRestartButton.size.x, g_ResultRestartButton.size.y, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	if (!GetIsLevelFinished(g_ResultLevel))
	{
		DrawSpriteColor(g_ResultNextButton.texNo, g_ResultNextButton.pos.x, g_ResultNextButton.pos.y,
			g_ResultNextButton.size.x, g_ResultNextButton.size.y, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));

		DrawSprite(g_ResultStarOFFTex, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50.0f, RESULTBUTTON_SIZE, RESULTBUTTON_SIZE, 0.0f, 0.0f, 1.0f, 1.0f);
	}
	else
	{
		if (CheckIsOnButton(&g_ResultNextButton))
		{
			DrawSpriteColor(g_ResultNextButton.texNo, g_ResultNextButton.pos.x, g_ResultNextButton.pos.y,
				g_ResultNextButton.size.x, g_ResultNextButton.size.y, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f));
		}
		else
		{
			DrawSpriteColor(g_ResultNextButton.texNo, g_ResultNextButton.pos.x, g_ResultNextButton.pos.y,
				g_ResultNextButton.size.x, g_ResultNextButton.size.y, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}

		DrawSprite(g_ResultStarONTex, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50.0f, RESULTBUTTON_SIZE, RESULTBUTTON_SIZE, 0.0f, 0.0f, 1.0f, 1.0f);
	}
	
}
