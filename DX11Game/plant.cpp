//=============================================================================
//
// �A�� [plant.cpp]
// Author : �����@��
//
//=============================================================================
#include "plant.h"
#include "collision.h"
#include "playerGirl.h"
#include "sceneGame.h"

// �O���[�o���ϐ�
Player_Girl* g_pPlayerGirl;

Tree::Tree()
{
	m_pBox = new Box;
}
Tree::~Tree()
{
	delete m_pBox;
}
void Tree::Update()
{
	g_pPlayerGirl = GetNow()->GetPlayerGirl();
	if (g_pPlayerGirl->GetGirlPos().x >= m_treePos.x - 3.5f && g_pPlayerGirl->GetGirlPos().x <= m_treePos.x + 3.5f)
		g_pPlayerGirl->SetGirlPos(m_treePos);
	m_pBox->Update();
}
void Tree::OldDraw()
{
	m_pBox->DrawOldNow(1);
}
void Tree::NowDraw()
{
	m_pBox->DrawOldNow(0);
}

// �؂̎��A����(�j�̎q�̍s��)
void Tree::Plant(XMFLOAT3 pos)
{
	pos.x += 2.0f;
	pos.y += -8.0f;
	m_pBox->CreateOldNow(pos, 1);
}

// �؂�������(���ł̕ω�)
void Tree::Grow(XMFLOAT3 pos)
{
	pos.x += 2.0f;
	for (int i = 0; i < 9; i++)
	{
		m_pBox->CreateOldNow(pos, 0);
		pos.y += 10.0f;
	}
	g_pPlayerGirl->SetGirlPos(pos);
	m_treePos = pos;
}