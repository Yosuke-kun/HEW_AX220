//=============================================================================
//
// �}�b�v [map.h]
// ����T�q
//=============================================================================
#pragma once
#include "main.h"
#include "box.h"
//*****�\���̒�`*****
typedef struct {
	int m_nCategory;	//�I�u�W�F�N�g�̎��
	int m_nObject;		//�I�u�W�F�N�g�Ǘ��ԍ�
	bool m_bOnBox;		//��̔���p
}OBJECT_INFO;

//*****�񋓌^*****
// �I�u�W�F�N�g�̎��
enum MAP_OBJECT 
{
	NONE,		// �Ȃɂ��Ȃ�
	NORMAL,		// ��
	BREAK,		// �󂹂锠
	CARRY,		// �^�ׂ锠
	PUSH,		// �����锠
};		

//*****�}�N����`*****
#define MAP_WIDTH	19
#define MAP_HEIGHT	5

HRESULT InitMap();
void UninitMap();
void UpdateMap();
void DrawOldMap();
void DrawNowMap();

OBJECT_INFO CollisionOldMap(XMFLOAT2 pos, XMFLOAT2 size);
OBJECT_INFO	CollisionNowMap(XMFLOAT2 pos, XMFLOAT2 size);

Box* GetBox();
OBJECT_INFO* GetMap(int);
