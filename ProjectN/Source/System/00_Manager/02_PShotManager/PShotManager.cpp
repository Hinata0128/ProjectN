#include "PShotManager.h"

PShotManager* PShotManager::m_pInstance = nullptr;

PShotManager::PShotManager()
{
}

PShotManager::~PShotManager()
{
}

PShotManager* PShotManager::GetInstance()
{
	static PShotManager s_Instance;	//�B��̃C���X�^���X.
	return &s_Instance;
}

void PShotManager::Update()
{
	for (auto it = m_PlayerShot.begin(); it != m_PlayerShot.end();)
	{
		(*it)->Update();	//�e�̍X�V����.

		if (!(*it)->IsActive())	//�����ɂȂ����e�͍폜.
		{
			it = m_PlayerShot.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void PShotManager::Draw()
{
	for (auto& shot : m_PlayerShot)
	{
		shot->Draw();	//�e�̕`�揈��.
	}
}

void PShotManager::AddPlayerShot(const D3DXVECTOR3& Pos, const D3DXVECTOR3& InitDirection)
{
	constexpr float Speed = 0.05f;	//�e��.

	auto PlayerShot = std::make_unique<PShot>();	//�V�K�e����.
	PlayerShot->Reload(Pos, InitDirection, Speed);	//�ʒu�E�����E���x��ݒ�.
	PlayerShot->SetDisplay(true);	//�`��ON.

	m_PlayerShot.push_back(std::move(PlayerShot));	//���X�g�ɒǉ�.
}

void PShotManager::ReMovePlayerShot(size_t index)
{
	if (index < m_PlayerShot.size())
	{
		m_PlayerShot.erase(m_PlayerShot.begin() + index);	//�w��e���폜.
	}
}

const std::vector<std::unique_ptr<PShot>>& PShotManager::GetPlayerShot()const
{
	return m_PlayerShot;	//�e���X�g��Ԃ�.
}

PShot* PShotManager::GetPlayerShot(size_t No)
{
	if (No < m_PlayerShot.size())
	{
		return m_PlayerShot[No].get();	//�w��e���擾.
	}
	return nullptr;	//�͈͊O.
}

size_t PShotManager::GetPlayerShotCount()const
{
	return m_PlayerShot.size();	//�e�̑�����Ԃ�.
}

std::vector<PShot*> PShotManager::GetShots()
{
	std::vector<PShot*> rawPointers;
	for (const auto& shot : m_PlayerShot)
	{
		if (shot)
		{
			rawPointers.push_back(shot.get());
		}
	}
	return rawPointers; // �l�Ƃ��ĕԂ�
}