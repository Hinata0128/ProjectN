#pragma once

#include "SkinMesh//SkinMesh.h"
#include "System//00_Manager//ManagerBase.h"

/*****************************************************************************
*	�X�L�����b�V���}�l�[�W���[�N���X
*	�ŏI�I�ɂ́A�A�Z�b�g�N���X���쐬���Ă����ɃX�^�e�B�b�N�ƃX�L�����b�V���𓝍�������.
*	���̓V���O���g���ɂ��Ă����܂�.
**/

class SkinMeshManager
	: public ManagerBase
{
public:
	// �X�L�����f���̎�ނ̗񋓌^.
	enum class SkinList
	{
		Player,		// �v���C���[.
		Enemy,		// ���̓G�ł�.

		Max
	};

public:
	// �V���O���g���֘A
	static SkinMeshManager* GetInstance();
	~SkinMeshManager() override;

	// ManagerBase�̊֐����I�[�o�[���C�h
	void Create() override;
	void Release() override;

	// �Ǝ��֐�
	SkinMesh* GetSkinMeshInstance(SkinList skinNo);

private:
	SkinMeshManager();
	SkinMeshManager(const SkinMeshManager&) = delete;
	SkinMeshManager& operator=(const SkinMeshManager&) = delete;

private:
	std::unique_ptr<SkinMesh> m_pSkin[static_cast<int>(SkinList::Max)];
};
