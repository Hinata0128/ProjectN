#pragma once
#include "StaticMash//StaticMesh.h"
#include "System//00_Manager//ManagerBase.h"

/**********************************************
*	�X�^�e�B�b�N���b�V���}�l�[�W���[�N���X.
**********************************************/
class StaticMeshManager
	: public ManagerBase
{
public:
	//���f���̎�ނ̗񋓌^.
	enum class CMeshList
	{
		Bullet,				//�e.
		Ground,				//�n��.
		SphereCollision,	//���̓����蔻��.
		EnemyBullet,		//�G�̒e.
		BoxCollision,		//�{�b�N�X�̓����蔻��.
		Portal,				//�|�[�^��.

		Max,
	};

public:
	~StaticMeshManager() override;

	void Create() override;
	void Release() override;
	void Init();

	//�X�^�e�B�b�N���b�V���̃C���X�^���X�擾.
	StaticMesh* GetMeshInstance(CMeshList MeshNo)
	{
		return m_pMesh[static_cast<int>(MeshNo)].get();
	};

	//�V���O���g���C���X�^���X�̎擾.
	static StaticMeshManager* GetInstance()
	{
		static StaticMeshManager s_Instance;//�B��̃C���X�^���X.
		return &s_Instance;//�Q�Ƃ�Ԃ�.
	}

private:
	StaticMeshManager();
	//�R���X�g���N�^���O���A�N�Z�X�֎~.
	StaticMeshManager(const StaticMeshManager& rhs) = delete;
	StaticMeshManager& operator=(const StaticMeshManager& rhs) = delete;

	std::unique_ptr<StaticMesh> m_pMesh[static_cast<int>(CMeshList::Max)];
};
