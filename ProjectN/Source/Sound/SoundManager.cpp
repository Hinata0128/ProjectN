#include "SoundManager.h"
#include "MyMacro.h"

SoundManager::SoundManager()
	: m_pSound	()
{
	//�C���X�^���X����.
	for( int i = 0; i < enList::max; i++ )
	{
		m_pSound[i] = new Sound();
	}
}

SoundManager::~SoundManager()
{
	Release();

	//�C���X�^���X�j��.
	for( int i = enList::max - 1; i >= 0; i-- )
	{
		SAFE_DELETE( m_pSound[i] );
	}
}

//�T�E���h�f�[�^�Ǎ��֐�.
bool SoundManager::Load( HWND hWnd )
{
	struct SoundList
	{
		int listNo;				//enList�񋓌^��ݒ�.
		const TCHAR path[256];	//�t�@�C���̖��O(�p�X�t��).
		const TCHAR alias[32];	//�G�C���A�X��.
	};
	SoundList SList[] =
	{
		{ enList::SE_Enter,		_T( "Data\\Sound\\SE\\Enter.mp3" ),				_T("SE_Enter") },
		{ enList::SE_Exp,		_T( "Data\\Sound\\SE\\explosion.mp3" ),			_T( "SE_Exp" ) },
		{ enList::SE_Shot,		_T( "Data\\Sound\\SE\\Shot.mp3" ),				_T( "SE_Shot" )},
		{ enList::BGM_Ending,	_T( "Data\\Sound\\BGM\\ending.mp3" ),			_T( "BGM_End"	)},
		{ enList::BGM_Over,		_T( "Data\\Sound\\BGM\\gameover.mp3" ),			_T( "BGM_Over"	)},
		{ enList::BGM_Main,		_T( "Data\\Sound\\BGM\\gamemain.mp3" ),			_T( "BGM_Main"	)},
		{ enList::BGM_Title,	_T( "Data\\Sound\\BGM\\title.mp3" ),			_T( "BGM_Title"	)},
	};
	//�z��̍ő�v�f�����Z�o (�z��S�̂̃T�C�Y/�z��1���̃T�C�Y).
	int list_max = sizeof( SList ) / sizeof( SList[0] );
	for( int i = 0; i < list_max; i++ )
	{
		if( m_pSound[SList[i].listNo]->Open(
			SList[i].path,
			SList[i].alias,
			hWnd ) == false )
		{
			return false;
		}
	}

	return true;
}

//�T�E���h�f�[�^����֐�.
void SoundManager::Release()
{
	//�J�������Ƌt���ŕ���.
	for( int i = enList::max - 1; i >= 0; i-- )
	{
		if( m_pSound[i] != nullptr )
		{
			m_pSound[i]->Close();
		}
	}
}
