#pragma once
#include "GameObject//SkinMeshObject//Character//Character.h"

/************************************************************************
*	�G�x�[�X�N���X.
*	��������N���X�ɂ��č쐬���Ă����܂�.
**/

class EnemyBase
	: public Character
{
public:
	EnemyBase();
	virtual ~EnemyBase() override;

	virtual void Update() override;
	virtual void Draw() override;

protected:
	//���͂܂��K�v���Ȃ��̂ŏ����Ȃ�.
};