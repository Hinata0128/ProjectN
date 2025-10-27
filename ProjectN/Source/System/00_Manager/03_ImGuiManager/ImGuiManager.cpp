#include "System/00_Manager/03_ImGuiManager/ImGuiManager.h"
#include "DirectX/DirectX11.h"
#include <utility>

//�g�p���Ă���t�H���g.
constexpr char FONT_FILE_PATH[] = "Data//ImGui//Font//NotoSansJP-SemiBold.ttf";
//�t�H���g�T�C�Y.
constexpr float FONT_SIZE = 18.f;
// �O���t��UI�v�f�Ȃǂɂ����āA�������C����ŏ������炵�ĕ\�����邽�߂̃I�t�Z�b�g�l�i100�s�N�Z���j
// constexpr ���g�����ƂŁA�R���p�C�����ɒ萔�Ƃ��Ĉ����A�œK�������
constexpr float SAMALINE_OFFSET = 100.f;    //ImGui::SameLine�̃I�t�Z�b�g�l.

ImGuiManager::ImGuiManager()
{

}

ImGuiManager::~ImGuiManager()
{

}

//�C���X�^���X���ɂ�����ɏ���.
ImGuiManager* ImGuiManager::GetInstance()
{
    static ImGuiManager Instance;
    return &Instance;
}

HRESULT ImGuiManager::Init(HWND hWnd)
{
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;   //�h�b�L���O��L���ɂ���.
    //�}���`�r���[�|�[�g(�����̃E�B���h�E)�ƃv���b�g�t�H�[���E�B���h�E�̗L����.
    //���킵���₭
    //ImGui�̃}���`�r���[�|�[�g�@�\��L����(UI�𕡐��E�B���h�E�Ƃ��ĕ\���\�ɂ���).
    // �����������킵������
    //�����E�B���h�E�\����L����.
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; //EnableMulti-Viewport / Platform Windows
    //�O�̃t���[������o�ߎ��Ԃ�ݒ�(�b�P��)�B�����ł́A1�t���[�� = 1/60�b (=60FPS��z��).
    io.DeltaTime = 1.f / 60.f;    //time elapsed since the previous frame (in seconds).
    io.DisplaySize.x = WND_W;   //���̉摜�T�C�Y.
    io.DisplaySize.y = WND_H;   //�c�̉摜�T�C�Y.

    //�t�H���g��ǂݍ���.
    // io.Fonts->AddFontFromFileTTF �֐����g���āATrueType�t�H���g�iTTF�j�t�@�C��������{��Ή��̃t�H���g��ǉ�����B
    ImFont* font = io.Fonts->AddFontFromFileTTF(
        FONT_FILE_PATH,                         //�ǂݍ��ރt�H���g�t�@�C���̃p�X(��: "fonts/MSGothic.ttc" �Ȃ�)
        FONT_SIZE,                              //�t�H���g�T�C�Y(�s�N�Z���P��)
        NULL,                                   //�t�H���g�ݒ�(NULL�Ńf�t�H���g�ݒ���g�p).
        io.Fonts->GetGlyphRangesJapanese());    //���{��̕����Z�b�g(�Ђ炪�ȁE�J�^�J�i�E����)���܂ރO���t�͈͂��擾���Đݒ�/

    //Setup Dear ImGui style
    //ImGui::StyleColorsDark();
    //UI�̕��������F�ɂ���.
    ImGui::StyleColorsDark();
    //�X�^�C���ݒ�ɃA�N�Z�X���邽�߂̎Q�Ƃ��擾.
    ImGuiStyle& style = ImGui::GetStyle();
    //�}���`�r���[�|�[�g(Platform Windows)���L���ȏꍇ�ɒǉ��X�^�C����ݒ�.
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.f;                 //�E�B���h�E�̊p�̊ۂ݂��[����(�l�p��)����.
        style.Colors[ImGuiCol_WindowBg].w = 1.f;    //�E�B���h�E�w�i�̓����x��1(���S�ɕs����)�ɂ���.
    }
    
    if (ImGui_ImplWin32_Init(hWnd) == false) { return E_FAIL; };
    if (ImGui_ImplDX11_Init(DirectX11::GetInstance()->GetDevice(), DirectX11::GetInstance()->GetContext()) == false) { return E_FAIL; }

    return S_OK;
}

