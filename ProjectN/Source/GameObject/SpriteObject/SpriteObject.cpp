#include "SpriteObject.h"

SpriteObject::SpriteObject()
	: m_pSprite(nullptr)
{
	D3DXMatrixIdentity(&m_View);
	D3DXMatrixIdentity(&m_Proj);
}

SpriteObject::~SpriteObject()
{
	DetachSprite();
}

void SpriteObject::Update()
{
	if (m_pSprite == nullptr) {
		return;
	}
	// �K�v�Ȃ炱���ɍX�V������ǉ�
}

void SpriteObject::Draw()
{
	if (m_pSprite == nullptr) {
		return;
	}

	// ���W���]���Ȃǂ��X�v���C�g�ɔ��f
	m_pSprite->SetPosition(m_vPosition);
	m_pSprite->SetRotation(m_vRotation);
	m_pSprite->SetScale(m_vScale);

	// �ݒ�ς݂�View�EProj�s����g�p���ĕ`��
	m_pSprite->Render(m_View, m_Proj);
}
