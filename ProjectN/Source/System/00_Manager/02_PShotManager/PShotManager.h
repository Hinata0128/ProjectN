#pragma once
#include "GameObject/StaticMeshObject/ShotBase/PShot/PShot.h"

/**********************************************
*�v���C���[�e�}�l�[�W���[�N���X.
*�e�̐����E�X�V�E�`��E�j�����Ǘ�����.
**********************************************/
class PShotManager
{
public:
	~PShotManager();

	static PShotManager* GetInstance();	//�C���X�^���X�擾.

	void Update();	//�e�̍X�V����.
	void Draw();	//�e�̕`�揈��.

	void AddPlayerShot(const D3DXVECTOR3& Pos, const D3DXVECTOR3& InitDirection);	//�v���C���[�̒e��ǉ�.
	void ReMovePlayerShot(size_t index);	//�w��C���f�b�N�X�̒e���폜.

	const std::vector<std::unique_ptr<PShot>>& GetPlayerShot()const;	//�e���X�g���擾.
	PShot* GetPlayerShot(size_t No);	//�w��ԍ��̒e���擾.
	size_t GetPlayerShotCount()const;	//�e�̑������擾.

	std::vector<PShot*> GetShots(); 
private:
	PShotManager();
	PShotManager(const PShotManager& rhs) = delete;
	PShotManager& operator=(const PShotManager& rhs) = delete;

private:
	static PShotManager* m_pInstance;	//�V���O���g���C���X�^���X.
	std::vector<std::unique_ptr<PShot>> m_PlayerShot;	//�e���X�g.
};
