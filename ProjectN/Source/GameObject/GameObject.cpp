#include "GameObject.h"

//�R���X�g���N�^.
GameObject::GameObject()
	: m_vPosition	{}
	, m_vRotation	( 0.0f, 0.0f, 0.0f )
	, m_vScale		( 1.0f, 1.0f, 1.0f )
{
}

//�f�X�g���N�^.
GameObject::~GameObject()
{
}