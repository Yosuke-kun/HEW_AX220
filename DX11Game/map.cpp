//=============================================================================
//
// �}�b�v [map.cpp]
// ����T�q
//=============================================================================
#include "map.h"
#include "box.h"
#include "collision.h"


OBJECT_INFO g_oldMap[MAP_HEIGHT][MAP_WIDTH] =
{
	{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},},
	{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},},
	{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},},
	{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{3,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},},
	{{0,0},{0,0},{2,0},{3,0},{0,0},{1,0},{0,0},{2,0},{0,0},{0,0},{0,0},{0,0},{3,0},{0,0},{1,0},{0,0},{0,0},{0,0},{0,0},},
};

OBJECT_INFO g_nowMap[MAP_HEIGHT][MAP_WIDTH] =
{
	{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{1,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},},
	{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{1,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},},
	{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{1,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},},
	{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{3,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},},
	{{0,0},{0,0},{2,0},{3,0},{0,0},{0,0},{0,0},{2,0},{0,0},{0,0},{0,0},{0,0},{3,0},{0,0},{1,0},{0,0},{0,0},{0,0},{0,0},},
};

// �v���g�^�C�v�錾
OBJECT_INFO CollisionBox(XMFLOAT2, XMFLOAT2, OBJECT_INFO);

static Box* g_pBox;

//=============================
//		������
//=============================
HRESULT InitMap() {
	g_pBox = new Box;
	for (int i = 0; i < MAP_HEIGHT; ++i) {
		for (int j = 0; j < MAP_WIDTH; ++j) {
			switch (g_oldMap[i][j].m_nCategory) {
			case 0:
				g_oldMap[i][j].m_bOnBox = false;
				break;
			case NORMAL:
				g_oldMap[i][j].m_nObject = g_pBox->Create(XMFLOAT3(-90.0f+ j * 10.0f, -10 - i * 10.0f,0.0f), g_oldMap[i][j].m_nCategory);
				g_oldMap[i][j].m_bOnBox = false;
				break;
			case BREAK:
				g_oldMap[i][j].m_nObject = g_pBox->Create(XMFLOAT3(-90.0f + j * 10.0f, -10 - i * 10.0f, 0.0f), g_oldMap[i][j].m_nCategory);
				g_oldMap[i][j].m_bOnBox = false;
				break;
			case CARRY:
				g_oldMap[i][j].m_nObject = g_pBox->Create(XMFLOAT3(-90.0f + j * 10.0f, -10 - i * 10.0f, 0.0f), g_oldMap[i][j].m_nCategory);
				g_oldMap[i][j].m_bOnBox = false;
				break;
			}
			switch (g_nowMap[i][j].m_nCategory) {
			case 0:
				g_nowMap[i][j].m_bOnBox = false;
				break;
			case NORMAL:
				g_nowMap[i][j].m_nObject = g_pBox->Create(XMFLOAT3(-90.0f + j * 10.0f, -10 - i * 10.0f, 0.0f), g_nowMap[i][j].m_nCategory);
				g_nowMap[i][j].m_bOnBox = false;
				break;
			case BREAK:
				g_nowMap[i][j].m_nObject = g_pBox->Create(XMFLOAT3(-90.0f + j * 10.0f, -10 - i * 10.0f, 0.0f), g_nowMap[i][j].m_nCategory);
				g_nowMap[i][j].m_bOnBox = false;
			case CARRY:
				g_nowMap[i][j].m_nObject = g_pBox->Create(XMFLOAT3(-90.0f + j * 10.0f, -10 - i * 10.0f, 0.0f), g_nowMap[i][j].m_nCategory);
				g_nowMap[i][j].m_bOnBox = false;
				break;
			}
		}
	}
	return true;
}

