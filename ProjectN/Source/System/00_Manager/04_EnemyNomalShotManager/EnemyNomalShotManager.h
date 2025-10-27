#pragma once
#include "GameObject/StaticMeshObject/ShotBase/EnemyNomalShot/EnemyNomalShot.h"

/*****************************************************************
*	�G�̒ʏ�U���}�l�[�W���[�N���X.
**/
class EnemyNomalShotManager
{
public:
	~EnemyNomalShotManager();

	static EnemyNomalShotManager* GetInstance();

	void Update();	//�e�̍X�V����.
	void Draw();	//�e�̕`�揈��.

	void AddEnemyNomalShot(const D3DXVECTOR3& Pos, const D3DXVECTOR3& InitDirecton);	//�G�̒e���쐬���ĊǗ����X�g�ɒǉ�.

	void ReMoveEnemyNomalShot(size_t index);	//�G�̒e���폜.

	const std::vector<std::unique_ptr<EnemyNomalShot>>& GetEnemyNomalShot() const;	//�G�̒e���X�g�擾.

	EnemyNomalShot* GetEnemyNomalShot(size_t No);	//�G�̒e�擾.

	size_t GetEnemyNomalShotCount() const;	//�G�̒e���擾.

	std::vector<EnemyNomalShot*> GetShots();
private:
	EnemyNomalShotManager();

	EnemyNomalShotManager(const EnemyNomalShotManager& rhs) = delete;	//�R�s�[�֎~.
	EnemyNomalShotManager& operator = (const EnemyNomalShotManager& rhs) = delete;	//����֎~.
private:
	static EnemyNomalShotManager* m_pInstance;	//�V���O���g���C���X�^���X.

	std::vector<std::unique_ptr<EnemyNomalShot>> m_EnemyNomalShot;	//�G�e�̊Ǘ��z��.
};