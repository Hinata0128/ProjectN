#include "Renderer.h"
// �K�v�ɉ����� LIGHT, CAMERA �\���̂̊��S�Ȓ�`���܂ރw�b�_�[���C���N���[�h���Ă�������

// ----------------------------------------------------
// �V���O���g���̎���
// ----------------------------------------------------
Renderer& Renderer::GetInstance()
{
	// C++11�ȍ~�ŃX���b�h�Z�[�t���ۏ؂����ł���ʓI�ȃV���O���g���p�^�[��
	static Renderer s_instance;
	return s_instance;
}

// ----------------------------------------------------
// �R���X�g���N�^ / �f�X�g���N�^�̎���
// ----------------------------------------------------
Renderer::Renderer()
{
	// �����o�[�ϐ��̏������������L�q���܂��B
	// ��: D3DXMatrixIdentity(&m_View); �ȂǁA���S�ȏ����l��ݒ肵�܂��B
}

Renderer::~Renderer()
{
	// �N���[���A�b�v����
}

// ----------------------------------------------------
// ���\�b�h�̎���
// ----------------------------------------------------

void Renderer::SetDrawParameters(const D3DXMATRIX& view, const D3DXMATRIX& proj, const LIGHT& light, const CAMERA& camera)
{
	m_View = view;
	m_Proj = proj;
	m_Light = light;
	m_Camera = camera;
}

// �Q�b�^�[�̎��� (���ׂ� const ���\�b�h)
const D3DXMATRIX& Renderer::GetView() const
{
	return m_View;
}

const D3DXMATRIX& Renderer::GetProj() const
{
	return m_Proj;
}

const LIGHT& Renderer::GetLight() const
{
	return m_Light;
}

const CAMERA& Renderer::GetCamera() const
{
	return m_Camera;
}