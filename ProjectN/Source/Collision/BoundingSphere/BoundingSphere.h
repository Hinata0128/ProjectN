#pragma once

#include "StaticMash/StaticMesh.h"

/**********************************************************************************
*	�o�E���f�B���O�X�t�B�A�N���X(�����蔻��N���X).
**/

class BoundingSphere
{
public:
	BoundingSphere();
	~BoundingSphere();

	//���f���ɍ��킹���o�E���f�B���O�X�t�B�A���쐬.
	//������&�����鎞�͂��̎��̃A�h���X����ɓ���邱�Ƃ��m���ɂł���.
	HRESULT CreateSphereForMesh(const StaticMesh& pMesh);

	//���̋��̂Ƃ̓����蔻��.
	bool IsHit(const BoundingSphere& pBSphere) const;

	//���S���W���擾����.
	const D3DXVECTOR3& GetPostion() const { return m_Position; }
	//���a(����)���擾����.
	float GetRadius() const { return m_Radius; }

	//���S���W��ݒ肷��.
	void SetPosition(const D3DXVECTOR3& Pos) { m_Position = Pos; }
	//���a(����)��ݒ肷��.
	void SetRadius(float Radius) { m_Radius = Radius; }

	void Update();
	void Draw();


private:
	StaticMesh* m_pMesh;
	D3DXVECTOR3		m_Position;	//���S���W.
	float			m_Radius;	//���a(����).
};