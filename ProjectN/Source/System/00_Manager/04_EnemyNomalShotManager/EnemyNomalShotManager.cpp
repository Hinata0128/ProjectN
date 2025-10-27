#include "EnemyNomalShotManager.h"

EnemyNomalShotManager* EnemyNomalShotManager::m_pInstance = nullptr;

EnemyNomalShotManager::EnemyNomalShotManager()
{
}

EnemyNomalShotManager::~EnemyNomalShotManager()
{
}

EnemyNomalShotManager* EnemyNomalShotManager::GetInstance()
{
	static EnemyNomalShotManager s_Instance;	//�B��̃C���X�^���X����.
	return &s_Instance;
}

void EnemyNomalShotManager::Update()
{
	for (auto it = m_EnemyNomalShot.begin(); it != m_EnemyNomalShot.end();)
	{
		(*it)->Update();	//�e�̍X�V����.

		if (!(*it)->IsActive())	//��A�N�e�B�u�Ȓe�͍폜.
		{
			it = m_EnemyNomalShot.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void EnemyNomalShotManager::Draw()
{
	for (std::unique_ptr<EnemyNomalShot>& ENomalShot : m_EnemyNomalShot)
	{
		ENomalShot->Draw();	//�e�̕`�揈��.
	}
}

void EnemyNomalShotManager::AddEnemyNomalShot(const D3DXVECTOR3& Pos, const D3DXVECTOR3& InitDirecton)
{
	constexpr float Speed = 0.05f;	//�e�̑��x�ݒ�.

	auto ENomalShot = std::make_unique<EnemyNomalShot>();	//�e�̐���.

	ENomalShot->Reload(Pos, InitDirecton, Speed);	//�e�̏�����.

	ENomalShot->SetDisplay(true);	//�\���L����.

	m_EnemyNomalShot.push_back(std::move(ENomalShot));	//���X�g�ɒǉ�.
}

void EnemyNomalShotManager::ReMoveEnemyNomalShot(size_t index)
{
	if (index < m_EnemyNomalShot.size())
	{
		m_EnemyNomalShot.erase(m_EnemyNomalShot.begin() + index);	//�w��e�폜.
	}
}

const std::vector<std::unique_ptr<EnemyNomalShot>>& EnemyNomalShotManager::GetEnemyNomalShot() const
{
	return m_EnemyNomalShot;	//�e���X�g�ԋp.
}

EnemyNomalShot* EnemyNomalShotManager::GetEnemyNomalShot(size_t No)
{
	if (No < m_EnemyNomalShot.size())
	{
		return m_EnemyNomalShot[No].get();	//�w��e�ԋp.
	}
	return nullptr;
}

size_t EnemyNomalShotManager::GetEnemyNomalShotCount() const
{
	return m_EnemyNomalShot.size();	//�e���ԋp.
}

std::vector<EnemyNomalShot*> EnemyNomalShotManager::GetShots()
{
	// ���̃|�C���^���i�[���邽�߂̐V�����x�N�^�[��錾
	std::vector<EnemyNomalShot*> rawPointers;

	// ������ unique_ptr �̃��X�g�𑖍�
	for (const auto& shot : m_EnemyNomalShot)
	{
		// unique_ptr ���L���ȏꍇ�A���̃|�C���^���擾���ĐV�����x�N�^�[�ɒǉ�
		if (shot)
		{
			rawPointers.push_back(shot.get());
		}
	}
	return rawPointers; // �l�Ƃ��ĕԂ�
}