//��ʑJ��[scene.cpp]
#include "scene.h"
#include "fade.h"
#include "sceneSample.h"
#include "sceneTitle.h"
#include "sceneGame.h"
#include "mapselect.h"
#include "stageselect.h"

//�O���[�o���ϐ�
static EScene g_eScene = SCENE_NONE;

//������
HRESULT InitScene() {
	HRESULT hr = S_OK;
	SetScene(SCENE_TITLE);		//�ŏ��̓^�C�g�����
	InitFade();
	return hr;
}

//�I������
void UninitScene() {
	SetScene(SCENE_NONE);		//���݂̉�ʂ��I��
	UninitFade();
}

//�X�V����
void UpdateScene() {
	switch (g_eScene) {
	case SCENE_TITLE:		//�^�C�g�����
		UpdateSceneTitle();
		break;
	case SCENE_MAP:
		UpdateMapSelect();
		break;
	case SCENE_STAGE:
		UpdateStageSelect();
		break;
	case SCENE_GAME:		//�Q�[�����
		UpdateSceneGame();
		break;
	case SCENE_RESULT:	//���U���g���
		//UpdateResult();
		break;
	case SCENE_SAMPLE:	//�T���v���V�[��
		UpdateSceneSample();
		break;
	}
	UpdateFade();
}

//�`�揈��
void DrawScene() {
	switch (g_eScene) {
	case SCENE_TITLE:		//�^�C�g�����
		DrawSceneTitle();
		break;
	case SCENE_GAME:		//�Q�[�����
		DrawSceneGame();
		break;
	case SCENE_RESULT:		//���U���g���
		//DrawResult();
		break;
	case SCENE_SAMPLE:		//�T���v���V�[��
		DrawSceneSample();
		break;
	}

	DrawFade();
}

//�؂�ւ�
void SetScene(EScene eScene) {
	//���݂̉�ʂ��I��
	switch (g_eScene) {
		case SCENE_TITLE:			//�^�C�g�����
			UninitSceneTitle();
			break;
		case SCENE_GAME:			//�Q�[�����
			UninitSceneGame();
			break;
		case SCENE_RESULT:			//���U���g���
			//UninitResult();
			break;
		case SCENE_SAMPLE:			//�T���v���V�[��
			UninitSceneSample();
			break;
	}

	//��ʂ����ւ�
	g_eScene = eScene;
	//���̉�ʂ�������
	switch (g_eScene) {
		case SCENE_TITLE:			//�^�C�g�����
			InitSceneTitle();
			break;
		case SCENE_GAME:			//�Q�[�����
			InitSceneGame();
			break;
		case SCENE_RESULT:			//���U���g���
			//InitResult();
			break;
		case SCENE_SAMPLE:			//�T���v���V�[��
			InitSceneSample();
			break;
	}
}

EScene GetScene() {
	return g_eScene;
}