#pragma once
#include "Scene/CSceneBase.h"
#include "Scene/Title/Title.h"
#include "Scene/GameMain/GameMain.h"
#include "Scene/GameOver/GameOver.h"
#include "Scene/Ending/Ending.h"

/********************************************
*	�V�[���}�l�[�W���[�N���X.
**/

class SceneManager
{
public:
	//�V�[�����X�g�̗񋓌^.
	enum List
	{
		//Title,
		Main,
		//GameOver,
		//Ending,

		max,
	};

public:
	//�V���O���g���p�^�[��
	static SceneManager* GetInstance()
	{
		static SceneManager s_Instance;
		return &s_Instance;
	}
	~SceneManager();

	HRESULT Create(HWND hWnd);

	void Update();
	void Draw();

	//�V�[���ǂݍ���.
	void LoadScene(List Scene);

	//HWND���擾.
	HWND GetHWND() const;
public:
	void SetDx11(DirectX11* Dx11) { m_pDx11 = Dx11; }
	void SetDx9(DirectX9* pDx9) { m_pDx9 = pDx9; }
private:
	//�V�[���쐬.
	void MakeScene(List Scene);
private:
	SceneManager();
	SceneManager(const SceneManager& rhs) = delete;
	SceneManager& operator = (const SceneManager& rhs) = delete;

private:
	std::unique_ptr<CSceneBase> m_pScene;
	HWND m_hWnd;

	DirectX11* m_pDx11;
	DirectX9*	m_pDx9;
};
