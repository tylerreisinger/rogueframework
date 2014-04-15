#ifndef GAME_H_
#define GAME_H_

#include <chrono>

#include <SDL2/SDL.h>

class Game
{
public:
	typedef std::chrono::high_resolution_clock Clock;

	Game();
	virtual ~Game() = default;

	Game(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator =(const Game&) = delete;
	Game& operator =(Game&&) = delete;

	virtual void run();

	///@brief Set the target frame rate for the Game.
	///@details A value of zero means no frame rate limiting.
	///The default value is 0.
	void setTargetFrameRate(double target);

	double getTargetFrameRate() const {return m_targetFrameRate;}

protected:

	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void initialize() = 0;

	bool m_isRunning = false;
	Clock::time_point m_frameStartTime;

private:

	double m_targetFrameRate = 0.0;
};

#endif
