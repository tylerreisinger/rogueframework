#ifndef FRAMEPERFORMANCECOUNTER_H_
#define FRAMEPERFORMANCECOUNTER_H_

#include <chrono>

namespace rf
{

class FramePerformanceCounter
{
public:
	typedef std::chrono::high_resolution_clock Clock;

	FramePerformanceCounter();
	~FramePerformanceCounter() = default;

	///Mark the beginning of a frame.
	void frameStart();

	///Mark the end of the game logic for a frame. This would be right before a
	///delay function is called.
	void frameLogicEnd();

	double frameRate() const {return m_frameRate;}

protected:

	std::chrono::milliseconds m_fpsSampleDuration;

	Clock::time_point m_fpsCountStartTime;
	int m_frameCount = -1;

	double m_frameRate = 0;
};

}

#endif
