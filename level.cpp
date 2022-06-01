#include "level.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "fade.h"
#include "button.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	LEVELBUTTON_SIZE (50.0f)


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static bool g_IsLevelUnlock[LEVEL_MAX] = { false };
static bool g_IsLevelFinished[LEVEL_MAX] = { false };
static LEVEL g_CurrentLevel = LEVEL_01;

static int g_LevelChooseBGTex = 0;
static int g_LevelChooseStarOFFTex = 0;
static int g_LevelChooseStarONTex = 0;
BUTTON g_LevelChooseButton[LEVEL_MAX];
BUTTON g_LevelChooseEndButton;


HRESULT InitLevel(void)
{
	g_IsLevelUnlock[LEVEL_01] = true;
	g_CurrentLevel = GetCurrentLevel();
	g_LevelChooseBGTex = LoadTexture("data/TEXTURE/LevelChooseBackground.png");
	g_LevelChooseStarOFFTex = LoadTexture("data/TEXTURE/Star_OFF.png");
	g_LevelChooseStarONTex = LoadTexture("data/TEXTURE/Star_ON.png");

	g_LevelChooseButton[LEVEL_01].texNo = LoadTexture("data/TEXTURE/Button_01.png");
	g_LevelChooseButton[LEVEL_02].texNo = LoadTexture("data/TEXTURE/Button_02.png");
	g_LevelChooseButton[LEVEL_03].texNo = LoadTexture("data/TEXTURE/Button_03.png");
	g_LevelChooseButton[LEVEL_04].texNo = LoadTexture("data/TEXTURE/Button_04.png");
	g_LevelChooseButton[LEVEL_05].texNo = LoadTexture("data/TEXTURE/Button_05.png");
	g_LevelChooseButton[LEVEL_06].texNo = LoadTexture("data/TEXTURE/Button_06.png");
	g_LevelChooseButton[LEVEL_07].texNo = LoadTexture("data/TEXTURE/Button_07.png");
	g_LevelChooseButton[LEVEL_08].texNo = LoadTexture("data/TEXTURE/Button_08.png");
	g_LevelChooseButton[LEVEL_09].texNo = LoadTexture("data/TEXTURE/Button_09.png");

	g_LevelChooseButton[LEVEL_01].pos = D3DXVECTOR3(640.0f, 680.0f, 0.0f);
	g_LevelChooseButton[LEVEL_02].pos = D3DXVECTOR3(500.0f, 600.0f, 0.0f);
	g_LevelChooseButton[LEVEL_03].pos = D3DXVECTOR3(530.0f, 470.0f, 0.0f);
	g_LevelChooseButton[LEVEL_04].pos = D3DXVECTOR3(670.0f, 370.0f, 0.0f);
	g_LevelChooseButton[LEVEL_05].pos = D3DXVECTOR3(820.0f, 350.0f, 0.0f);
	g_LevelChooseButton[LEVEL_06].pos = D3DXVECTOR3(770.0f, 220.0f, 0.0f);
	g_LevelChooseButton[LEVEL_07].pos = D3DXVECTOR3(600.0f, 230.0f, 0.0f);
	g_LevelChooseButton[LEVEL_08].pos = D3DXVECTOR3(510.0f, 150.0f, 0.0f);
	g_LevelChooseButton[LEVEL_09].pos = D3DXVECTOR3(640.0f, 60.0f, 0.0f);

	g_LevelChooseEndButton.texNo = LoadTexture("data/TEXTURE/End.png");
	g_LevelChooseEndButton.pos = D3DXVECTOR3(920.0f, 40.0f, 0.0f);
	g_LevelChooseEndButton.size = D3DXVECTOR3(LEVELBUTTON_SIZE, LEVELBUTTON_SIZE, 0.0f);

	for (int i = 0; i < LEVEL_MAX; i++)
	{
		g_LevelChooseButton[i].size = D3DXVECTOR3(LEVELBUTTON_SIZE, LEVELBUTTON_SIZE, 0.0f);
		//g_IsLevelUnlock[i] = true;
	}

	return S_OK;
}

