#pragma once
#include "GameObject//SkinMeshObject//Character//EnemyBase//EnemyBase.h"	//�x�[�X�N���X.

class EnemyNomalShotManager;
class Timer;

class EnemyNomal final
	: EnemyBase
{
public:
	EnemyNomal();
	~EnemyNomal() override;

	void Update() override;
	void Draw() override; 

	void SetAnimSpeed(double speed);

	void Stop();

public:
	void SetEnemyPosition(const D3DXVECTOR3& pos) { GameObject::SetPosition(pos); }
	// GameObject �� private �����o�[�ɃA�N�Z�X���郉�b�p�[
	D3DXVECTOR3 GetEnemyPosition() const { return m_vPosition; }
public:
	//W�ES�̑O�i��ޗp�֐�.
	D3DXVECTOR3 Enemy_WS() const;

	BoundingSphere& GetBoundingSphere() { return m_BSphere; }

private:
	EnemyNomalShotManager* m_pENShotManager;

	BoundingSphere m_BSphere; // �G�p�o�E���f�B���O�X�t�B�A
};