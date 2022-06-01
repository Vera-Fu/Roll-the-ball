#pragma once

// 登録シーン一覧
enum SCENE
{
	SCENE_NONE,		//シーン処理なし
	SCENE_TUTORIAL,
	SCENE_TITLE,	//タイトル
	SCENE_LEVEL,
	SCENE_GAME,		//ゲーム
	SCENE_RESULT,	//リザルト
	SCENE_FINISH,

	SCENE_MAX		//最後だとわかる奴をいれる
};

void InitScene(SCENE index);
void UninitScene(void);
void UpdateScene(void);
void DrawScene(void);

void SetScene(SCENE index);
void CheckScene(void);
