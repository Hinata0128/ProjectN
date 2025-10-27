#pragma once
#include "GameObject/SkinMeshObject/Character/Character.h"

class PShot;
class PShotManager;
class Timer;

/**************************************************
*	�v���C���[�N���X.
**/
class Player final
	: public Character
{
public:
	Player();
	 ~Player() override;

	void Update() override;
	void Draw() override;

	void SetAnimSpeed(double speed) { m_AnimSpeed = speed; }

	void Stop();

public:
	//W�ES�̑O�i��ޗp�֐�.
	D3DXVECTOR3 Player_WS() const;
	//A�ED�̍��E�p�֐�.
	D3DXVECTOR3 Player_AD() const;

	BoundingSphere& GetBoundingSphere() { return m_BSphere; }

	PShotManager* GetShotManager() { return m_pShotManager; }

private:
	PShotManager*	m_pShotManager;

	BoundingSphere m_BSphere; // �v���C���[�p�o�E���f�B���O�X�t�B�A
};