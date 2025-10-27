#include "StaticMeshObject.h"
// Renderer �N���X�̎����ɕK�v�ȃw�b�_�[
// #include "Renderer.h" // �w�b�_�[�ŃC���N���[�h�ς݂����A�O�̂��ߋL��

StaticMeshObject::StaticMeshObject()
	: m_pMesh(nullptr)
{
	// m_vPosition, m_vRotation, m_vScale �ȂǁAGameObject �̃����o�ϐ��̏��������K�v�ł�
	// (GameObject �̃R���X�g���N�^�ŏ���������Ă��邱�Ƃ�O��Ƃ��܂�)
}

StaticMeshObject::~StaticMeshObject()
{
	// �ڑ����ꂽ���b�V���i���\�[�X���́j�́A���̃I�u�W�F�N�g�����L���Ă��Ȃ��i���|�C���^�[�̂��߁j
	// ���̂��߁A�����ł� DetachMesh() �� nullptr �ɐݒ肷��݂̂ł��B
	DetachMesh();
}

void StaticMeshObject::Update()
{
	if (m_pMesh == nullptr) {
		return;
	}
	// �����Ɉʒu�̍X�V��Փ˔���Ȃǂ̃��W�b�N������܂��B
}

void StaticMeshObject::Draw()
{
	if (!m_pMesh) return;

	// Renderer����`��p�����[�^�擾
	auto& renderer = Renderer::GetInstance();

	// ���W�E��]�E�X�P�[���𔽉f
	// m_vPosition �Ȃǂ̃����o�[�ϐ��� GameObject �N���X�Œ�`����Ă��邱�Ƃ�O��Ƃ��܂��B
	m_pMesh->SetPosition(m_vPosition);
	m_pMesh->SetRotation(m_vRotation);
	m_pMesh->SetScale(m_vScale);

	// Render�Ăяo��
	// Renderer�̃Q�b�^�[�� StaticMesh::Render �̈����� const �Q�� (const T&) ��
	// ��v���Ă��邽�߁A�^�G���[�͉�������܂��B
	m_pMesh->Render(
		renderer.GetView(),
		renderer.GetProj(),
		renderer.GetLight(),
		renderer.GetCamera().vPosition // �J�����ʒu (D3DXVECTOR3�^��z��)
	);
}