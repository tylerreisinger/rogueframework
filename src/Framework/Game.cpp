#include "Game.h"

#include <cassert>

namespace rf
{

Game::Game()
{


}

void Game::run()
{
	initialize();

	m_isRunning = true;

	while(m_isRunning)
	{
		m_frameStartTime = Clock::now();

		update();
		draw();

		auto frameDuration =
				std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(Clock::now() - m_frameStartTime);

		if(m_targetFrameRate > 0)
		{
			double delayTime = (1000.0 / m_targetFrameRate) - frameDuration.count();
			if(delayTime > 0.0)
			{
				SDL_Delay(delayTime);
			}
		}
	}
}

void Game::setTargetFrameRate(double target)
{
	assert(target >= 0.0);

	m_targetFrameRate = target;
}

void Game::stop()
{
	m_isRunning = false;
}

}


