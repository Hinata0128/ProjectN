#pragma once
#include "GameObject/StaticMeshObject/StaticMeshObject.h"
#include "GameObject//StaticMeshObject//ShotBase//ShotBase.h"

class StaticMeshManager;

/******************************************************************
*	�V���b�g�N���X.
**/

class PShot
	: public ShotBase
{
public:
	PShot();
	~PShot() override;

	void Update() override;
	void Draw() override;

	//�e�̏�����.
	void Init();

	// ShotBase �ŏ������z�ɂ��� Reload ������
	void Reload(const D3DXVECTOR3& pos, const D3DXVECTOR3& direction, float speed) override;

private:
};