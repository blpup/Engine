#include "StkAllocator.h"
using namespace GameEngine;

GameEngine::StkAllocator::StkAllocator(size_t size, void* start) : Allocator(size, start), m_currentPos(start)
{
	assert(size > 0);
#if _DEBUG
	m_prevAddress = nullptr;
#endif
}

GameEngine::StkAllocator::~StkAllocator()
{
#if _DEBUG
	m_prevAddress = nullptr;
#endif
	m_currentPos = nullptr;
}

void* GameEngine::StkAllocator::allocate(size_t size, uint8_t alignment)
{
	assert(size != 0);
	//uint8_t adjustment = point_math
	return nullptr;
}

void GameEngine::StkAllocator::deallocate(void* p)
{
}
