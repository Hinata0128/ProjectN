#include "CollisionManager.h"

#include "Effect/Effect.h"

#include <algorithm>

#include "System//02_Singleton//Timer//Timer.h"



CollisionManager::CollisionManager()
    : m_pPlayer(nullptr)
{
}

CollisionManager::~CollisionManager()
{
    Release();
}

void CollisionManager::Update()
{
    AllCollider(); 
}

void CollisionManager::Draw()
{
#ifdef _DEBUG
    //スフィア描画
    for (const auto& sphere : m_pBSphere)
    {
        if (sphere) sphere->Draw();	
    }

    //ボックス描画
    for (const auto& box : m_pBBox)
    {
        if (box) box->Draw();		
    }
#endif
}

//------------------------- Create -------------------------
void CollisionManager::Create()
{
    m_pBSphere.clear();	//スフィアクリア.
    m_pBBox.clear();	//ボックスクリア.
}

//------------------------- Release -------------------------
void CollisionManager::Release()
{
    m_pBSphere.clear();
    m_pBBox.clear();
    m_pPlayer.reset();
    m_vEnemies.clear();
    m_PlayerShots.clear();
    m_EnemyShots.clear();
}

void CollisionManager::AddSphere(const std::shared_ptr<BoundingSphere>& sphere)
{
    if (sphere) m_pBSphere.push_back(sphere); //スフィア登録.
}

void CollisionManager::AddBox(const std::shared_ptr<BoundingBox>& box)
{
    if (box) m_pBBox.push_back(box); //ボックス登録.
}

void CollisionManager::Clear()
{
}

void CollisionManager::AllCollider()
{
    if (!m_pPlayer) return;

    //プレイヤーの位置を同期
    m_pPlayer->GetBoundingSphere().SetPosition(m_pPlayer->GetPosition());

    for (auto enemy : m_vEnemies)
    {
        if (!enemy) continue;

        enemy->GetBoundingSphere().SetPosition(enemy->GetEnemyPosition());

        for (auto pShot : m_PlayerShots)
        {
            if (!pShot || !pShot->IsDisplay() || !pShot->IsActive()) continue;

            pShot->GetBoundingSphere().SetPosition(pShot->GetPosition());

            if (pShot->GetBoundingSphere().IsHit(enemy->GetBoundingSphere()))
            {
                pShot->SetDisplay(false);
                pShot->SetActive(false);
                pShot->SetPosition(D3DXVECTOR3(0.f, -100.f, 0.f));

                enemy->SetEnemyPosition(D3DXVECTOR3(0.f, 0.f, 20.f));

                Effect::Play(Effect::Test0, enemy->GetEnemyPosition()); 
                break;
            }
        }
    }

    for (auto eShot : m_EnemyShots)
    {
        if (!eShot || !eShot->IsDisplay() || !eShot->IsActive()) continue;

        eShot->GetBoundingSphere().SetPosition(eShot->GetPosition());

        if (eShot->GetBoundingSphere().IsHit(m_pPlayer->GetBoundingSphere()))
        {
            OutputDebugStringA("Enemy Shot hit Player!\n");
            eShot->SetDisplay(false);
            eShot->SetActive(false);

            Effect::Play(Effect::Test0, eShot->GetPosition()); 
            break;
        }
    }
}

bool CollisionManager::CheckSphereSphere(const BoundingSphere& a, const BoundingSphere& b)
{
    return a.IsHit(b);
}

bool CollisionManager::CheckBoxBox(const BoundingBox& a, const BoundingBox& b)
{
    return a.IsHit(b);
}

bool CollisionManager::CheckSphereBox(const BoundingSphere& sphere, const BoundingBox& box)
{
    // 球体とAABBの判定（後で拡張可能）.
    // 今は簡易版として中心距離で判定.
    D3DXVECTOR3 closest;
    closest.x = std::max<float>(box.GetMin().x, std::min<float>(sphere.GetPostion().x, box.GetMax().x));
    closest.y = std::max<float>(box.GetMin().y, std::min<float>(sphere.GetPostion().y, box.GetMax().y));
    closest.z = std::max<float>(box.GetMin().z, std::min<float>(sphere.GetPostion().z, box.GetMax().z));

    D3DXVECTOR3 diff = sphere.GetPostion() - closest;
    return D3DXVec3Length(&diff) <= sphere.GetRadius();
}
