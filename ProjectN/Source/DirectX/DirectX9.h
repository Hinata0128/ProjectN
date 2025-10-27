#pragma once

//�x���ɂ��ẴR�[�h���͂𖳌��ɂ���.4005:�Ē�`.
#pragma warning(disable:4005)

//DirectX9.
#include <d3dx9.h>

//���C�u�����ǂݍ���.
#pragma comment( lib, "winmm.lib" )
//DirectX9.
#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )


/**************************************************
*	DirectX9 �Z�b�g�A�b�v.
**/
class DirectX9
{
public:
	~DirectX9();

	//�C���X�^���X�擾(�B��̃A�N�Z�X�o�H).
//���֐��̑O��static��t���邱�ƂŃC���X�^���X�������Ȃ��Ă��g�p�ł���.
	static DirectX9* GetInstance()
	{
		//�B��̃C���X�^���X���쐬����.
		//��static�ō쐬���ꂽ�̂�2��ڈȍ~�́A����1�s�͖��������.
		static DirectX9 s_Instance;	//s_:static�̈Ӗ�.
		return &s_Instance;
	}
	//DirectX9�\�z.
	HRESULT Create( HWND hWnd );
	//DirectX9���.
	void Release();

	//�f�o�C�X�I�u�W�F�N�g���擾.
	LPDIRECT3DDEVICE9 GetDevice() const { return m_pDevice9; }

private:
	DirectX9();
	DirectX9(const DirectX9& rhs) = delete;
	//������Z�q�ɂ��R�s�[���֎~����.
	//operator(�I�y���[�^):���Z�q�̃I�[�o�[���[�h�ŁA���Z�̒��g���g���ł���.
	DirectX9& operator = (const DirectX9& rhs) = delete;



private:
	LPDIRECT3DDEVICE9	m_pDevice9;	//�f�o�C�X�I�u�W�F�N�g.
};