//=============================
//		�I��
//=============================
void UninitMap() {
	for (int i = 0; i < MAP_HEIGHT; ++i) {
		for (int j = 0; j < MAP_WIDTH; ++j) {
			switch (g_oldMap[i][j].m_nCategory) {
			case 0:
				break;
			case NORMAL:
				g_pBox->Release(g_oldMap[i][j].m_nObject);
				break;
			case BREAK:
				g_pBox->Release(g_oldMap[i][j].m_nObject);
				break;
			case CARRY:
				g_pBox->Release(g_oldMap[i][j].m_nObject);
				break;
			}
			switch (g_nowMap[i][j].m_nCategory) {
			case 0:
				break;
			case NORMAL:
				g_pBox->Release(g_nowMap[i][j].m_nObject);
				break;
			case BREAK:
				g_pBox->Release(g_nowMap[i][j].m_nObject);
				break;
			case CARRY:
				g_pBox->Release(g_nowMap[i][j].m_nObject);
				break;
			}
		}
	}
	delete g_pBox;
}

//=============================
//		�X�V
//=============================
void UpdateMap() {
	g_pBox->Update();
}

//=============================
//		�`��
//=============================
void DrawOldMap() {
	for (int i = 0; i < MAP_HEIGHT; ++i) {
		for (int j = 0; j < MAP_WIDTH; ++j) {
			switch (g_oldMap[i][j].m_nCategory) {
			case 0:
				break;
			case NORMAL:
				g_pBox->Draw(g_oldMap[i][j].m_nObject);
				break;
			case BREAK:
				g_pBox->Draw(g_oldMap[i][j].m_nObject);
				break;
			case CARRY:
				g_pBox->Draw(g_oldMap[i][j].m_nObject);
				break;
			}
		}
	}
}

//=============================
//		�`��
//=============================
void DrawNowMap() {
	for (int i = 0; i < MAP_HEIGHT; ++i) {
		for (int j = 0; j < MAP_WIDTH; ++j) {
			switch (g_nowMap[i][j].m_nCategory) {
			case 0:
				break;
			case NORMAL:
				g_pBox->Draw(g_nowMap[i][j].m_nObject);
				break;
			case BREAK:
				g_pBox->Draw(g_nowMap[i][j].m_nObject);
				break;
			case CARRY:
				g_pBox->Draw(g_nowMap[i][j].m_nObject);
				break;
			}
		}
	}
}

//=============================
//		�����蔻��ߋ�
//=============================
OBJECT_INFO CollisionOldMap(XMFLOAT2 pos, XMFLOAT2 size) {
	XMFLOAT2 BoxPos;
	XMFLOAT2 BoxSize;
	for (int i = 0; i < MAP_HEIGHT; ++i) {
		for (int j = 0; j < MAP_WIDTH; ++j) {
			switch (g_oldMap[i][j].m_nCategory) {
			case 0:
				break;
			case NORMAL:
				//box�Ƃ̓����蔻��
				if (!g_pBox->GetState(g_oldMap[i][j].m_nObject))
				{
					break;
				}
				BoxPos = XMFLOAT2(g_pBox->GetPos(g_oldMap[i][j].m_nObject).x, g_pBox->GetPos(g_oldMap[i][j].m_nObject).y);
				BoxSize = g_pBox->GetSize();
				if (CollisionRect(pos, size, BoxPos, BoxSize))
				{
					if (pos.y >= BoxPos.y + BoxSize.y + 4.0f)
						g_oldMap[i][j].m_bOnBox = true;
					else
						g_oldMap[i][j].m_bOnBox = false;

					return g_oldMap[i][j];
				}
				break;
			case BREAK:
				//box�Ƃ̓����蔻��
				if (!g_pBox->GetState(g_oldMap[i][j].m_nObject))
				{
					break;
				}
				BoxPos = XMFLOAT2(g_pBox->GetPos(g_oldMap[i][j].m_nObject).x, g_pBox->GetPos(g_oldMap[i][j].m_nObject).y);
				BoxSize = g_pBox->GetSize();
				if (CollisionRect(pos, size, BoxPos, BoxSize))
				{
					if (pos.y >= BoxPos.y + BoxSize.y + 4.0f)
						g_oldMap[i][j].m_bOnBox = true;
					else
						g_oldMap[i][j].m_bOnBox = false;

					return g_oldMap[i][j];
				}
				break;
			case CARRY:
				//box�Ƃ̓����蔻��
				if (!g_pBox->GetState(g_oldMap[i][j].m_nObject))
				{
					break;
				}
				BoxPos = XMFLOAT2(g_pBox->GetPos(g_oldMap[i][j].m_nObject).x, g_pBox->GetPos(g_oldMap[i][j].m_nObject).y);
				BoxSize = g_pBox->GetSize();
				if (CollisionRect(pos, size, BoxPos, BoxSize))
				{
					if (pos.y >= BoxPos.y + BoxSize.y + 4.0f)
						g_oldMap[i][j].m_bOnBox = true;
					else
						g_oldMap[i][j].m_bOnBox = false;

					return g_oldMap[i][j];
				}
				break;
			}
		}
	}

	return OBJECT_INFO{-1,-1};
}

