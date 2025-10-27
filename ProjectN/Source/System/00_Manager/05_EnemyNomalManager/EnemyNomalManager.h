#pragma once
#include "GameObject//SkinMeshObject//Character//EnemyBase//EnemyNomal//EnemyNomal.h"
#include "System//00_Manager//ManagerBase.h"

/*********************************************************************************
*	�m�[�}���̓G�̐��𑝂₷�̂Ń}�l�[�W���[�N���X���쐬.
*	�V���O���g���ō쐬���܂�.
**/

class EnemyNomalManager
	: public ManagerBase
{
public:
	~EnemyNomalManager();

	static EnemyNomalManager* GetInstace();

	void Update() override;
	void Draw() override;
	void Create() override;
	void Release() override;

	//�G�̔j��.
	void ReMoveEnemy(size_t index);

	EnemyNomal* GetEnemyNomal(size_t No);

	//�m�[�}���̓G�̐����擾����.
	size_t GetEnemyNomalCount() const;

	// �����ŃN���X���͕s�v
	void AddEnemy(std::unique_ptr<EnemyNomal> enemy, const D3DXVECTOR3& pos);

	std::vector<EnemyNomal*> GetEnemies();
private:
	EnemyNomalManager();

	EnemyNomalManager(const EnemyNomalManager& rhs) = delete;
	EnemyNomalManager& operator = (const EnemyNomalManager& rhs) = delete;
private:
	std::vector<std::unique_ptr<EnemyNomal>> m_pEnemyNomal;
};