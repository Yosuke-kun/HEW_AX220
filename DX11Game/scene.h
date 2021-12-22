//��ʑJ��[scene.h]
#pragma once
#include "main.h"

//�萔��`
enum EScene {
	SCENE_NONE = 0,		//���ݒ�
	SCENE_TITLE,		//�^�C�g�����
	SCENE_GAME,			//�Q�[�����
	SCENE_RESULT,		//���U���g���
	SCENE_SAMPLE,
	SCENE_MAP,
	SCENE_STAGE,
	
	MAX_SCENE			//�V�[������
};

//�֐��v���g�^�C�v
HRESULT InitScene();			//������
void UninitScene();				//�I������
void UpdateScene();				//�X�V
void DrawScene();				//�`��

void SetScene(EScene eScene);	//�؂�ւ�

EScene GetScene();				//�V�[���擾