#pragma once

#include <iostream>
#include <D3DX9.h>
// D3DXMATRIX, D3DXVECTOR3 �̒�`���܂�

// LIGHT, CAMERA �\���̂̒�`�͊O���t�@�C���i��F�Q�[�����ʃw�b�_�[�j�ɂ���Ɖ��肵�܂��B
// ��:
// struct LIGHT { ... };
// struct CAMERA { ... };


/************************************************************************************
*	�����_���[�N���X.
**/
class Renderer
{
public:
	// �V���O���g���C���X�^���X���擾����ÓI���\�b�h
	static Renderer& GetInstance();

	// ���z�f�X�g���N�^ (�V���O���g���ł��p�������\�������邽�ߐ���)
	virtual ~Renderer();

	// --- �O������`��p�����[�^��ݒ肷�郁�\�b�h ---
	void SetDrawParameters(const D3DXMATRIX& view, const D3DXMATRIX& proj, const LIGHT& light, const CAMERA& camera);

	// --- �e�p�����[�^���擾���邽�߂̃Q�b�^�[ ---
	const D3DXMATRIX& GetView() const;
	const D3DXMATRIX& GetProj() const;
	const LIGHT& GetLight() const;
	const CAMERA& GetCamera() const;

private:
	// �R���X�g���N�^�� private �ɂ��ĊO������̒��ڐ������֎~
	Renderer();

	// �R�s�[�A���[�u���֎~
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;
	Renderer(Renderer&&) = delete;
	Renderer& operator=(Renderer&&) = delete;

private:
	// �����o�[�ϐ��̒�`
	D3DXMATRIX	m_View;
	D3DXMATRIX	m_Proj;

	CAMERA		m_Camera;
	LIGHT		m_Light;
};