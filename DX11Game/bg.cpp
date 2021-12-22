// �w�i [bg.cpp]
#include "bg.h"
#include "scene.h"
#include "Texture.h"
#include "polygon.h"

// �}�N����`
#define BG_TEXTURE_PATH_SAMPLE	L"data/texture/sky001.jpg"
#define BG_TEXTURE_PATH_TITLE	L"data/texture/field000.jpg"
#define BG_TEXTURE_PATH_GAME	L"data/texture/�_�a.jpg"
#define BG_POS_X		0.0f
#define BG_POS_Y		0.0f
#define BG_SIZE_X		SCREEN_WIDTH
#define BG_SIZE_Y		SCREEN_HEIGHT

#define BG_SCROLL_SPEED	(0.5f)

//// �O���[�o���ϐ�
//static ID3D11ShaderResourceView* g_pTexture;
//
//// ������
//HRESULT InitBG()
//{
//	HRESULT hr = S_OK;
//	ID3D11Device* pDevice = GetDevice();
//
//	// �e�N�X�`���Ǎ�
//	hr = CreateTextureFromFile(pDevice, PATH_BGTEXTURE, &g_pTexture);
//
//	return hr;
//}
//
//// �I������
//void UninitBG()
//{
//	// �w�i�e�N�X�`�����
//	SAFE_RELEASE(g_pTexture);
//}
//
//// �X�V
//void UpdateBG()
//{
//	// �������Ȃ�
//}
//
//// �`��
//void DrawBG()
//{
//	ID3D11DeviceContext* pDC = GetDeviceContext();
//	SetPolygonSize(BG_WIDTH, BG_HEIGHT);
//	SetPolygonPos(BG_POS_X, BG_POS_Y);
//	SetPolygonTexture(g_pTexture);
//	SetPolygonUV(0.0f, 0.0f);
//	DrawPolygon(pDC);
//}


//==============================================================
//�ݽ�׸�
//==============================================================
BG::BG()
	:m_pos(XMFLOAT2(BG_POS_X, BG_POS_Y))
	,m_pos2(XMFLOAT2(BG_SIZE_X, BG_POS_Y))
	,m_size(XMFLOAT2(BG_SIZE_X, BG_SIZE_Y))
{
	//�e�N�X�`���ǂݍ���
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = GetDevice();

	switch (GetScene()) {
	case SCENE_TITLE:
		hr = CreateTextureFromFile(pDevice, BG_TEXTURE_PATH_TITLE, &m_pTexture);
		break;
	case SCENE_GAME:
		hr = CreateTextureFromFile(pDevice, BG_TEXTURE_PATH_GAME, &m_pTexture);
		break;
	case SCENE_RESULT:
		//hr = CreateTextureFromFile(pDevice, BG_TEXTURE_PATH_RESULT, &m_pTexture);
		break;
	case SCENE_SAMPLE:
		hr = CreateTextureFromFile(pDevice, BG_TEXTURE_PATH_SAMPLE, &m_pTexture);
	}
}
//==============================================================
//�޽�׸�
//==============================================================
BG::~BG() {
	//�e�N�X�`�����
	SAFE_RELEASE(m_pTexture);
}
//==============================================================
//�X�V
//==============================================================
void BG::Update() {
	switch (GetScene())
	{
	case SCENE_GAME:
		// �w�i�̍��W�����Z�b�g
		if (m_pos.x <= -BG_SIZE_X)
			m_pos.x = BG_SIZE_X;
		if (m_pos2.x <= -BG_SIZE_X)
			m_pos2.x = BG_SIZE_X;

		m_pos.x -= BG_SCROLL_SPEED;
		m_pos2.x -= BG_SCROLL_SPEED;
		break;
	default:
		break;
	}
}
//==============================================================
//�`��
//==============================================================
void BG::Draw() {
	ID3D11DeviceContext* pDC = GetDeviceContext();
	SetPolygonSize(m_size.x, m_size.y);
	SetPolygonPos(m_pos.x, m_pos.y);
	SetPolygonTexture(m_pTexture);
	SetPolygonUV(0.0f, 0.0f);
	DrawPolygon(pDC);

	if (!GetScene() == SCENE_GAME)
		return;
	SetPolygonSize(m_size.x, m_size.y);
	SetPolygonPos(m_pos2.x, m_pos2.y);
	SetPolygonTexture(m_pTexture);
	SetPolygonUV(0.0f, 0.0f);
	DrawPolygon(pDC);

	//���ɖ߂�
}
