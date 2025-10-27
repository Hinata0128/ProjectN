#include "EnemyNomalManager.h"


EnemyNomalManager::EnemyNomalManager()
{
}

EnemyNomalManager::~EnemyNomalManager()
{
}

EnemyNomalManager* EnemyNomalManager::GetInstace()
{
	static EnemyNomalManager s_Instance;
	return &s_Instance;
}

void EnemyNomalManager::Update()
{
	for (size_t i = 0; i < m_pEnemyNomal.size(); ++i)
	{
		if (m_pEnemyNomal[i] != nullptr)
		{
			m_pEnemyNomal[i]->Update();

			//�G�����S���Ă�����폜(���͂Ȃ��̂ł��������ǉ�).
		}
	}
}

void EnemyNomalManager::Draw()
{
	for (size_t i = 0; i < m_pEnemyNomal.size(); ++i)
	{
		if (m_pEnemyNomal[i] != nullptr)
		{
			m_pEnemyNomal[i]->Draw();
		}
	}
}

void EnemyNomalManager::Create()
{
}

void EnemyNomalManager::Release()
{
}

void EnemyNomalManager::ReMoveEnemy(size_t index)
{
	if (index < m_pEnemyNomal.size())
	{
		m_pEnemyNomal.erase(m_pEnemyNomal.begin() + index);   //�R���e�i����v�f���폜.
	}

}

EnemyNomal* EnemyNomalManager::GetEnemyNomal(size_t No)
{
	if (No < m_pEnemyNomal.size())
	{
		return m_pEnemyNomal[No].get();
	}
	return nullptr;
}

size_t EnemyNomalManager::GetEnemyNomalCount() const
{
	return m_pEnemyNomal.size();
}

void EnemyNomalManager::AddEnemy(std::unique_ptr<EnemyNomal> enemy, const D3DXVECTOR3& pos)
{
	enemy->SetEnemyPosition(pos); // �����Ń��b�p�[�֐����g��
	m_pEnemyNomal.push_back(std::move(enemy));
}

std::vector<EnemyNomal*> EnemyNomalManager::GetEnemies()
{
	// ���̃|�C���^���i�[���邽�߂̐V�����x�N�^�[��錾
	std::vector<EnemyNomal*> rawPointers;

	// ������ unique_ptr �̃��X�g�𑖍�
	for (const auto& enemy : m_pEnemyNomal)
	{
		// unique_ptr ���L���ȏꍇ�A���̃|�C���^���擾���ĐV�����x�N�^�[�ɒǉ�
		if (enemy)
		{
			rawPointers.push_back(enemy.get());
		}
	}

	return rawPointers; // �l�Ƃ��ĕԂ�}
}
