#pragma once
#include "System//02_Singleton//Timer//Timer.h"
#include "Collision//BoundingBox//BoundingBox.h"
#include "Collision//BoundingSphere//BoundingSphere.h"

//�����蔻��Ɏg�p����N���X���C���N���[�h.
#include "System//00_Manager//ManagerBase.h"
#include "System//00_Manager//04_EnemyNomalShotManager//EnemyNomalShotManager.h"
#include "System//00_Manager//05_EnemyNomalManager//EnemyNomalManager.h"
#include "GameObject//StaticMeshObject//ShotBase//PShot//PShot.h"
#include "GameObject//SkinMeshObject//Character//Player//Player.h"

/******************************************************************************
*	�����蔻��}�l�[�W���[�N���X.
**/

class CollisionManager
	: public ManagerBase
{
public:
	CollisionManager();
	~CollisionManager() override;

	void Update() override;
	void Draw() override;
	void Create() override;
	void Release() override;

	//�R���C�_�[�̓o�^�֐�.
	void AddSphere(const std::shared_ptr<BoundingSphere>& sphere);
	void AddBox(const std::shared_ptr<BoundingBox>& box);
	//�o�^����Ă��邷�ׂẴR���C�_�[���폜����.
	void Clear();

	//�����蔻�����ɋN�����Ă����֐�.
	void AllCollider();

public:
	void SetPlayer(const std::shared_ptr<Player>& player) { m_pPlayer = player; }
	void SetEnemies(const std::vector<EnemyNomal*>& enemies) { m_vEnemies = enemies; }
	void SetPlayerShots(const std::vector<PShot*>& shots) { m_PlayerShots = shots; }
	void SetEnemyShots(const std::vector<EnemyNomalShot*>& shots) { m_EnemyShots = shots; }

private:
	//�����蔻��̊֐��������ɏ����܂�
	bool CheckSphereSphere(const BoundingSphere& a, const BoundingSphere& b);	//�X�t�B�A���m�̔���. 
	bool CheckBoxBox(const BoundingBox& a, const BoundingBox& b);				//AABB���m�̔���. 
	bool CheckSphereBox(const BoundingSphere& sphere, const BoundingBox& box);	//�X�t�B�A��AABB�̔���. 

private:
	std::vector<std::shared_ptr<BoundingSphere>>	m_pBSphere;
	std::vector<std::shared_ptr<BoundingBox>>		m_pBBox;

	std::shared_ptr<Player> m_pPlayer;
	std::vector<EnemyNomal*> m_vEnemies;	
	std::vector<PShot*> m_PlayerShots;
	std::vector<EnemyNomalShot*> m_EnemyShots;
};