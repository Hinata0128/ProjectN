#include "Player.h"
#include "System/00_Manager/00_SkinMeshManager/SkinMeshManager.h"
#include "GameObject//StaticMeshObject//ShotBase//PShot//PShot.h"

#include "System/00_Manager/02_PShotManager/PShotManager.h"

#include "System/02_Singleton/Timer//Timer.h"

constexpr float zero = 0.0f;

Player::Player()
    :Character()
{
	SkinMesh* raw_mesh = SkinMeshManager::GetInstance()->GetSkinMeshInstance(SkinMeshManager::SkinList::Player);

	auto shared_mesh = std::shared_ptr<SkinMesh>(raw_mesh,[](SkinMesh*){});

	//AttachMesh �� shared_ptr ��n��
	AttachMesh(shared_mesh);
	SetScale(0.04f);
	SetPosition(0.f, 0.f, 0.f);

	//�A�j���[�V�����̑��x��
	m_AnimSpeed = 0.02f;

    m_pShotManager = PShotManager::GetInstance();
    m_BSphere.SetRadius(0.5f);
}

Player::~Player()
{
}

void Player::Update()
{
    m_pMesh->SetAnimSpeed(m_AnimSpeed);

    //���[�J���ϐ��錾�ꏊ.
    constexpr float add_value = 0.1f;

    //�N�[���^�C���̎���.
    float deltaTime = Timer::GetInstance().DeltaTime();

    bool isMoving = false;  // �ړ����Ă��邩�t���O
    int newAnimNo = -1;     // ����Đ����ׂ��A�j���[�V����

    //�N�[���^�C��(0.5f)��0.0f�ɂȂ�����e�𔭎�.
    if (m_CoolTime >= zero)
    {
        m_ShotCoolDown -= deltaTime;
    }

    D3DXVECTOR3  ForwardAndBackward = Player_WS();
    D3DXVECTOR3  LeftAndRight       = Player_AD();

    // �L�[���͂ɂ��ړ�
    if (GetAsyncKeyState('W') & 0x8000)
    {
        m_vPosition += ForwardAndBackward * add_value;
        isMoving = true; 
        newAnimNo = 2;  // ����A�j���[�V����
    }
    if (GetAsyncKeyState('S') & 0x8000)
    {
        m_vPosition -= ForwardAndBackward * add_value;
        isMoving = true;
        newAnimNo = 0;  // ��ރA�j���[�V����
    }
    if (GetAsyncKeyState('D') & 0x8000)
    {
        m_vPosition += LeftAndRight * add_value;
        isMoving = true;
        newAnimNo = 2;  // ����A�j���[�V����
    }
    if (GetAsyncKeyState('A') & 0x8000)
    {
        m_vPosition -= LeftAndRight * add_value;
        isMoving = true;
        newAnimNo = 2;  // ����A�j���[�V����
    }
    if (GetAsyncKeyState(VK_UP) & 0x8000)
    {
        m_vRotation.y += add_value;
    }

    // �ړ����Ă���ꍇ�̂݃A�j���[�V������؂�ւ�
    if (isMoving)
    {
        if (m_AnimNo != newAnimNo)
        {
            m_AnimNo = newAnimNo;
            m_AnimTime = 0.0f;
            m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
        }
    }
    else
    {
        if (m_AnimNo != 0)  // �ҋ@�A�j���[�V������0�Ɖ���
        {
            m_AnimNo = 0;
            m_AnimTime = 0.0f;
            m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
        }
    }

    //�{�[�����W�̎擾
    m_pMesh->GetPosFromBone("blade_l_head", &m_BonePos);

    //�e�����{�^��.
    if (GetAsyncKeyState(VK_SPACE) & 0x8000 && m_ShotCoolDown <= zero)
    {
        //�A�j���[�V������2�Ԃɂ���.
        m_AnimNo = 2;
        //�A�j���[�V�����̎��Ԃ�������.
        m_AnimTime = 0.0f;
        //�A�j���[�V������ύX.
        m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);

        //�e�ϊ��s����쐬.
        D3DXMATRIX matS, matR, matT, playerWorldMatrix;
        D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);
        D3DXMatrixRotationYawPitchRoll(&matR, m_vRotation.y, m_vRotation.x, m_vRotation.z);
        D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
        D3DXMatrixMultiply(&playerWorldMatrix, &matS, &matR);
        D3DXMatrixMultiply(&playerWorldMatrix, &playerWorldMatrix, &matT);

        D3DXVECTOR3 worldBonePos;
        D3DXVec3TransformCoord(&worldBonePos, &m_BonePos, &playerWorldMatrix);

        D3DXVECTOR3 shotPos = worldBonePos + m_ShotOffset;

        D3DXVECTOR3 Dir = Player_WS();
        D3DXVec3Normalize(&Dir, &Dir);
        // Manager �ɒe��ǉ�
        m_pShotManager->AddPlayerShot(shotPos, Dir);

        // �N�[���^�C�����Z�b�g
        m_ShotCoolDown = m_CoolTime;
    }

    // �A�j���[�V�����X�V
    m_pAnimCtrl->AdvanceTime(m_AnimSpeed, nullptr);

    // �e�̍X�V
    m_pShotManager->Update();

    Character::Update();
}


void Player::Draw()
{
	m_pMesh->SetAnimSpeed(m_AnimSpeed);

	Character::Draw();

    m_pShotManager->Draw();
}

void Player::Stop()
{
    if (m_pAnimCtrl)
    {
        // �A�j���[�V�����i�s���~�߂�
        m_pAnimCtrl->AdvanceTime(0.0f, nullptr);

        D3DXTRACK_DESC trackDesc;
        m_pAnimCtrl->GetTrackDesc(0, &trackDesc);
        trackDesc.Enable = FALSE;
        m_pAnimCtrl->SetTrackDesc(0, &trackDesc);
    }
}
//W�ES�̑O�i��ޗp�֐�.
D3DXVECTOR3 Player::Player_WS() const
{
    // Player �̉�]����O�������x�N�g�����v�Z
    D3DXVECTOR3 dir;
    
    dir.x = sinf(m_vRotation.y);
    dir.y = zero;
    dir.z = cosf(m_vRotation.y);
    return dir;

}
//A�ED�̍��E�p�֐�.
D3DXVECTOR3 Player::Player_AD() const
{
    D3DXVECTOR3 dir;
    dir.x = cosf(m_vRotation.y);
    dir.y = zero;
    dir.z = -sinf(m_vRotation.y);
    return dir;
}

