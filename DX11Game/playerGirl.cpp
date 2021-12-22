//=============================================================================
//
// �v���C���[���̎q [playerGirl.cpp]
// ����T�q
//=============================================================================
#include "playerGirl.h"
#include "playerBoy.h"
#include "sceneGame.h"
#include "input.h"
#include "collision.h"
#include "map.h"

//*****�萔��`*****
#define PLAYER_BOY_MODEL_PATH			"data/model/dog.x"

#define	PLAYER_BOY_VALUE_MOVE	(0.05f)		// �ړ����x
#define	PLAYER_BOY_RATE_MOVE	(0.20f)		// �ړ������W��
#define	PLAYER_BOY_VALUE_ROTATE	(9.0f)		// ��]���x
#define	PLAYER_BOY_RATE_ROTATE	(0.20f)		// ��]�����W��

#define PLAYER_BOY_COLLISION_SIZE_X		4.0f
#define PLAYER_BOY_COLLISION_SIZE_Y		4.0f
#define PLAYER_BOY_COLLISION_SIZE_Z		2.5f

#define PLAYER_BOY_COLLISION_SIZE_RAD	4.0f

#define GRAVITY_GIRL	(2.0f)	// �d��

//*****�O���[�o���ϐ�*****

XMFLOAT3 g_BoyPos; // �j�̎q�̍��W
XMFLOAT3 g_oldGirlPos; // �O�̍��W

//==============================================================
//�ݽ�׸�
//==============================================================
Player_Girl::Player_Girl()
{
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = GetDevice();
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();

	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	m_pos = XMFLOAT3(-100.0f, -45.0f, 0.0f);
	m_move = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_rotDest = XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_BoyPos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_oldGirlPos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_bLand = false;


	// ���f���f�[�^�̓ǂݍ���
	if (!m_model.Load(pDevice, pDeviceContext, PLAYER_BOY_MODEL_PATH)) {
		MessageBoxA(GetMainWnd(), "���f���f�[�^�ǂݍ��݃G���[", "InitModel", MB_OK);
	}

	//m_nCube = GetCube()->Create(XMFLOAT3(0.0f,0.0f,0.0f),XMFLOAT3(5.0f,5.0f,5.0f),m_mtxWorld);
}
//==============================================================
//�޽�׸�
//==============================================================
Player_Girl::~Player_Girl() {
	// ���f���̉��
	m_model.Release();
	//�����̉��
	//GetCube()->Release(m_nCube);
}
//==============================================================
//�X�V
//==============================================================
void Player_Girl::Update() {
	g_oldGirlPos = m_pos;

	// �J�����̌����擾
	XMFLOAT3 rotCamera = CCamera::Get()->GetAngle();
	// �j�̎q�̍��W���擾
	g_BoyPos = GetOld()->GetPlayerBoy()->GetBoyPos();

	// �E�ړ�
	m_move.x -= SinDeg(rotCamera.y - 90.0f) * PLAYER_BOY_VALUE_MOVE;
	m_move.z -= CosDeg(rotCamera.y - 90.0f) * PLAYER_BOY_VALUE_MOVE;

	m_rotDest.y = rotCamera.y - 90.0f;

	// �d��
	m_move.y -= GRAVITY_GIRL;


	// �ړI�̊p�x�܂ł̍���
	float fDiffRotY = m_rotDest.y - m_rot.y;
	if (fDiffRotY >= 180.0f) {
		fDiffRotY -= 360.0f;
	}
	if (fDiffRotY < -180.0f) {
		fDiffRotY += 360.0f;
	}

	// �ړI�̊p�x�܂Ŋ�����������
	m_rot.y += fDiffRotY * PLAYER_BOY_RATE_ROTATE;
	if (m_rot.y >= 180.0f) {
		m_rot.y -= 360.0f;
	}
	if (m_rot.y < -180.0f) {
		m_rot.y += 360.0f;
	}

	// �ʒu�ړ�
	m_pos.x += m_move.x;

	m_pos.y += m_move.y;
	m_pos.z += m_move.z;



	// �ړ��ʂɊ�����������
	m_move.x += (0.0f - m_move.x) * PLAYER_BOY_RATE_MOVE;
	m_move.y += (0.0f - m_move.y) * PLAYER_BOY_RATE_MOVE;
	m_move.z += (0.0f - m_move.z) * PLAYER_BOY_RATE_MOVE;

	if (m_pos.x < -310.0f) {
		m_pos.x = -310.0f;
	}
	if (m_pos.x > 310.0f) {
		m_pos.x = 310.0f;
	}
	if (m_pos.z < -310.0f) {
		m_pos.z = -310.0f;
	}
	if (m_pos.z > 310.0f) {
		m_pos.z = 310.0f;
	}
	if (m_pos.y < -45.0f) {
		m_pos.y = -45.0f;
		m_move.y = 0.0f;
		m_bLand = true;
	}
	if (m_pos.y > 80.0f) {
		m_pos.y = 80.0f;
	}

	// �����蔻��
	OBJECT_INFO collision = CollisionNowMap(XMFLOAT2(m_pos.x, m_pos.y), XMFLOAT2(PLAYER_BOY_COLLISION_SIZE_X, PLAYER_BOY_COLLISION_SIZE_Y));
	if (collision.m_nCategory > 0)
	{
		if (m_bLand == true && collision.m_bOnBox == true)
			m_pos.y = g_oldGirlPos.y;
		else if (m_bLand == true)
			m_pos.x = g_oldGirlPos.x;
	}
	//----�n�`�Ƃ̓����蔻��----
	if (CheckField())
	{	//������ꍇ�̏���
		m_move.y = 0.0f;
		m_bLand = true;
	}
	else
	{
		if (m_bLand)
		{
			m_bLand = false;
		}
	}

	if (GetKeyPress(VK_RETURN)) {
		// ���Z�b�g
		m_pos = XMFLOAT3(-100.0f, -45.0f, 0.0f);
		m_move = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_rotDest = XMFLOAT3(0.0f, 0.0f, 0.0f);
	}

	XMMATRIX mtxWorld, mtxRot, mtxTranslate;

	// ���[���h�}�g���b�N�X�̏�����
	mtxWorld = XMMatrixIdentity();

	// ��]�𔽉f
	mtxRot = XMMatrixRotationRollPitchYaw(XMConvertToRadians(m_rot.x),
		XMConvertToRadians(m_rot.y), XMConvertToRadians(m_rot.z));
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

	// �ړ��𔽉f
	mtxTranslate = XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

	// ���[���h�}�g���b�N�X�ݒ�
	XMStoreFloat4x4(&m_mtxWorld, mtxWorld);

	//�����̈ړ�
	//GetCube()->Move(m_nCube,m_mtxWorld);
	/*�e�X�g*/

	//�����蔻��
}
//==============================================================
//�`��
//==============================================================
void Player_Girl::Draw() {
	ID3D11DeviceContext* pDC = GetDeviceContext();

	// �s����������`��
	m_model.Draw(pDC, m_mtxWorld, eOpacityOnly);

	// ������������`��
	SetBlendState(BS_ALPHABLEND);	// �A���t�@�u�����h�L��
	SetZWrite(false);				// Z�o�b�t�@�X�V���Ȃ�
	m_model.Draw(pDC, m_mtxWorld, eTransparentOnly);
	SetZWrite(true);				// Z�o�b�t�@�X�V����
	SetBlendState(BS_NONE);			// �A���t�@�u�����h����
}

