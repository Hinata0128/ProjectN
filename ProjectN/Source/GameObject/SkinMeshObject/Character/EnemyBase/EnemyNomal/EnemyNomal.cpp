#include "EnemyNomal.h"
#include "System/00_Manager/00_SkinMeshManager/SkinMeshManager.h"
#include "System/00_Manager/04_EnemyNomalShotManager/EnemyNomalShotManager.h"
#include "System/02_Singleton/Timer//Timer.h"

constexpr float zero = 0.0f;

EnemyNomal::EnemyNomal()
    : m_pENShotManager(nullptr)
{
    SkinMesh* raw_mesh = SkinMeshManager::GetInstance()->GetSkinMeshInstance(SkinMeshManager::SkinList::Enemy);
    auto shared_mesh = std::shared_ptr<SkinMesh>(raw_mesh, [](SkinMesh*) {});
    AttachMesh(shared_mesh);

    SetScale(0.002f);
    SetPosition(0.0f, 0.0f, 10.0f);

    m_AnimSpeed = 0.0002f;

    m_pENShotManager = EnemyNomalShotManager::GetInstance();

    m_BSphere.SetRadius(1.5f);

    // �N�[���^�C��������
    m_ShotCoolDown = 0.0f;
    m_CoolTime = 1.0f; // 1�b���Ƃɔ���
}

EnemyNomal::~EnemyNomal() 
{
}

void EnemyNomal::Update()
{
    m_pMesh->SetAnimSpeed(m_AnimSpeed);
    float deltaTime = Timer::GetInstance().DeltaTime();

    // �N�[���^�C�����Z
    m_ShotCoolDown -= deltaTime;
    if (m_ShotCoolDown < 0.0f) m_ShotCoolDown = 0.0f;

    // �{�[�����W�擾
    m_pMesh->GetPosFromBone("entotu_Joint", &m_BonePos);

    // �A�j���[�V�����X�V
    m_pAnimCtrl->AdvanceTime(m_AnimSpeed, nullptr);

    // �e�̔��ˁi�����j
    if (m_ShotCoolDown == 0.0f)
    {
        // �ϊ��s��쐬
        D3DXMATRIX matS, matR, matT, enemyWorldMatrix;
        D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);
        D3DXMatrixRotationYawPitchRoll(&matR, m_vRotation.y, m_vRotation.x, m_vRotation.z);
        D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
        D3DXMatrixMultiply(&enemyWorldMatrix, &matS, &matR);
        D3DXMatrixMultiply(&enemyWorldMatrix, &enemyWorldMatrix, &matT);

        // �{�[�����W�����[���h���W�ɕϊ�
        D3DXVECTOR3 worldBonePos;
        D3DXVec3TransformCoord(&worldBonePos, &m_BonePos, &enemyWorldMatrix);

        D3DXVECTOR3 shotPos = worldBonePos + m_ShotOffset;

        // �e�͏�� -Z ����
        D3DXVECTOR3 Dir = Enemy_WS();
        D3DXVec3Normalize(&Dir, &Dir);

        // �e��ǉ�
        m_pENShotManager->AddEnemyNomalShot(shotPos, Dir);

        // �N�[���^�C�����Z�b�g
        m_ShotCoolDown = m_CoolTime;
    }

    // �e�̍X�V
    m_pENShotManager->Update();

    EnemyBase::Update();
}

void EnemyNomal::Draw()
{
    m_pMesh->SetAnimSpeed(m_AnimSpeed);
    EnemyBase::Draw();
    m_pENShotManager->Draw();
}

// �e�̔�ԕ����i��� -Z�j
D3DXVECTOR3 EnemyNomal::Enemy_WS() const
{
    return D3DXVECTOR3(0.0f, 0.0f, -1.0f);
}
