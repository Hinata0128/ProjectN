#include "Character.h"

Character::Character()
	: SkinMeshObject()
	, m_ShotOffset(0.0f, 1.5f, 1.0f)

	, m_ShotCoolDown(0.0f)
	//�X�̏��������l��ݒ肷�邱�ƂŔ��˃��[�g���オ�����艺�������肷��.
	, m_CoolTime(0.0f)
{
}

Character::~Character()
{
}

void Character::Update()
{
	SkinMeshObject::Update();
}

void Character::Draw()
{
	SkinMeshObject::Draw();
}