void ImGuiManager::Relese()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

//�t���[���̐ݒ�.
void ImGuiManager::NewFrameSetting()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
}

//�`��.
void ImGuiManager::Render()
{
    //ImGuiIO�^��io��void�Ƃ��Ďg�p�H
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::Render();

    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }
}

//���̓{�b�N�X�\��.
template<typename T>
bool ImGuiManager::Input(const char* label,
    T& value,
    bool isLabel,
    float step,
    float stepFast,
    const char* format,
    ImGuiInputTextFlags flags)
{
    //���x���̕�������쐬.
    const std::string newlabel = "##" + std::string(label);

    //���x���ݒ肪�L���Ȃ烉�x����\��.
    if (isLabel == true)
    {
        //���x��(�e�L�X�g)��\������.
        ImGui::Text(label);
        //���x���ƃX���C�_�[�𓯂��s�ɔz�u���邽�߂ɉ����тɂ���.
        //SAMALINE_OFFSET�����E�ɂ��炵�ĕ\��.
        ImGui::SameLine(SAMALINE_OFFSET);
    }

    // int�^�ŕ\��.
    if constexpr (std::is_same_v<T, int>) 
    {
        return ImGui::InputInt(newlabel.c_str(),
            &value,
            static_cast<int>(step),
            static_cast<int>(stepFast),
            flags);
    }
    // float�^�ŕ\��.
    else if constexpr (std::is_same_v<T, float>) 
    {
        return ImGui::InputFloat(newlabel.c_str(),
            &value,
            step,
            stepFast,
            format,
            flags);
    }
    // double�^�ŕ\��.
    else if constexpr (std::is_same_v<T, double>) 
    {
        return ImGui::InputDouble(newlabel.c_str(),
            &value,
            static_cast<double>(step),
            static_cast<double>(stepFast),
            format,
            flags);
    }
    // D3DXVECTOR2�^�ŕ\��.
    else if constexpr (std::is_same_v<T, D3DXVECTOR2>) 
    {
        //D3DXVECTOR2�^���g�p����Ƃ���Input�֐�.
        return ImGui::InputFloat2(newlabel.c_str(),
            &value.x,
            format,
            flags);
    }
    // D3DXVECTOR3�^�ŕ\��.
    else if constexpr (std::is_same_v<T, D3DXVECTOR3>) 
    {
        //D3DXVECTOR3�^���g�p����Ƃ���Input�֐�.
        return ImGui::InputFloat3(newlabel.c_str(),
            &value.x,
            format,
            flags);
    }
    // string�^�ŕ\��.
    else if constexpr (std::is_same_v<T, std::string>) 
    {
        char buffer[256];
        strncpy_s(buffer,
            value.c_str(),
            sizeof(buffer));
        //std::string���g�p����Ƃ���Input�֐�.
        if (ImGui::InputText(newlabel.c_str(),
            buffer,
            sizeof(buffer)))
        {
            value = buffer;
            return true;
        }
    }
    return false;
}
template bool ImGuiManager::Input<int>(const char*,
    int&,
    bool,
    float,
    float,
    const char*,
    ImGuiInputTextFlags);
template bool ImGuiManager::Input<float>(const char*,
    float&,
    bool,
    float,
    float,
    const char*,
    ImGuiInputTextFlags);
template bool ImGuiManager::Input<double>(const char*,
    double&,
    bool,
    float,
    float,
    const char*,
    ImGuiInputTextFlags);
template bool ImGuiManager::Input<D3DXVECTOR2>(const char*,
    D3DXVECTOR2&,
    bool,
    float,
    float,
    const char*,
    ImGuiInputTextFlags);
template bool ImGuiManager::Input<D3DXVECTOR3>(const char*,
    D3DXVECTOR3&,
    bool,
    float,
    float,
    const char*,
    ImGuiInputTextFlags);
