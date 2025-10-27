#pragma once
#include "Scene//CSceneBase.h"
#include "GameObject//SpriteObject//SpriteObject.h"
#include "SceneManager//SceneManager.h"

#include "GameObject//StaticMeshObject//Ground//Ground.h"
#include "GameObject//SkinMeshObject//Character//Player//Player.h"
#include "GameObject//SkinMeshObject//Character//EnemyBase//EnemyNomal//EnemyNomal.h"

#include "System/00_Manager/05_EnemyNomalManager/EnemyNomalManager.h"
#include "System/00_Manager/02_PShotManager/PShotManager.h"
#include "System/00_Manager/04_EnemyNomalShotManager/EnemyNomalShotManager.h"

#include "System/00_Manager/06_CollisionManager/CollisionManager.h"

#include "Sprite3D//Sprite3D.h"

class Timer;


/*********************************************
*	�Q�[�����C���摜�N���X.
**/

class GameMain
	: public CSceneBase
{
public:
	GameMain();
	~GameMain() override;

	void Initialize() override;
	void Create() override;
	void Update() override;
	void Draw() override;

	HRESULT LoadData();

	//�J�����֐�.
	void Camera();
	//�v���W�F�N�V�����֐�.
	void Projection();

private:
	//�Q�[���ň����X�v���C�g�f�[�^(�g���܂킷����).
	std::unique_ptr<Sprite3D> m_pSp3D;

	//�X�^�e�B�b�N���b�V���I�u�W�F�N�g�N���X.
	std::unique_ptr<StaticMeshObject> m_pStcMeshObj;

	//�n�ʃN���X.
	std::unique_ptr<Ground>	m_pGround;

	//�v���C���[�N���X.
	std::shared_ptr<Player> m_pPlayer;

	std::shared_ptr<CollisionManager> m_pCollisionManager;
};