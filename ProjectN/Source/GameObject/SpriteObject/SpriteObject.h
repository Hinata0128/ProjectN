#pragma once

#include "GameObject/GameObject.h"
#include "Sprite3D/Sprite3D.h"

/************************************************************
*	�X�v���C�g�I�u�W�F�N�g�N���X.
**/
class SpriteObject
	: public GameObject
{
public:
	SpriteObject();
	virtual ~SpriteObject() override;

	// GameObject�̏������z�֐����`
	virtual void Update() override;
	// �����Ȃ�Draw�i�I�[�o�[���C�h�j
	virtual void Draw() override;

	// �X�v���C�g��ڑ�����
	void AttachSprite(Sprite3D& pSprite) {
		m_pSprite = &pSprite;
	}
	// �X�v���C�g��؂藣��
	void DetachSprite() {
		m_pSprite = nullptr;
	}

	// �s����O������ݒ�ł���悤�ɂ���
	void SetViewMatrix(const D3DXMATRIX& view) { m_View = view; }
	void SetProjMatrix(const D3DXMATRIX& proj) { m_Proj = proj; }

protected:
	Sprite3D* m_pSprite;
	D3DXMATRIX m_View;
	D3DXMATRIX m_Proj;
};
