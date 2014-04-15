#include "FramePerformanceCounter.h"

FramePerformanceCounter::FramePerformanceCounter()
{

}

void FramePerformanceCounter::frameStart()
{
	///Time since we began timing.
	auto elapsed = Clock::now() - m_fpsCountStartTime;

	if(elapsed >= m_fpsSampleDuration)
	{
		m_frameRate = m_frameCount / std::chrono::duration_cast<std::chrono::seconds>(elapsed).count();
		m_frameCount = 0;
		m_fpsCountStartTime = Clock::now();
	}
}

void FramePerformanceCounter::frameLogicEnd()
{
	m_frameCount += 1;
}
