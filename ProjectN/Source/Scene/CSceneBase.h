#pragma once
#include "StaticMash/StaticMesh.h"
#include "DirectX/DirectX11.h"
#include "DirectX/DirectX9.h"
#include "Sprite2D/Sprite2D.h"
#include "GameObject/UIObject/UIObject.h"


/**********************************************************
*	���N���X.
**/

class CSceneBase	
{
public:
	CSceneBase();
	virtual ~CSceneBase() {}

	virtual void Initialize() = 0;
	virtual void Create() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	//���b�V����ڑ�����.
	void AttachMesh(StaticMesh& pMesh) {
		m_pMesh = &pMesh;
	}

	void PreDraw();

protected:
	StaticMesh* m_pMesh;
	DirectX9* m_pDx9;
	DirectX11* m_pDx11;

	//�E�B���h�E�n���h��.
	HWND				m_hWnd;

	//�J�������.
	CAMERA				m_Camera;
	//���C�g���
	LIGHT				m_Light;

	//�s��.
	D3DXMATRIX			m_mView;	//�r���[(�J����)�s��.
	D3DXMATRIX			m_mProj;	//�ˉe�i�v���W�F�N�V�����j�s��.

	int m_Score;

	int m_Count;
};