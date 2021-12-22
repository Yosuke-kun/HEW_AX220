//===================================================
//		��[box.cpp]
//����T�q
//=====================================================
#include "box.h"
#include "Texture.h"
#include "Shader.h"
#include "bsphere.h"
#include "sceneGame.h"
#include "map.h"

//*********************************************************
//�}�N����`
//*********************************************************
#define BOX_MODEL_PATH	"data/model/box001.x"

#define BOX_COLLISION_SIZE_X	4.0f
#define BOX_COLLISION_SIZE_Y	4.0f

#define BOY_HUND_LONG			10.0f

//*********************************************************
//�O���[�o���ϐ�
//*********************************************************

//=============================
//		�ݽ�׸�
//=============================
Box::Box(){

	ID3D11Device* pDevice = GetDevice();
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();

	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	for (int i = 0; i < MAX_BOX; ++i) {
		m_box[i].m_pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_box[i].m_oldPos = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_box[i].m_state = true;
		m_box[i].m_use = false;
	}

	// ���f���f�[�^�̓ǂݍ���
	if (!m_model.Load(pDevice, pDeviceContext, BOX_MODEL_PATH)) {
		MessageBoxA(GetMainWnd(), "���f���f�[�^�ǂݍ��݃G���[", "InitModel", MB_OK);
	}

}

