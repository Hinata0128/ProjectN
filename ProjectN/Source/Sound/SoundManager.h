#pragma once
#include "Sound.h"		//�T�E���h�N���X.

/**************************************************
*	�T�E���h�}�l�[�W���[�N���X.
*	Manager(�}�l�[�W���[)�F�Ǘ���.
*		Singleton(�V���O���g���F�f�U�C���p�^�[���̂P��)�ō쐬.
**/
class SoundManager
{
public:
	//�T�E���h���X�g�񋓌^.
	enum enList
	{
		BGM_Title,	//�^�C�g��.
		BGM_Main,	//���C��.
		BGM_Over,	//�I�[�o�[.
		BGM_Ending,	//�G���f�B���O.
		SE_Shot,	//�V���b�g.
		SE_Exp,		//����.
		SE_Enter,	//����̎��ɂȂ鉹.

		//������������u�����v�ɒǉ����Ă�������.
		max,		//�ő吔.
	};

public:
	//�C���X�^���X�擾(�B��̃A�N�Z�X�o�H).
	//���֐��̑O��static��t���邱�ƂŃC���X�^���X�������Ȃ��Ă��g�p�ł���.
	static SoundManager* GetInstance()
	{
		//�B��̃C���X�^���X���쐬����.
		//��static�ō쐬���ꂽ�̂�2��ڈȍ~�́A����1�s�͖��������.
		static SoundManager s_Instance;	//s_:static�̈Ӗ�.
		return &s_Instance;
	}


	~SoundManager();

	//�T�E���h�f�[�^�Ǎ��֐�.
	bool Load( HWND hWnd );
	//�T�E���h�f�[�^����֐�.
	void Release();

	//SE���Đ�����.
	static void PlaySE( enList list ) {
		SoundManager::GetInstance()->m_pSound[list]->PlaySE();
	}
	//���[�v�Đ�����.
	static void PlayLoop( enList list ) {
		SoundManager::GetInstance()->m_pSound[list]->PlayLoop();
	}
	//��~����.
	static void Stop( enList list ) {
		SoundManager::GetInstance()->m_pSound[list]->Stop();
	}

private://�O������A�N�Z�X�s�\.
	//�O������R���X�g���N�^�ւ̃A�N�Z�X���֎~����.
	SoundManager();
	//�R�s�[�R���X�g���N�^�ɂ��R�s�[���֎~����.
	//�u=delete�v�Ŋ֐��̒�`���폜�ł���.
	SoundManager( const SoundManager& rhs ) = delete;
	//������Z�q�ɂ��R�s�[���֎~����.
	//operator(�I�y���[�^):���Z�q�̃I�[�o�[���[�h�ŁA���Z�̒��g���g���ł���.
	SoundManager& operator = ( const SoundManager& rhs ) = delete;

private:
	Sound*		m_pSound[enList::max];
};