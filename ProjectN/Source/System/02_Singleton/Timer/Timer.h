#pragma once
#include <chrono>

/********************************************************************
*	Timer�N���X.
**/

class Timer final
{
public:
	~Timer();

	static Timer& GetInstance();

	void Update();

	//�����̎��Ԍv��.
	float DeltaTime() const;
	//�Q�[���J�n����̑��o�ߎ���.
	float ElapsedTime() const;

private:
	Timer();
	Timer(const Timer&) = delete;
	Timer& operator = (const Timer&) = delete;
private:
	float m_DeltaTime;
	std::chrono::high_resolution_clock::time_point m_lastTimer;

	float m_elapsedTime;
};