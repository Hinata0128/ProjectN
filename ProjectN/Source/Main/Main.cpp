#include "Main.h"
#include "DirectX\\DirectX9.h"
#include "DirectX\\DirectX11.h"
#include "SceneManager/SceneManager.h"
#include "System/00_Manager/01_StaticMeshManager/StaticMeshManager.h"
#include "System/00_Manager/00_SkinMeshManager/SkinMeshManager.h"
#include "Effect/Effect.h"
#include "Sound/SoundManager.h"

#include "System/00_Manager/03_ImGuiManager/ImGuiManager.h"
// ImGui�̃��b�Z�[�W�n���h���̂��߂̊O���錾�B�ʏ��ImguiManager.h�Ɋ܂܂�܂��B
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


//�E�B���h�E����ʒ����ŋN����L���ɂ���.
//#define ENABLE_WINDOWS_CENTERING

//=================================================
//	�萔.
//=================================================
const TCHAR WND_TITLE[] = _T("Ones");
const TCHAR APP_NAME[] = _T("Ones");
// �O����`��FPS�萔 (Loop�֐��Ŏg�p)
// const int FPS = 60; 


//=================================================
//	�R���X�g���N�^.
//=================================================
Main::Main()
//���������X�g.
	: m_hWnd(nullptr)
	// m_SomeFloatValue, m_bFeatureEnabled �� Main.h �̏��������X�g�Őݒ肳��Ă��邱�Ƃ�z��
{
	AllocConsole(); // �R�}���h�v�����v�g�\��
}


//=================================================
//	�f�X�g���N�^.
//=================================================
Main::~Main()
{
	DeleteObject(m_hWnd);
}


//=================================================
//	�\�z����.
//=================================================
HRESULT Main::Create()
{
	auto pDx9 = DirectX9::GetInstance();
	auto pDx11 = DirectX11::GetInstance();

	if (FAILED(pDx9->Create(m_hWnd)))
		return E_FAIL;
	if (FAILED(pDx11->Create(m_hWnd)))
		return E_FAIL;

	StaticMeshManager::GetInstance()->Create();
	SkinMeshManager::GetInstance()->Create();

	SceneManager::GetInstance()->SetDx9(pDx9);
	SceneManager::GetInstance()->SetDx11(pDx11);

	Effect::GetInstance()->Create(pDx11->GetDevice(), pDx11->GetContext());

	// ImGui ������
	if (FAILED(ImGuiManager::GetInstance()->Init(m_hWnd)))
		return E_FAIL;

	return S_OK;
}

//=================================================
//	�X�V����.
//=================================================
void Main::Update()
{
	ImGuiManager::GetInstance()->NewFrameSetting();

	SceneManager::GetInstance()->Update();

	ImGui::Begin("My Debug Window");
	ImGui::Text("Hello, ImGui!");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	if (ImGui::Button("Test Button"))
	{
		OutputDebugString(_T("Test Button Clicked!\n"));
	}
	// �� ImGui�̏����ʒu�ݒ�i�ړ��ł��Ȃ��ꍇ�͂�����R�����g�A�E�g���Ă��������j
	// ImGui::SetNextWindowPos(ImVec2(100, 100), ImGuiCond_Once); 

	ImGui::SliderFloat("Float Value", &m_SomeFloatValue, 0.0f, 100.0f);
	ImGui::Checkbox("Enable Feature", &m_bFeatureEnabled);

	ImGui::End();
}

//=================================================
//	�`�揈��.
//=================================================
void Main::Draw()
{
	auto pDx11 = DirectX11::GetInstance();

	//�o�b�N�o�b�t�@���N���A
	pDx11->ClearBackBuffer();

	SceneManager::GetInstance()->Draw();

	ImGuiManager::GetInstance()->Render();

	// ��ʂɕ\��
	pDx11->Present();
}


//=================================================
//	�f�[�^���[�h����.
//=================================================
HRESULT Main::LoadData()
{
	if (SoundManager::GetInstance()->Load(m_hWnd) == false) {
		return E_FAIL;
	}

	if (FAILED(Effect::GetInstance()->LoadData()))
	{
		return E_FAIL;
	}

	SceneManager::GetInstance()->Create(m_hWnd);

	return S_OK;
}


//=================================================
//	�������.
//=================================================
void Main::Release()
{
	DirectX11::GetInstance()->Release();
	DirectX9::GetInstance()->Release();
}


//=================================================
//	���b�Z�[�W���[�v.
//=================================================
void Main::Loop()
{
	if (FAILED(LoadData())) {
		return;
	}

	//------------------------------------------------
	//	�t���[�����[�g��������.
	//------------------------------------------------
	float Rate = 0.0f;
	DWORD sync_old = timeGetTime();
	DWORD sync_now;

	timeBeginPeriod(1);
	// FPS�͊O���Œ�`����Ă���Ɖ���
	Rate = 1000.0f / static_cast<float>(FPS);

	MSG msg = { 0 };
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		sync_now = timeGetTime();

		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else if (sync_now - sync_old >= Rate)
		{
			sync_old = sync_now;

			// �X�V�ƕ`��𕪗����ČĂяo��
			Update();
			Draw();
		}
	}

	timeEndPeriod(1); // timeBeginPeriod�Ƒ΂ŌĂ�
	Release();
}

//=================================================
//	�E�B���h�E�������֐�.
//=================================================
HRESULT Main::InitWindow(
	HINSTANCE hInstance,
	INT x, INT y,
	INT width, INT height)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));

	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = MsgProc;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wc.lpszClassName = APP_NAME;
	wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

	if (!RegisterClassEx(&wc)) {
		_ASSERT_EXPR(false, _T("�E�B���h�E�N���X�̓o�^�Ɏ��s"));
		return E_FAIL;
	}

	// ... (�E�B���h�E�\���ʒu�̒������W�b�N�͊ȗ���) ...

	RECT	rect = { 0, 0, width, height };
	DWORD	dwStyle = WS_OVERLAPPEDWINDOW;

	if (AdjustWindowRect(&rect, dwStyle, FALSE) == 0)
	{
		MessageBox(nullptr, _T("�E�B���h�E�̈�̒����Ɏ��s"), _T("�G���[���b�Z�[�W"), MB_OK);
		return E_FAIL;
	}

	INT winWidth = rect.right - rect.left;
	INT winHeight = rect.bottom - rect.top;

	m_hWnd = CreateWindow(
		APP_NAME, WND_TITLE, dwStyle,
		0, 0, // �ȗ������č���ɕ\��
		winWidth, winHeight,
		nullptr, nullptr, hInstance, nullptr);

	if (!m_hWnd) {
		_ASSERT_EXPR(false, _T("�E�B���h�E�쐬���s"));
		return E_FAIL;
	}

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	return S_OK;
}


//=================================================
//	�E�B���h�E�֐��i���b�Z�[�W���̏����j.
//=================================================
LRESULT CALLBACK Main::MsgProc(
	HWND hWnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam)
{
	// �� �C��: ImGui�̃��b�Z�[�W�n���h�����ŏ��ɌĂяo���AUI�����b�Z�[�W��������珈���𒆒f���܂�
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
	{
		return true; // ImGui���C�x���g����������
	}

	switch (uMsg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (static_cast<char>(wParam)) {
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}