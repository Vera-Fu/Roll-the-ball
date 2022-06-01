#include "pause.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "fade.h"
#include "button.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	LEVELBUTTON_SIZE (70.0f)


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static bool g_Pause = false;

BUTTON g_PauseButton;
BUTTON g_MenuButton;
BUTTON g_RestartButton;
BUTTON g_CancelButton;

static int g_PausePanelTex = 0;
static int g_PauseBackgroundTex = 0;

HRESULT InitPause(void)
{
	g_Pause = false;

	g_PauseButton.texNo = LoadTexture("data/TEXTURE/Pause.png");
	g_PauseButton.pos = D3DXVECTOR3(1200.0f, 80.0f, 0.0f);
	g_PauseButton.size = D3DXVECTOR3(LEVELBUTTON_SIZE, LEVELBUTTON_SIZE, 0.0f);

	g_MenuButton.texNo = LoadTexture("data/TEXTURE/Menu.png");
	g_MenuButton.pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 60.0f, SCREEN_HEIGHT / 2, 0.0f);
	g_MenuButton.size = D3DXVECTOR3(LEVELBUTTON_SIZE, LEVELBUTTON_SIZE, 0.0f);

	g_RestartButton.texNo = LoadTexture("data/TEXTURE/Restart.png");
	g_RestartButton.pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 60.0f, SCREEN_HEIGHT / 2, 0.0f);
	g_RestartButton.size = D3DXVECTOR3(LEVELBUTTON_SIZE, LEVELBUTTON_SIZE, 0.0f);

	g_CancelButton.texNo = LoadTexture("data/TEXTURE/Cancel.png");
	g_CancelButton.pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 150.0f, SCREEN_HEIGHT / 2 - 50.0f, 0.0f);
	g_CancelButton.size = D3DXVECTOR3(LEVELBUTTON_SIZE / 2, LEVELBUTTON_SIZE / 2, 0.0f);

	g_PausePanelTex = LoadTexture("data/TEXTURE/PausePanel.png");
	g_PauseBackgroundTex = LoadTexture("data/TEXTURE/fade_white.png");

	return S_OK;
}

void UninitPause(void)
{

}

void UpdatePause(void)
{
	if (IsMouseLeftTriggered())
	{
		if (CheckIsOnButton(&g_PauseButton) && !g_Pause)
		{
			g_Pause = true;
		}

		if (g_Pause)
		{
			if (CheckIsOnButton(&g_CancelButton))
			{
				g_Pause = false;
			}
			if (CheckIsOnButton(&g_RestartButton))
			{
				SceneTransition(SCENE_GAME);
			}
			if (CheckIsOnButton(&g_MenuButton))
			{
				SceneTransition(SCENE_LEVEL);
			}
		}
	}

}

void DrawPause(void)
{
	if (CheckIsOnButton(&g_PauseButton))
	{
		DrawSpriteColor(g_PauseButton.texNo, g_PauseButton.pos.x, g_PauseButton.pos.y,
			g_PauseButton.size.x, g_PauseButton.size.y, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f));
	}
	else
	{
		DrawSpriteColor(g_PauseButton.texNo, g_PauseButton.pos.x, g_PauseButton.pos.y,
			g_PauseButton.size.x, g_PauseButton.size.y, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	if (g_Pause)
	{
		DrawSpriteColor(g_PauseBackgroundTex, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT,
			0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

		DrawSprite(g_PausePanelTex, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 300.0f, 100.0f,
			0.0f, 0.0f, 1.0f, 1.0f);

		if (CheckIsOnButton(&g_CancelButton))
		{
			DrawSpriteColor(g_CancelButton.texNo, g_CancelButton.pos.x, g_CancelButton.pos.y,
				g_CancelButton.size.x, g_CancelButton.size.y, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f));
		}
		else
		{
			DrawSpriteColor(g_CancelButton.texNo, g_CancelButton.pos.x, g_CancelButton.pos.y,
				g_CancelButton.size.x, g_CancelButton.size.y, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}

		if (CheckIsOnButton(&g_RestartButton))
		{
			DrawSpriteColor(g_RestartButton.texNo, g_RestartButton.pos.x, g_RestartButton.pos.y,
				g_RestartButton.size.x, g_RestartButton.size.y, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f));
		}
		else
		{
			DrawSpriteColor(g_RestartButton.texNo, g_RestartButton.pos.x, g_RestartButton.pos.y,
				g_RestartButton.size.x, g_RestartButton.size.y, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}

		if (CheckIsOnButton(&g_MenuButton))
		{
			DrawSpriteColor(g_MenuButton.texNo, g_MenuButton.pos.x, g_MenuButton.pos.y,
				g_MenuButton.size.x, g_MenuButton.size.y, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f));
		}
		else
		{
			DrawSpriteColor(g_MenuButton.texNo, g_MenuButton.pos.x, g_MenuButton.pos.y,
				g_MenuButton.size.x, g_MenuButton.size.y, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}	
}


bool GetIsPause(void)
{
	return g_Pause;
}