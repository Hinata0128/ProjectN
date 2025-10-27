#include "Portal.h"

#include "System//00_Manager//01_StaticMeshManager//StaticMeshManager.h"

Portal::Portal()
{
	AttachMesh(*StaticMeshManager::GetInstance()->GetMeshInstance(StaticMeshManager::CMeshList::Portal));

	SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
	//�|�[�^���̈ꎞ�I�ȕ\���ʒu.
	SetPosition(0.0f, 0.0f, 5.0f);
}

Portal::~Portal()
{
}

void Portal::Update()
{
}

void Portal::Draw()
{
	StaticMeshObject::Draw();
}
