#pragma once

#include "StaticMash/StaticMesh.h"
#include <d3dx9.h>       // D3DXVECTOR3 �̒�`���K�v
#include <cfloat>        // FLT_MAX, -FLT_MAX �̂��߂ɕK�v

/**************************************************
*	�o�E���f�B���O�{�b�N�X.
**/

class BoundingBox
{
public:
	BoundingBox();
	~BoundingBox();

	//���f���ɍ��킹���o�E���f�B���O�{�b�N�X���쐬.
	//���b�V���̊O��AABB���v�Z����.
	HRESULT CreateBoxForMesh(const StaticMesh& pMesh);

	void Draw();

	//���̃{�b�N�X�Ƃ̓����蔻��(AABB vs AABB).
	bool IsHit(const BoundingBox& pBBox) const;

	//���݂�AABB�̍ŏ����W���擾����.
	const D3DXVECTOR3& GetMinPosition() const { return m_MinPosition; }
	//���݂�AABB�̍ő���W���擾����.
	const D3DXVECTOR3& GetMaxPosition() const { return m_MaxPosition; }

	//���݂�AABB�̍ŏ����W��ݒ肷��.
	void SetMinPosition(const D3DXVECTOR3& MinPos) { m_MinPosition = MinPos; }
	//���݂�AABB�̍ő���W��ݒ肷��.
	void SetMaxPosition(const D3DXVECTOR3& MaxPos) { m_MaxPosition = MaxPos; }

	// BoundingBox�̒��S���W���擾
	D3DXVECTOR3 GetCenter() const;

	// BoundingBox�̃T�C�Y�i���A�����A���s���j���擾���郁�\�b�h
	D3DXVECTOR3 GetSize() const;

	// �I���W�i���̃��[�J��AABB�̍ŏ��E�ő���W��ۑ�/�擾����
	void SetOriginalLocalMinMax(const D3DXVECTOR3& minPos, const D3DXVECTOR3& maxPos);
	D3DXVECTOR3 GetOriginalLocalMin() const { return m_OriginalLocalMin; }
	D3DXVECTOR3 GetOriginalLocalMax() const { return m_OriginalLocalMax; }

	//���݂�AABB�̍ŏ����W���擾����.
	const D3DXVECTOR3& GetMin() const { return m_MinPosition; }
	//���݂�AABB�̍ő���W���擾����.
	const D3DXVECTOR3& GetMax() const { return m_MaxPosition; }

private:
	D3DXVECTOR3 m_MinPosition;	// ���[���h��ԁA�܂��͕ϊ����AABB�̍ŏ����W.
	D3DXVECTOR3 m_MaxPosition;	// ���[���h��ԁA�܂��͕ϊ����AABB�̍ő���W.
	D3DXVECTOR3 m_OriginalLocalMin; // CreateBoxForMesh�Ōv�Z���ꂽ���[�J��AABB�̍ŏ����W.
	D3DXVECTOR3 m_OriginalLocalMax; // CreateBoxForMesh�Ōv�Z���ꂽ���[�J��AABB�̍ő���W.

	StaticMesh* m_pMesh;
	D3DXVECTOR3		m_Position;	//���S���W.
	float			m_Radius;	//���a(����).

};