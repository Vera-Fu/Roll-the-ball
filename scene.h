#pragma once

// �o�^�V�[���ꗗ
enum SCENE
{
	SCENE_NONE,		//�V�[�������Ȃ�
	SCENE_TUTORIAL,
	SCENE_TITLE,	//�^�C�g��
	SCENE_LEVEL,
	SCENE_GAME,		//�Q�[��
	SCENE_RESULT,	//���U���g
	SCENE_FINISH,

	SCENE_MAX		//�Ōゾ�Ƃ킩��z�������
};

void InitScene(SCENE index);
void UninitScene(void);
void UpdateScene(void);
void DrawScene(void);

void SetScene(SCENE index);
void CheckScene(void);