//=============================
//		�޽�׸�
//=============================
Box::~Box() {
	// ���f���̉��
	m_model.Release();
}
//=============================
//		�X�V
//=============================
void Box::Update() {
	XMMATRIX mtxWorld,mtxTranslate;

	for (int i = 0; i < MAX_BOX; ++i) 
	{
		//���g�p�Ȃ�X�L�b�v
		if (!m_box[i].m_use) {
			continue;
		}
		// ���[���h�}�g���b�N�X�̏�����
		mtxWorld = XMMatrixIdentity();
		// �ړ��𔽉f
		mtxTranslate = XMMatrixTranslation(m_box[i].m_pos.x, m_box[i].m_pos.y, m_box[i].m_pos.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

		// ���[���h�}�g���b�N�X�ݒ�
		XMStoreFloat4x4(&m_box[i].m_mtxWorld, mtxWorld);


	}
	
}

//=============================
//		�`��
//=============================
void Box::Draw() {
	ID3D11DeviceContext* pDC = GetDeviceContext();

	for (int i = 0; i < MAX_BOX; ++i)
	{
		//���g�p�Ȃ�X�L�b�v
		if (!m_box[i].m_use) {
			continue;
		}

		// �s����������`��
		m_model.Draw(pDC, m_box[i].m_mtxWorld, eOpacityOnly);

		// ������������`��
		SetBlendState(BS_ALPHABLEND);	// �A���t�@�u�����h�L��
		SetZWrite(false);				// Z�o�b�t�@�X�V���Ȃ�
		m_model.Draw(pDC, m_box[i].m_mtxWorld, eTransparentOnly);
		SetZWrite(true);				// Z�o�b�t�@�X�V����
		SetBlendState(BS_NONE);			// �A���t�@�u�����h����
	}
}

//=============================
//		�`��
//=============================
void Box::Draw(int num) {
	ID3D11DeviceContext* pDC = GetDeviceContext();
		//���g�p�Ȃ�`�悵�Ȃ�
		if (!m_box[num].m_use) {
			return;
		}
		//�j�󂳂�Ă�����`�悵�Ȃ�
		if (!m_box[num].m_state) {
			return;
		}
		// �s����������`��
		m_model.Draw(pDC, m_box[num].m_mtxWorld, eOpacityOnly);

		// ������������`��
		SetBlendState(BS_ALPHABLEND);	// �A���t�@�u�����h�L��
		SetZWrite(false);				// Z�o�b�t�@�X�V���Ȃ�
		m_model.Draw(pDC, m_box[num].m_mtxWorld, eTransparentOnly);
		SetZWrite(true);				// Z�o�b�t�@�X�V����
		SetBlendState(BS_NONE);			// �A���t�@�u�����h����
}

//=============================
//	������ ���� : ���f�����W�A�T�C�Y�A���[���h�}�g���b�N�X
//=============================
int Box::Create(XMFLOAT3 pos, int nCat) {
	TBox* pBox = m_box;
	for (int i = 0; i < MAX_BOX; ++i, ++pBox) {
		if (pBox->m_use) continue;
		pBox->m_pos = pos;
		pBox->m_oldPos = pos;
		pBox->m_state = true;
		pBox->m_use = true;
		pBox->m_nCat = nCat;

		return i;
	}
	return -1;
}

//=============================
//	�����	���� :�L���[�u�ԍ�
//=============================
void Box::Release(int num) {
	if (num < 0 || num >= MAX_BOX)
		return;
	m_box[num].m_use = false;
}

//=============================
//	���@�j��
//=============================
bool Box::Destroy(int num) {
	if (num < 0 || num >= MAX_BOX)
		return false;
	if (!m_box[num].m_nCat == CARRY)
		return false;
	m_box[num].m_state = false;
	return true;
}

//=============================
//	���̏��@�擾
//=============================
TBox* Box::GetBox()
{
	return m_box;
}

//=============================
//	���@���W�擾
//=============================
XMFLOAT3 Box::GetPos(int num) {
	return m_box[num].m_pos;
}

//=============================
//	���@���W�ݒ�
//=============================
void Box::SetBoxPos(int num, XMFLOAT3 pos,int time) {
	XMFLOAT3 boyPos = GetOld()->GetBoyPos();
	if (!m_box[num].m_nCat == CARRY)	// ������NORMAL�ɂ��Ă���܂�(�{���Ȃ�MOVE)
		return;

	// �ߋ��p
	if (time == 0){
		if (pos.x > 0.0f)
			m_box[num].m_pos.x = boyPos.x + BOY_HUND_LONG;
		else if (pos.x < 0.0f)
			m_box[num].m_pos.x = boyPos.x - BOY_HUND_LONG;

		if (!(boyPos.y - m_box[num].m_pos.y >= BOY_HUND_LONG || boyPos.y - m_box[num].m_pos.y <= -BOY_HUND_LONG))
			m_box[num].m_pos.y += pos.y;
		if (!(boyPos.z - m_box[num].m_pos.z >= BOY_HUND_LONG || boyPos.y - m_box[num].m_pos.z <= -BOY_HUND_LONG))
			m_box[num].m_pos.z += pos.z;
	}
	// �����p
	if (time == 1) {
		if (pos.x > 0.0f)
			m_box[num].m_oldPos.x = boyPos.x + BOY_HUND_LONG;
		else if (pos.x < 0.0f)
			m_box[num].m_oldPos.x = boyPos.x - BOY_HUND_LONG;

		if (!(boyPos.y - m_box[num].m_oldPos.y >= BOY_HUND_LONG || boyPos.y - m_box[num].m_oldPos.y <= -BOY_HUND_LONG))
			m_box[num].m_oldPos.y += pos.y;
		if (!(boyPos.z - m_box[num].m_oldPos.z >= BOY_HUND_LONG || boyPos.y - m_box[num].m_oldPos.z <= -BOY_HUND_LONG))
			m_box[num].m_oldPos.z += pos.z;
	}
#ifndef TAKEI_HARUTO
	PrintDebugProc("ο�ݻ�ˮ�x:%2f,y:%2f,z:%2f\n", m_box[num].m_pos.x, m_box[num].m_pos.y, m_box[num].m_pos.z);
	PrintDebugProc("�ݴ���ˮ�x:%2f,y:%2f,z:%2f\n", 
		m_box[num].m_oldPos.x, m_box[num].m_oldPos.y, m_box[num].m_oldPos.z);
#endif
}

//=============================
//	���@���W���f
//=============================
void Box::SetOldBoxPos(int num) {
	if (!m_box[num].m_nCat == CARRY)	// ������NORMAL�ɂ��Ă���܂�(�{���Ȃ�MOVE)
		return;

	m_box[num].m_pos.x = m_box[num].m_oldPos.x;
	m_box[num].m_pos.y = m_box[num].m_oldPos.y;
	m_box[num].m_pos.z = m_box[num].m_oldPos.z;

}

//=============================
//	���@�T�C�Y�擾
//=============================
XMFLOAT2 Box::GetSize() {
	return XMFLOAT2(BOX_COLLISION_SIZE_X, BOX_COLLISION_SIZE_Y);
}

//=============================
//	���@��Ԏ擾
//=============================
bool Box::GetState(int num) {
	return m_box[num].m_state;
}

//===============================================
//		���Ɖߋ��𕪂����`��(0�����A1���ߋ�)
//===============================================
void Box::DrawOldNow(int nTime) {
	ID3D11DeviceContext* pDC = GetDeviceContext();

	for (int i = 0; i < MAX_BOX; ++i)
	{
		if (!m_box[i].m_use) {
			continue;
		}
		if (!m_box[i].m_nTime == nTime)
		{
			continue;
		}
		// �s����������`��
		m_model.Draw(pDC, m_box[i].m_mtxWorld, eOpacityOnly);

		// ������������`��
		SetBlendState(BS_ALPHABLEND);	// �A���t�@�u�����h�L��
		SetZWrite(false);				// Z�o�b�t�@�X�V���Ȃ�
		m_model.Draw(pDC, m_box[i].m_mtxWorld, eTransparentOnly);
		SetZWrite(true);				// Z�o�b�t�@�X�V����
		SetBlendState(BS_NONE);			// �A���t�@�u�����h����
	}
}

//=======================================
//	�L���[�u����(0�����A1���ߋ�)
//=======================================
int Box::CreateOldNow(XMFLOAT3 pos, int nTime) {
	TBox* pBox = m_box;
	for (int i = 0; i < MAX_BOX; ++i, ++pBox) {
		if (pBox->m_use) continue;
		pBox->m_pos = pos;
		pBox->m_oldPos = pos;
		pBox->m_state = true;
		pBox->m_use = true;
		pBox->m_nTime = nTime;
		return i;
	}
	return -1;
}