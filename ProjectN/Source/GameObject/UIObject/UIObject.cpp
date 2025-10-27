#include "UIObject.h"

UIObject::UIObject()
	: m_pSprite		( nullptr )
	, m_PatternNo	()
{
}

UIObject::~UIObject()
{
	DetachSprite();
}

void UIObject::Update()
{
	if( m_pSprite == nullptr ){
		return;
	}
}

//�����Ȃ���Draw()�֐�
void UIObject::Draw()
{
	if (m_pSprite == nullptr) {
		return;
	}

	// �`�撼�O�ō��W�E��]�E�X�P�[���𔽉f
	m_pSprite->SetPosition(m_vPosition);
	m_pSprite->SetRotation(m_vRotation);
	m_pSprite->SetScale(m_vScale);

	// �p�^�[���ԍ��ݒ�
	m_pSprite->SetPatternNo(m_PatternNo.x, m_PatternNo.y);

	// �����_�����O
	m_pSprite->Render();
}

