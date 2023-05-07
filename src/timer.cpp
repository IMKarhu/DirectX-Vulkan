#include "Timer.h"

Timer::Timer()
{
	m_TimerLast = std::chrono::steady_clock::now();
}

float Timer::GetDt()
{
	const auto old = m_TimerLast;
	m_TimerLast = std::chrono::steady_clock::now();
	const std::chrono::duration<float> frameTime = m_TimerLast - old;
	return frameTime.count();
}

float Timer::GetTimer()
{
	return std::chrono::duration<float>(std::chrono::steady_clock::now() - m_TimerLast).count();
}
