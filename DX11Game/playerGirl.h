//=============================================================================
//
// �v���C���[���̎q [playerGirl.h]
// ����T�q
//=============================================================================
#pragma once
#include "main.h"
#include "AssimpModel.h"

class Player_Girl {
public:
	Player_Girl();
	~Player_Girl();
	void Update();
	void Draw();

	XMFLOAT3 GetGirlPos();
	XMFLOAT3 GetGirlMove();
	void SetGirlPos(XMFLOAT3);

	bool CheckField();
private:
	CAssimpModel	m_model;	//���f��
	XMFLOAT3		m_pos;		// ���݂̈ʒu
	XMFLOAT3		m_rot;		// ���݂̌���
	XMFLOAT3		m_rotDest;	// �ړI�̌���
	XMFLOAT3		m_move;		// �ړ���
	bool			m_bLand;	// ���n�E�ڒn�t���O

	XMFLOAT4X4		m_mtxWorld;		// ���[���h�}�g���b�N�X

	int				m_nCube;		//�����̔ԍ�
};
