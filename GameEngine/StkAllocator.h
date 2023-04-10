#pragma once
#include "Allocator.h"
#include <assert.h>
namespace GameEngine {
	class StkAllocator : public Allocator
	{
	public:
		StkAllocator(size_t size, void* start);
		~StkAllocator();
		void* allocate(size_t size, uint8_t alignment) override;
		void deallocate(void* p) override;
	private:
		StkAllocator(const StkAllocator&);
		StkAllocator& operator=(const StkAllocator&);

		struct AllocationHeader {
		#if _DEBUG
			void* prev_address;
		#endif
			uint8_t adjustment;
		};
	#if _DEBUG
		void* m_prevAddress;
	#endif
		void* m_currentPos;
	};
}


