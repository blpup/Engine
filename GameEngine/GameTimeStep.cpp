#include "GameTimeStep.h"
using namespace GameEngine;

GameTimeStep& GameTimeStep::GetInstance()
{
	static GameTimeStep instance;
	return instance;
}

void GameTimeStep::StartTimeStep()
{
	m_startTime = std::chrono::high_resolution_clock::now();
}

void GameTimeStep::EndTimeStep()
{
	m_endingTime = std::chrono::high_resolution_clock::now();
	CalculateAverage();
}

float GameTimeStep::GetSecondsPerFrame()
{
	return m_average;
}

float GameTimeStep::GetFPS()
{
	return 1 / GetSecondsPerFrame();
}

void GameTimeStep::CalculateAverage()
{
	if (m_index == MAX_FRAMES) m_index = 0;
	std::chrono::duration<float> diff = (m_endingTime - m_startTime);
	m_steps[m_index] = diff.count();
	m_index += 1;
	for (size_t i = 0; i < MAX_FRAMES; i++)
	{
		m_average += m_steps[i];
	}
	
	m_average = m_average / MAX_FRAMES;

}