template bool ImGuiManager::Input<std::string>(const char*,
    std::string&,
    bool,
    float,
    float,
    const char*,
    ImGuiInputTextFlags);

//�X���C�_�[�̕\��.
template<typename T>
void ImGuiManager::Slider(const char* label, T& value, T valueMin, T valueMax, bool isLabel)
{
    //���x���̕�������쐬.
    const std::string newlabel = "##" + std::string(label);

    //���x���ݒ肪�L���Ȃ烉�x����\��.
    if (isLabel == true)
    {
        //���x��(�e�L�X�g)��\������.
        ImGui::Text(label);
        //���x���ƃX���C�_�[�𓯂��s�ɔz�u���邽�߂ɉ����тɂ���.
        //SAMALINE_OFFSET�����E�ɂ��炵�ĕ\��.
        ImGui::SameLine(SAMALINE_OFFSET);
    }

    //int�^�ŕ\��.
    if constexpr (std::is_same_v<T, int>)
    {
        ImGui::SliderInt(
            newlabel.c_str(),
            &value,
            valueMin,
            valueMax);
    }
    //float�^�ŕ\��
    else if constexpr (std::is_same_v<T, float>)
    {
        ImGui::SliderFloat(
            newlabel.c_str(),
            &value,
            valueMin,
            valueMax);
    }
}
template void ImGuiManager::Slider<int>(
    const char*,
    int&,
    int,
    int, 
    bool);
template void ImGuiManager::Slider<float>(const char*,
    float&,
    float, 
    float,
    bool);

//�R���{�{�b�N�X.
std::string ImGuiManager::Combo(const char* Label,
    std::string& NowItem,
    const std::vector<std::string>& List,
    bool isLabel,
    float space)
{
    //�I�𒆂̃��X�g�̗v�f�ԍ�.
    int No = 0;

    //���X�g�̍ő吔���擾.
    const int List_Max = static_cast<int>(List.size());

    //���ݑI������Ă���List�̗v�f�ԍ���ۑ�.
    for (int i = 0; i < List_Max; ++i)
    {
        if (List[i] == NowItem)
        {
            No = i;
            break;
        }
    }

    //���x���ݒ肪�L���Ȃ�e�L�X�g��\��.
    if (isLabel == true)
    {
        ImGui::Text(Label);
        ImGui::SameLine(space);
    }

    //�R���{�{�b�N�X�̕\��.
    if (ImGui::BeginCombo(std::string("##" + std::string(Label)).c_str(),
        NowItem.c_str()))
    {
        const int Size = static_cast<int>(List.size());
        for (int i = 0; i < Size; ++i)
        {
            //�I����Ԃ��擾.
            bool is_Selected = (NowItem == List[i]);

            //�I�𒆂̃��X�g�̗v�f�ԍ����X�V����.
            if (ImGui::Selectable(List[i].c_str(),
                is_Selected))
            {
                No = i;
            }

            //�I�����ꂽList�Ƀt�H�[�J�X��ݒ�.
            if (is_Selected)
            {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }
    return NowItem = List[No];
}

//�`�F�b�N�{�b�N�X�̕\��.
bool ImGuiManager::CheckBox(
    const char* label,
    bool& flag,
    bool isLabel)
{
    //���x���ݒ肪�L���Ȃ�e�L�X�g��\��.
    if (isLabel == true)
    {
        //���x��(�e�L�X�g)��\������.
        ImGui::Text(label);
        //���x���ƃX���C�_�[�𓯂��s�ɔz�u���邽�߂ɉ����тɂ���.
        //SAMALINE_OFFSET�����E�ɂ��炵�ĕ\��.
        ImGui::SameLine(SAMALINE_OFFSET);
    }
    return ImGui::Checkbox(
        std::string("##" + std::string(label)).c_str(),
        &flag);
}

//�O���t��\��.
void ImGuiManager::Graph(
    const char* Label,
    std::vector<float>& Data,
    const ImVec2& Size)
{
    ImGui::PlotLines(std::string("##" + std::string(Label)).c_str(),
        Data.data(), static_cast<int>(Data.size()),
        0, nullptr,
        FLT_MAX,
        FLT_MAX,
        Size);
}