//==============================================================
//���̎q�̈ʒu�擾
//==============================================================
XMFLOAT3 Player_Girl::GetGirlPos()
{
	return m_pos;
}
XMFLOAT3 Player_Girl::GetGirlMove()
{
	return m_move;
}
//==============================================================
//���̎q�̈ʒu�ݒ�
//==============================================================
void Player_Girl::SetGirlPos(XMFLOAT3 pos)
{
	if (m_pos.y < pos.y)	
	{
		m_move.y += GRAVITY_GIRL + 3.0f;
	}
	//m_pos = pos;
}

//==============================================================
//���̎q�̓����蔻��
//==============================================================
bool Player_Girl::CheckField()
{
	Box* pBox = GetBox();
	OBJECT_INFO* pNowMap = GetMap(0);

	XMFLOAT3 boxPos;
	for (int i = 0; i < MAP_HEIGHT * MAP_WIDTH; i++, pNowMap++) {
		switch (pNowMap->m_nCategory) {
		case 0:
			break;
		case NORMAL:
			if (!pBox->GetState(pNowMap->m_nObject))
			{
				break;
			}
			boxPos = pBox->GetPos(pNowMap->m_nObject);
			if (m_pos.x <= boxPos.x - 8.0f) continue;
			if (boxPos.x + 8.0f <= m_pos.x) continue;

			if (m_pos.y >= boxPos.y + 18.0f && g_oldGirlPos.y <= boxPos.y + 18.0f)
			{
				m_pos.y = boxPos.y + 18.0f;
				return true;
			}
			else if (m_pos.y <= boxPos.y - 5.0f && g_oldGirlPos.y >= boxPos.y - 5.0f)
			{
				m_pos.y = boxPos.y - 5.0f;
				m_move.y = 0.0f;
			}
			break;
		case CARRY:
			if (!pBox->GetState(pNowMap->m_nObject))
			{
				break;
			}
			boxPos = pBox->GetPos(pNowMap->m_nObject);
			if (m_pos.x <= boxPos.x - 8.0f) continue;
			if (boxPos.x + 8.0f <= m_pos.x) continue;

			if (m_pos.y >= boxPos.y + 18.0f && g_oldGirlPos.y <= boxPos.y + 18.0f)
			{
				m_pos.y = boxPos.y + 18.0f;
				return true;
			}
			else if (m_pos.y <= boxPos.y - 5.0f && g_oldGirlPos.y >= boxPos.y - 5.0f)
			{
				m_pos.y = boxPos.y - 5.0f;
				m_move.y = 0.0f;
			}
			break;
		}
	}
}