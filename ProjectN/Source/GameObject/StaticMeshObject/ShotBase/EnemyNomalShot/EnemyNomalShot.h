#pragma once
#include "GameObject//StaticMeshObject//ShotBase//ShotBase.h"

class StaticMeshManager;

/**********************************************************************
*	�G�ʏ�e�N���X.
**/

class EnemyNomalShot
	: public ShotBase
{
public:
	EnemyNomalShot();
	~EnemyNomalShot() override;

	void Update() override;
	void Draw() override;

	//�e�̏�����.
	void Init() override;

	void Reload(const D3DXVECTOR3& pos, const D3DXVECTOR3& direction, float speed) override;

private:
};