void UninitLevel(void)
{

}

void UpdateLevel(void)
{
	if (IsMouseLeftTriggered())
	{
		for (int i = 0; i < LEVEL_MAX; i++)
		{
			if (g_IsLevelUnlock[i] && CheckIsOnButton(&g_LevelChooseButton[i]))
			{
				g_CurrentLevel = LEVEL(i);
				SceneTransition(SCENE_GAME);
				break;
			}
		}

		if (CheckIsOnButton(&g_LevelChooseEndButton))
		{
			SceneTransition(SCENE_TITLE);
		}
	}
}

void DrawLevel(void)
{
	// １枚のポリゴンの頂点とテクスチャ座標を設定
	DrawSpriteLeftTop(g_LevelChooseBGTex, SCREEN_WIDTH / 4, 0.0f, SCREEN_WIDTH / 2, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);

	for (int i = 0; i < LEVEL_MAX; i++)
	{
		if (!g_IsLevelUnlock[i])
		{
			DrawSpriteColor(g_LevelChooseButton[i].texNo,
				g_LevelChooseButton[i].pos.x, g_LevelChooseButton[i].pos.y,
				g_LevelChooseButton[i].size.x, g_LevelChooseButton[i].size.y, 
				0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		}
		else
		{
			if (CheckIsOnButton(&g_LevelChooseButton[i]))
			{
				DrawSpriteColor(g_LevelChooseButton[i].texNo,
					g_LevelChooseButton[i].pos.x, g_LevelChooseButton[i].pos.y,
					g_LevelChooseButton[i].size.x, g_LevelChooseButton[i].size.y,
					0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(0.85f, 0.85f, 0.85f, 1.0f));
			}
			else
			{
				DrawSpriteColor(g_LevelChooseButton[i].texNo,
					g_LevelChooseButton[i].pos.x, g_LevelChooseButton[i].pos.y,
					g_LevelChooseButton[i].size.x, g_LevelChooseButton[i].size.y,
					0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			if (!g_IsLevelFinished[i])
			{
				DrawSprite(g_LevelChooseStarOFFTex,
					g_LevelChooseButton[i].pos.x, g_LevelChooseButton[i].pos.y + 20.0f,
					20.0f, 20.0f, 0.0f, 0.0f, 1.0f, 1.0f);
			}
			else
			{
				DrawSprite(g_LevelChooseStarONTex,
					g_LevelChooseButton[i].pos.x, g_LevelChooseButton[i].pos.y + 20.0f,
					20.0f, 20.0f, 0.0f, 0.0f, 1.0f, 1.0f);
			}
		}		
	}

	if (CheckIsOnButton(&g_LevelChooseEndButton))
	{
		DrawSpriteColor(g_LevelChooseEndButton.texNo,
			g_LevelChooseEndButton.pos.x, g_LevelChooseEndButton.pos.y,
			g_LevelChooseEndButton.size.x, g_LevelChooseEndButton.size.y,
			0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f));
	}
	else
	{
		DrawSpriteColor(g_LevelChooseEndButton.texNo,
			g_LevelChooseEndButton.pos.x, g_LevelChooseEndButton.pos.y,
			g_LevelChooseEndButton.size.x, g_LevelChooseEndButton.size.y,
			0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}
	

LEVEL GetCurrentLevel(void)
{
	return g_CurrentLevel;
}

void UnlockNextLevel(LEVEL currentLevel)
{
	g_IsLevelFinished[currentLevel] = true;
	if (!g_IsLevelUnlock[currentLevel + 1] && (currentLevel != LEVEL_MAX - 1))
	{
		g_IsLevelUnlock[currentLevel + 1] = true;
	}
}

void SetCurrentLevel(LEVEL level)
{
	g_CurrentLevel = level;
}

bool GetIsLevelFinished(LEVEL level)
{
	return g_IsLevelFinished[level];
}