#pragma once

#include "..//Data/ImGui/Library/imgui_impl_dx11.h"
#include "..//Data/ImGui/Library/imgui_impl_win32.h"

#include <string>

/*****************************************************
*	ImGui�}�l�[�W���[�N���X.
* �@(�V���O���g���ō쐬).
**/

class ImGuiManager final
{
public:
	~ImGuiManager();
	//�C���X�^���X���擾.
	static ImGuiManager* GetInstance();

	//������.
	//������hWnd�����Ă��闝�R(�\�z)
	//�E�B���h�E�����ł����g��Ȃ��̂ŃQ�[�����ł͎g�p���Ȃ����߂��Ƃ�����.
	static HRESULT Init(HWND hWnd);

	//�����[�X�֐�.
	static void Relese();

	//�t���[���̐ݒ�.
	static void NewFrameSetting();

	//Render�֐��͏�������֐��ł�.
	//�`�施�߂���������֐�.
	//�������ADraw()�֐��ł͂Ȃ����R�́A
	//Draw�֐��́A�����ɕ`�悷��C���[�W�֐��ł�.
	static void Render();

	//���̓{�b�N�X�̕\��.
	template<typename T>
	static bool Input(
		const char* label,				//���x������(ImGui�ł̕\�����Ȃ�)
		T& value,						//���[�U�[�����͂���l�ւ̎Q��(�^��T)
		bool isLabel = true,			//���x���\�����邩�ǂ���(�f�t�H���gtrue)
		float step = 0.f,				//�X�e�b�v��(��: ���l�̑����{�^���p)
		float steoFast = 0.f,			//�X�e�b�v��(�����o�[�W����)��typo�����H
		const char* format = "% .3f",	//�\���t�H�[�}�b�g
		ImGuiInputTextFlags flags = 0);	//ImGui�̓��̓I�v�V����.

	//�X���C�_�[�̕\��.
	//ImGui�Œl���X���C�_�[�Œ����ł���悤�ɂ���.
	template<typename T>
	static void Slider(
		const char* label,		//���x����(UI�ɕ\������閼�O(��: "Speed"))
		T& value,				//�����Ώۂ̒l(�Q�Ɠn���A��: speed)
		T valueMin,				//�X���C�_�[�̍ŏ��l.
		T valieMax,				//�X���C�_�[�̍ő�l(�ŏ��l�͒ʏ�0�Ɖ��肳���)
		bool isLabel = true);	//���x����UI�ɕ\�����邩(true�Ȃ�\��)

	//�R���{�{�b�N�X.
	static std::string Combo(
		const char* label,						//���x����(UI�ɕ\������閼�O).
		std::string& NowItem,					//���ݑI�΂�Ă��鍀�ڂ̖��O(�I����Ԃ̕ێ��Ɏg��).
		const std::vector<std::string>& List,	//�I�����̈ꗗ(�\�����郊�X�g)
		bool isLabel = false,					//���x�����R���{�{�b�N�X�̉��ɕ\�����邩�Htrue: �\��, false: ��\��.
		float space = 100.f);					//�R���{�{�b�N�X�̕�(�������s�N�Z���Ŏw��).

	//�`�F�b�N�{�b�N�X�̕\��.
	//bool&�́A�Ăяo�����̕ϐ����̂��̂𑀍삷��.
	static bool CheckBox(
		const char* Label,		//�`�F�b�N�{�b�N�X�̉��ɕ\������郉�x��(���O).
		bool& flag,				//�`�F�b�N��Ԃ��Ǘ�����ϐ�(�Q�Ɠn���ŁAON/OFF��Ԃ𒼐ڕύX����).
		bool isLabel = true);	//���x����\���Afalse: ���x����\��(�ȗ�����true).

	//�O���t��\��.
	static void Graph(
		const char* Label,							//�O���t�̃^�C�g��(���x��)
		std::vector<float>& Data,					//�O���t�ɕ\�����鐔�l�f�[�^�̔z��(�܂���O���t��_�O���t�̌�).
		const ImVec2& Size = ImVec2(300.f, 300.f));	//�O���t�̃T�C�Y(����300�A����300)���ȗ��\.

private:
	ImGuiManager();

	//������R�s�[���폜.
	ImGuiManager(const ImGuiManager& rhs) = delete;
	ImGuiManager& operator = (const ImGuiManager& rhs) = delete;

};