/*==============================================================================

   �V�[���Ǘ� [scene.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/

#include "scene.h"
#include "tutorial.h"
#include "title.h"
#include "level.h"
#include "game.h"
#include "result.h"
#include "finish.h"
#include "fade.h"


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
static SCENE g_SceneIndex = SCENE_NONE;
static SCENE g_SceneNextIndex = g_SceneIndex;


/*------------------------------------------------------------------------------
   �������֐�
------------------------------------------------------------------------------*/
void InitScene(SCENE index)
{
	g_SceneIndex = g_SceneNextIndex = index;

	switch (g_SceneIndex)
	{
	case SCENE_NONE:
		break;

	case SCENE_TUTORIAL:
		InitTutorial();
		break;

	case SCENE_TITLE:
		InitTitle();
		break;

	case SCENE_LEVEL:
		InitLevel();
		break;

	case SCENE_GAME:
		InitGame();
		break;

	case SCENE_RESULT:
		InitResult();
		break;

	case SCENE_FINISH:
		InitFinish();
		break;
	}
}

/*------------------------------------------------------------------------------
   �I������������֐�
------------------------------------------------------------------------------*/
void UninitScene(void)
{
	switch (g_SceneIndex)
	{
	case SCENE_NONE:
		break;

	case SCENE_TUTORIAL:
		UninitTutorial();
		break;

	case SCENE_TITLE:
		UninitTitle();
		break;

	case SCENE_LEVEL:
		UninitLevel();
		break;

	case SCENE_GAME:
		UninitGame();
		break;

	case SCENE_RESULT:
		UninitResult();
		break;

	case SCENE_FINISH:
		UninitFinish();
		break;
	}
}

/*------------------------------------------------------------------------------
   �X�V����������֐�
------------------------------------------------------------------------------*/
void UpdateScene(void)
{
	switch( g_SceneIndex ) 
	{
	case SCENE_NONE:
		break;

	case SCENE_TUTORIAL:
		UpdateTutorial();
		break;

	case SCENE_TITLE:
		UpdateTitle();
		break;

	case SCENE_LEVEL:
		UpdateLevel();
		break;

	case SCENE_GAME:
		UpdateGame();
		break;

	case SCENE_RESULT:
		UpdateResult();
		break;

	case SCENE_FINISH:
		UpdateFinish();
		break;
	}

	UpdateFade();
}

/*------------------------------------------------------------------------------
   �`�揈��������֐�
------------------------------------------------------------------------------*/
void DrawScene(void)
{
	switch( g_SceneIndex )
	{
	case SCENE_NONE:
		break;

	case SCENE_TUTORIAL:
		DrawTutorial();
		break;
		

	case SCENE_TITLE:
		DrawTitle();
		break;

	case SCENE_LEVEL:
		DrawLevel();
		break;

	case SCENE_GAME:
		DrawGame();
		break;

	case SCENE_RESULT:
		DrawResult();
		break;

	case SCENE_FINISH:
		DrawFinish();
		break;
	}

	DrawFade();
}

/*------------------------------------------------------------------------------
   �V�[���J�ڂ�v������֐�
------------------------------------------------------------------------------*/
void SetScene(SCENE index)
{
	//�J�ڐ�V�[����ݒ肷��
	g_SceneNextIndex = index;

	CheckScene();
}

/*------------------------------------------------------------------------------
   �J�ڂ�v��������ꍇ�ɃV�[����؂�ւ���֐�
------------------------------------------------------------------------------*/
void CheckScene(void)
{	
	//���݂̃V�[�����I��������
	UninitScene();

	//�J�ڐ�V�[���̏������������s��
	InitScene(g_SceneNextIndex);
	//���݂̃V�[���ƑJ�ڐ�V�[��������Ă�����
	/*if( g_SceneIndex != g_SceneNextIndex )
	{
		
	}*/
}
