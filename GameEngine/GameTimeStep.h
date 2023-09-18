#pragma once
#include <time.h>
#include <ctime>
#include <chrono>
#define MAX_FRAMES 10
#define IDEAL_FRAMERATE 1.f/30.f
namespace GameEngine {
	class GameTimeStep
	{
		using Clock = std::chrono::steady_clock;
		using ms = std::chrono::milliseconds;
		using hrc = std::chrono::high_resolution_clock;
		using framePeriod = std::chrono::duration<int32_t, std::ratio<1, 30>>;
	public:
		GameTimeStep(GameTimeStep& other) = delete;
		void operator=(const GameTimeStep&) = delete;
		static GameTimeStep& GetInstance();
		void StartTimeStep();
		void EndTimeStep();
		double GetSecondsPerFrame();
		double GetFPS();
		const float idealFramerate = 1 / 60.f;
	private:
		double m_steps[MAX_FRAMES] = { 0.f };
		double m_average = 0.f;
		std::chrono::time_point<Clock> m_startTime = Clock::now();
		std::chrono::time_point<Clock> m_endingTime = m_startTime;
		size_t m_index = 0;
		GameTimeStep(void) {};
		void CalculateAverage();
	};
}


