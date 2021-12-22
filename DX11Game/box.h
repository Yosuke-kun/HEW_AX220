//===================================================
//		��[box.h]
//����T�q
//=====================================================
#pragma once
#include "main.h"
#include "mesh.h"
#include "AssimpModel.h"


//*****************************************************************************
// �\����
//*****************************************************************************
struct TBox {
	bool		m_use;		// �g�p���Ă��邩�ǂ���
	XMFLOAT3	m_pos;		// ���S���W(���f�����W�n)
	XMFLOAT3    m_oldPos;   // �����ł̃{�b�N�X�𔽉f������O�̍��W(���������Ă���Ƃ��Ɏg�p)
	bool		m_state;	//���	true:�󂳂�ĂȂ�,false:�󂳂�Ă���
	XMFLOAT4X4	m_mtxWorld;	// ���[���h�}�g���b�N�X
	int			m_nTime;	// �����ߋ���
	int			m_nCat;		// ���̎��
};

//*****�}�N����`*****
#define MAX_BOX		(100)

class Box {
public:
	Box();
	~Box();
	void Update();
	void Draw();
	void Draw(int num);

	int Create(XMFLOAT3 pos, int nCat);

	void Release(int num);

	bool Destroy(int num);

	TBox* GetBox();
	XMFLOAT3 GetPos(int num);
	void SetBoxPos(int num, XMFLOAT3 pos,int time);
	void SetOldBoxPos(int num);
	XMFLOAT2 GetSize();

	bool GetState(int num);

	void DrawOldNow(int nTime);
	int CreateOldNow(XMFLOAT3 pos, int nTime);

private:
	CAssimpModel	m_model;	//���f��
	XMFLOAT4X4		m_mtxWorld;		// ���[���h�}�g���b�N�X
	TBox			m_box[MAX_BOX];		//���̏��
};
