#pragma once

#include "GameObject/GameObject.h"
#include "Sprite2D/Sprite2D.h"

/************************************************************
*	UI�I�u�W�F�N�g�N���X.
**/
class UIObject : public GameObject
{
public:
	UIObject();
	virtual ~UIObject() override;

	// Update �� Draw�i�����Ȃ��j
	virtual void Update() override;
	virtual void Draw() override final; // �� ������final�w��OK�I

	// �X�v���C�g��ڑ�����
	void AttachSprite(Sprite2D& pSprite) { m_pSprite = &pSprite; }
	void DetachSprite() { m_pSprite = nullptr; }

	// �p�^�[���ԍ���ݒ�
	void SetPatternNo(SHORT x, SHORT y)
	{
		m_PatternNo.x = x;
		m_PatternNo.y = y;
	}

protected:
	Sprite2D* m_pSprite;
	POINTS		m_PatternNo;	// �p�^�[���ԍ�(�}�X��)
};
