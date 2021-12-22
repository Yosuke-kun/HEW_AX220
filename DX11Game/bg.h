// �w�i�`�� [bg.h]
#pragma once
#include "main.h"

//// �֐��v���g�^�C�v
//HRESULT InitBG();	// ������
//void UninitBG();	// �I������
//void UpdateBG();	// �X�V
//void DrawBG();		// �`��


class BG {
public:
	BG();
	 ~BG();
	void Update();
	void Draw();
private:
	XMFLOAT2	m_pos;
	XMFLOAT2	m_pos2;
	XMFLOAT2	m_size;
	ID3D11ShaderResourceView* m_pTexture;
};