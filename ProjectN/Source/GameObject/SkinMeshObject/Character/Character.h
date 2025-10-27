#pragma once
#include "GameObject/SkinMeshObject/SkinMeshObject.h"
#include "Collision/BoundingSphere/BoundingSphere.h"

/************************************************************
*	�L�����N�^�[�N���X.
**/

class Character
	: public SkinMeshObject
{
public:
	Character();
	virtual ~Character() override;

	virtual void Update() override;
	virtual void Draw() override;
protected:
	D3DXVECTOR3		m_ShotOffset; // �e���ˈʒu�̃I�t�Z�b�g

	//�e�̃N�[���^�C������.
	float m_ShotCoolDown;
	float m_CoolTime;

};