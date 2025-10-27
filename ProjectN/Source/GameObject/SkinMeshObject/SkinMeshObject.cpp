#include "SkinMeshObject.h"

SkinMeshObject::SkinMeshObject()
	: GameObject		()
	, m_pMesh			( std::make_shared<SkinMesh>() )
	, m_pAnimCtrl		( nullptr )
	, m_AnimNo			( 0 )
	, m_AnimSpeed		( 0.0 )
	, m_AnimTime		( 0.0 )
	, m_BonePos			()
	, m_Loop			( false )
{
}

SkinMeshObject::~SkinMeshObject()
{
	DetachMesh();
}

void SkinMeshObject::Update()
{
	if( m_pMesh == nullptr ){
		return;
	}

	// ���Ԃ�i�߂�
	m_AnimTime += m_AnimSpeed;

	// ���[�v�Đ����L���ȏꍇ
	if (m_Loop)
	{
		double animPeriod = m_pMesh->GetAnimPeriod(m_AnimNo); // �� �A�j���̑S���擾
		if (m_AnimTime > animPeriod)
		{
			m_AnimTime = 0.0; // �ŏ��ɖ߂�
			m_pAnimCtrl->SetTrackPosition(0, 0.0);
		}
	}

	// DirectX�A�j���[�V�������Ԃ�i�߂�
	m_pAnimCtrl->AdvanceTime(m_AnimSpeed, nullptr);
}

void SkinMeshObject::Draw()
{
	if (!m_pMesh) return;

	auto& renderer = Renderer::GetInstance();

	// ���W�E��]�E�X�P�[�����f
	m_pMesh->SetPosition(m_vPosition);
	m_pMesh->SetRotation(m_vRotation);
	m_pMesh->SetScale(m_vScale);

	D3DXVECTOR3 camPos = renderer.GetCamera().vPosition; // �^���m�F

	// �A�j���[�V�����R���g���[����nullptr�Ȃ�nullptr��n��
	m_pMesh->Render(
		renderer.GetView(),
		renderer.GetProj(),
		renderer.GetLight(),
		camPos,
		m_pAnimCtrl
	);
}

//���b�V����ڑ�����.
void SkinMeshObject::AttachMesh(std::shared_ptr<SkinMesh> pMesh)
{
	m_pMesh = pMesh;

	//�A�j���[�V�����R���g���[�����擾
	LPD3DXANIMATIONCONTROLLER pAC = m_pMesh->GetAnimationController();

	//�A�j���[�V�����R���g���[���̃N���[�����쐬
	if (FAILED(
		pAC->CloneAnimationController(
			pAC->GetMaxNumAnimationOutputs(),
			pAC->GetMaxNumAnimationSets(),
			pAC->GetMaxNumTracks(),
			pAC->GetMaxNumEvents(),
			&m_pAnimCtrl)))
	{
		_ASSERT_EXPR(false, L"�A�j���[�V�����R���g���[���̃N���[���쐬���s");
	}
}
//���b�V����؂藣��.
void SkinMeshObject::DetachMesh()
{
	m_pMesh = nullptr;

	SAFE_RELEASE(m_pAnimCtrl);
}

void SkinMeshObject::SetIsLoop(const bool& IsLoop)
{
	m_Loop = IsLoop;
}

