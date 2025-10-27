#pragma once

#include "GameObject\\GameObject.h"
#include "StaticMash\StaticMesh.h"


/************************************************************
*	�X�^�e�B�b�N���b�V���I�u�W�F�N�g�N���X.
*	3DSTG�ł̓��C���̕���.
**/
class StaticMeshObject
	: public GameObject
{
public:
	StaticMeshObject();
	virtual ~StaticMeshObject() override;

	// CGameObject�ŏ������z�֐��̐錾������Ă�̂ł�����Œ�`������.
	virtual void Update() override;
	virtual void Draw() override;

	// ���b�V����ڑ�����. (���Q�Ƃ��󂯎��A���|�C���^�[�ɐݒ�)
	void AttachMesh(StaticMesh& pMesh) {
		m_pMesh = &pMesh;
	}
	// �X�v���C�g��؂藣��.
	void DetachMesh() {
		m_pMesh = nullptr;
	}


protected:
	// ���|�C���^�[�ɖ߂����ƂŁAAttachMesh �̑���G���[���������܂��B
	StaticMesh* m_pMesh;
};