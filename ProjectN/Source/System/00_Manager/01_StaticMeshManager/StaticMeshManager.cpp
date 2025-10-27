#include "StaticMeshManager.h"
//�x���ɂ��ẴR�[�h���͂𖳌��ɂ���.4005:�Ē�`.
#pragma warning(disable:4005)

StaticMeshManager::StaticMeshManager()
{
}

StaticMeshManager::~StaticMeshManager()
{
	Release();
}

void StaticMeshManager::Create()
{
	//�X�^�e�B�b�N���b�V���z���������.
	for (int i = 0; i < static_cast<int>(CMeshList::Max); ++i)
	{
		m_pMesh[i] = std::make_unique<StaticMesh>();
	}

	//�ǂݍ��݃��X�g�\���̂̒�`.
	struct MeshList
	{
		int listNo;//CMeshList�񋓌^��ݒ�.
		const TCHAR path[256];//�t�@�C���p�X.
	};

	//�ǂݍ��ݑΏۃ��X�g�̐ݒ�.
	MeshList MList[] =
	{
		{ static_cast<int>(CMeshList::Bullet),			_T("Data\\Mesh\\Static\\Bullet\\BulletTest.x") },
		{ static_cast<int>(CMeshList::Ground),			_T("Data\\Mesh\\Static\\Ground\\ground.x") },
		{ static_cast<int>(CMeshList::SphereCollision),	_T("Data\\Mesh\\Static\\Collision\\Sphere.x") },
		{ static_cast<int>(CMeshList::EnemyBullet),		_T("Data\\Mesh\\Static\\Bullet\\EnemyBullet.x") },
		{ static_cast<int>(CMeshList::BoxCollision),	_T("Data\\Mesh\\Static\\Collision\\Box.x")},
		{ static_cast<int>(CMeshList::Portal),			_T("Data\\Mesh\\Static\\Portal\\Portal.x")},
	};

	//�z��̗v�f�����擾.
	const int listMax = static_cast<int>(std::size(MList));

	//�ǂݍ��ݏ���.
	for (int i = 0; i < listMax; ++i)
	{
		int idx = MList[i].listNo;
		if (FAILED(m_pMesh[idx]->Init(MList[i].path)))
		{
			//�ǂݍ��ݎ��s���͈��S�ɏI��.
			return;
		}
	}
}

void StaticMeshManager::Release()
{
	//unique_ptr�Ȃ̂Ŏ����ŉ������邪�A�����I�Ƀ��Z�b�g���Ă���.
	for (int i = 0; i < static_cast<int>(CMeshList::Max); ++i)
	{
		m_pMesh[i].reset();
	}
}

void StaticMeshManager::Init()
{
	//�������������K�v�ȏꍇ�����ɋL�q.
}
