#pragma once
#include <chrono>

class Timer
{
public:
	Timer();
	float GetDt();
	float GetTimer();

private:
	std::chrono::steady_clock::time_point m_TimerLast;
};