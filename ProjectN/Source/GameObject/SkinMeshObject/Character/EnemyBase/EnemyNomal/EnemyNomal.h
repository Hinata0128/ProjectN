#pragma once
#include "GameObject//SkinMeshObject//Character//EnemyBase//EnemyBase.h"	//ベースクラス.

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
	// GameObject の private メンバーにアクセスするラッパー
	D3DXVECTOR3 GetEnemyPosition() const { return m_vPosition; }
public:
	//W・Sの前進後退用関数.
	D3DXVECTOR3 Enemy_WS() const;

	BoundingSphere& GetBoundingSphere() { return m_BSphere; }

private:
	EnemyNomalShotManager* m_pENShotManager;

	BoundingSphere m_BSphere; // 敵用バウンディングスフィア
};