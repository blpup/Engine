#include "Allocator.h"
using namespace GameEngine;

GameEngine::Allocator::Allocator(size_t size, void* start)
{
	m_start = start;
	m_size = size;
	m_usedMemory = 0;
	m_numAllocations = 0;
}

GameEngine::Allocator::~Allocator()
{
	assert(m_numAllocations == 0 && m_usedMemory == 0);
	m_start = nullptr;
	m_size = 0;
}
