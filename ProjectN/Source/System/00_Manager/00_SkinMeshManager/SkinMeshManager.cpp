#include "SkinMeshManager.h"

SkinMeshManager::SkinMeshManager()
{
}

SkinMeshManager::~SkinMeshManager()
{
	Release();//�O�̂��߈��S�Ƀ��\�[�X���.
}

void SkinMeshManager::Create()
{
	//�X�L���z��̏�����.
	for (int i = 0; i < static_cast<int>(SkinList::Max); ++i)
	{
		m_pSkin[i] = std::make_unique<SkinMesh>();
	}

	//�ǂݍ��݃��X�g�\���̂̒�`.
	struct MeshList
	{
		int listNo;
		const TCHAR path[256];
	};

	//�ǂݍ��ݑΏۃ��X�g�̐ݒ�.
	MeshList SList[] =
	{
		{ static_cast<int>(SkinList::Player),	_T("Data\\Mesh\\Skin\\EXTINGER\\extinger.X") },
		{ static_cast<int>(SkinList::Enemy),	_T("Data\\Mesh\\Skin\\zako\\zako.X") },
	};

	//�z��̗v�f�����擾.
	const int listMax = static_cast<int>(std::size(SList));

	//�ǂݍ��ݏ���.
	for (int i = 0; i < listMax; ++i)
	{
		int idx = SList[i].listNo;
		if (FAILED(m_pSkin[idx]->Init(SList[i].path)))
		{
			//�ǂݍ��ݎ��s���͈��S�ɏI��.
			return;
		}
	}
}

void SkinMeshManager::Release()
{
	//unique_ptr�Ȃ̂Ŏ����ŉ������邪�A�����I�Ƀ��Z�b�g���Ă���.
	for (int i = 0; i < static_cast<int>(SkinList::Max); ++i)
	{
		m_pSkin[i].reset();
	}
}

SkinMesh* SkinMeshManager::GetSkinMeshInstance(SkinList skinNo)
{
	//�w�肳�ꂽ�X�L���ԍ��̃C���X�^���X���擾.
	return m_pSkin[static_cast<int>(skinNo)].get();
}

//�V���O���g���C���X�^���X�̎擾.
SkinMeshManager* SkinMeshManager::GetInstance()
{
	static SkinMeshManager s_Instance;//�ÓI�C���X�^���X.
	return &s_Instance;//�Q�Ƃ�Ԃ�.
}
