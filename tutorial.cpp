//=============================================================================
//
// タイトル画面処理 [tutorial.cpp]
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
// マクロ定義
//*****************************************************************************



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static int	g_TutorialBGTex = 0;	// テクスチャ情報
BUTTON		g_TutorialButton;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTutorial(void)
{
	//テクスチャ生成
	g_TutorialBGTex = LoadTexture("data/TEXTURE/Tutorial.png");

	g_TutorialButton.texNo = LoadTexture("data/TEXTURE/Tutorial_Button.png");
	g_TutorialButton.pos = D3DXVECTOR3(SCREEN_WIDTH / 2, 600.0f, 0.0f);
	g_TutorialButton.size = D3DXVECTOR3(320.0f, 80.0f, 0.0f);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTutorial(void)
{

}

//=============================================================================
// 更新処理
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
// 描画処理
//=============================================================================
void DrawTutorial(void)
{
	// １枚のポリゴンの頂点とテクスチャ座標を設定
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

