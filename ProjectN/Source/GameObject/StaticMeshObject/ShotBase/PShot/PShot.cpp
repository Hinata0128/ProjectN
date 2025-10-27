#include "PShot.h"
#include "System/00_Manager/01_StaticMeshManager/StaticMeshManager.h"

PShot::PShot()
{
	AttachMesh(*StaticMeshManager::GetInstance()->GetMeshInstance(StaticMeshManager::CMeshList::Bullet));

	// �R���X�g���N�^�ŏ�����
	Init();
}

PShot::~PShot()
{

}

void PShot::Update()
{
	constexpr float MaxRange = 30.0f;

	if (!m_IsActive) return;

	if (m_Disp)
	{
		// �ʒu�X�V
		m_vPosition += m_Direction * m_Speed;

		// ��苗���𒴂����烊�Z�b�g
		if (D3DXVec3Length(&m_vPosition) >= MaxRange)
		{
			Init();
			return;
		}
		// �o�E���f�B���O�X�t�B�A�̈ʒu����
		UpdateBPosition();
	}
}

void PShot::Draw()
{
	if (m_Disp)
	{
		ShotBase::Draw();
	}
}

void PShot::Init()
{
	// �e�N���X�̊�{������
	ShotBase::Init();

	// �����ڂ̑傫���i�v���C���[�̒e�j
	m_vScale = D3DXVECTOR3(5.0f, 5.0f, 5.0f);

	// �����蔻��̑傫���i�X�P�[���ɍ��킹�āj
	if (m_BSphere)
	{
		m_BSphere->SetRadius(2.5f); // �X�P�[���̔���
	}
}

void PShot::Reload(const D3DXVECTOR3& pos, const D3DXVECTOR3& direction, float speed)
{
	m_vPosition = pos;
	m_Direction = direction;
	m_Speed		= speed;

	m_Disp		= true;
	m_IsActive	= true;

	if (m_BSphere)
	{
		m_BSphere->SetPosition(m_vPosition);
		m_BSphere->SetRadius(0.5f);
	}
}
