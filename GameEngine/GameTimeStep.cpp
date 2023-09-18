#include "GameTimeStep.h"
#include <thread>
#include <iostream>

using namespace GameEngine;

GameTimeStep& GameTimeStep::GetInstance()
{
	static GameTimeStep instance;
	return instance;
}

void GameTimeStep::StartTimeStep()
{
	m_startTime = Clock::now();
	
}

void GameTimeStep::EndTimeStep()
{
	m_endingTime = Clock::now();
	CalculateAverage();
}

double GameTimeStep::GetSecondsPerFrame()
{
	return m_average;
}

double GameTimeStep::GetFPS()
{
	return 1 / GetSecondsPerFrame();
}

void GameTimeStep::CalculateAverage()
{
	if (m_index == MAX_FRAMES) m_index = 0;
	auto diffInSeconds = std::chrono::duration<double>(m_endingTime - m_startTime).count();
	m_steps[m_index] = diffInSeconds;
	m_index += 1;
	for (size_t i = 0; i < MAX_FRAMES; i++)
	{
		m_average += m_steps[i];
	}
	
	m_average = m_average / MAX_FRAMES;
}
