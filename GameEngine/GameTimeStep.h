#pragma once
#include <time.h>
#include <ctime>
#include <chrono>
#define MAX_FRAMES 80
#define IDEAL_FRAMERATE 1.0f/30.f
namespace GameEngine {
	class GameTimeStep
	{
	public:
		GameTimeStep(GameTimeStep& other) = delete;
		void operator=(const GameTimeStep&) = delete;
		static GameTimeStep& GetInstance();
		void StartTimeStep();
		void EndTimeStep();
		float GetSecondsPerFrame();
		float GetFPS();
	private:
		float m_steps[MAX_FRAMES] = { 0.f };
		float m_average = 0.f;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_startTime;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_endingTime;
		size_t m_index = 0;
		GameTimeStep(void) {};
		void CalculateAverage();
	};
}