//=============================
//		�����蔻�茻��
//=============================
OBJECT_INFO	CollisionNowMap(XMFLOAT2 pos, XMFLOAT2 size) {
	XMFLOAT2 BoxPos;
	XMFLOAT2 BoxSize;
	for (int i = 0; i < MAP_HEIGHT; ++i) {
		for (int j = 0; j < MAP_WIDTH; ++j) {
			switch (g_nowMap[i][j].m_nCategory) {
			case 0:
				break;
			case NORMAL:
				//box�Ƃ̓����蔻��
				if (!g_pBox->GetState(g_nowMap[i][j].m_nObject))
				{
					break;
				}
				BoxPos = XMFLOAT2(g_pBox->GetPos(g_nowMap[i][j].m_nObject).x, g_pBox->GetPos(g_nowMap[i][j].m_nObject).y);
				BoxSize = g_pBox->GetSize();
				if (CollisionRect(pos, size, BoxPos, BoxSize))
				{
					if (pos.y >= BoxPos.y + BoxSize.y + 4.0f)
						g_nowMap[i][j].m_bOnBox = true;
					else
						g_nowMap[i][j].m_bOnBox = false;

					return g_nowMap[i][j];
				}
				break;
			case BREAK:
				//box�Ƃ̓����蔻��
				if (!g_pBox->GetState(g_nowMap[i][j].m_nObject))
				{
					break;
				}
				BoxPos = XMFLOAT2(g_pBox->GetPos(g_nowMap[i][j].m_nObject).x, g_pBox->GetPos(g_nowMap[i][j].m_nObject).y);
				BoxSize = g_pBox->GetSize();
				if (CollisionRect(pos, size, BoxPos, BoxSize))
				{
					if (pos.y >= BoxPos.y + BoxSize.y + 4.0f)
						g_nowMap[i][j].m_bOnBox = true;
					else
						g_nowMap[i][j].m_bOnBox = false;

					return g_nowMap[i][j];
				}
				break;
			case CARRY:
				//box�Ƃ̓����蔻��
				if (!g_pBox->GetState(g_nowMap[i][j].m_nObject))
				{
					break;
				}
				BoxPos = XMFLOAT2(g_pBox->GetPos(g_nowMap[i][j].m_nObject).x, g_pBox->GetPos(g_nowMap[i][j].m_nObject).y);
				BoxSize = g_pBox->GetSize();
				if (CollisionRect(pos, size, BoxPos, BoxSize))
				{
					if (pos.y >= BoxPos.y + BoxSize.y + 4.0f)
						g_nowMap[i][j].m_bOnBox = true;
					else
						g_nowMap[i][j].m_bOnBox = false;

					return g_nowMap[i][j];
				}
				break;
			}
		}
	}
	return OBJECT_INFO{ -1,-1 };
}

//==========================
//		���@�擾
//==========================
Box* GetBox() {
	return g_pBox;
}
//==========================
//		�}�b�v�@�擾
//==========================
OBJECT_INFO* GetMap(int nTime)
{
	switch (nTime)
	{
	case 0:
		return *g_nowMap;
		break;
	case 1:
		return *g_oldMap;
		break;
	}
}