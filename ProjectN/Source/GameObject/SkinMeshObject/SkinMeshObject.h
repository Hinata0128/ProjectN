#pragma once

#include "GameObject/GameObject.h"
#include "SkinMesh/SkinMesh.h"

/************************************************************
*	�X�L�����b�V���I�u�W�F�N�g�N���X.
**/
class SkinMeshObject
	: public GameObject
{
public:
	SkinMeshObject();
	virtual ~SkinMeshObject() override;

	//CGameObject�ŏ������z�֐��̐錾������Ă�̂ł�����Œ�`������.
	virtual void Update() override;
	virtual void Draw() override;

	//���b�V����ڑ�����.
	void AttachMesh(std::shared_ptr<SkinMesh> pMesh);
	//���b�V����؂藣��.
	void DetachMesh();

public:
	//�Z�b�g�E�Q�b�g�֐�.
	//�A�j���[�V�����̍Đ��p�Z�b�g�֐�.
	void SetIsLoop(const bool& IsLoop);
protected:
	//SkinMesh*					m_pMesh;
	std::shared_ptr<SkinMesh> m_pMesh;
	LPD3DXANIMATIONCONTROLLER	m_pAnimCtrl;	//�A�j���[�V�����R���g���[��

	int				m_AnimNo;			//�A�j���[�V�����ԍ�
	double			m_AnimTime;			//�A�j���[�V�����o�ߎ���
	double			m_AnimSpeed;		//�A�j���[�V�������x
	D3DXVECTOR3		m_BonePos;			//�{�[�����W

	bool			m_Loop;	//�A�j���[�V�����̃��[�v�Đ�.
};
