#pragma once
#include "GameObject\StaticMeshObject\StaticMeshObject.h"	//���N���X

/******************************************
*	�n�ʃN���X.
**/

class Ground
	: public StaticMeshObject	//�X�^�e�B�b�N���b�V���I�u�W�F�N�g�N���X
{
public:
	Ground();
	virtual ~Ground();

	virtual void Update() override;

private:
};