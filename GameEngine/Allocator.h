#pragma once
#include <cstdint>
#include <assert.h>

namespace GameEngine {
	class Allocator
	{
	public:
		Allocator(size_t size, void* start);
		virtual ~Allocator();
		virtual void* allocate(size_t size, uint8_t alignment = 4) = 0;
		virtual void deallocate(void* p) = 0;
		void* getStart() const { return m_start; }
		size_t getSize() const { return m_size; }
		size_t getUsedMemory() const { return m_usedMemory; }
		size_t getNumAllocations() const { return m_numAllocations; }

	protected:
		void* m_start;
		size_t m_size;
		size_t m_usedMemory;
		size_t m_numAllocations;
	public:
		template <typename T>
		T* allocateNew(Allocator& allocator) {
			return new (allocator.allocate(sizeof(T), __alignof(T))) T;
		}

		template <typename T>
		T* allocateNew(Allocator& allocator, const T& t) {
			return new (allocator.allocate(sizeof(T), __alignof(T))) T(t);
		}

		template <typename T>
		void deallocateDelete(Allocator& allocator, T& object) {
			object.~T();
			allocator.deallocate(&object);
		}

		template <typename T>
		T* allocateArray(Allocator& allocator, size_t length) {
			assert(length != 0);
			uint8_t headerSize = sizeof(size_t) / sizeof(T);
			if (sizeof(size_t) % sizeof(T) > 0) headerSize += 1;

			T* p = ((T*)allocator.allocate(sizeof(T) * (length + headerSize), __alignof(T))) + headerSize;
			*(((size_t*)p) - 1) = length;

			for (size_t i = 0; i < length; i++)
				new (&p) T;
			return p;
		}

		template <typename T>
		void deallocateArray(Allocator& allocator, T* array) {
			assert(array != nullptr);
			size_t length = *(((size_t*)array) - 1);
			for (size_t i = 0; i < length; i++) array.~T();

			uint8_t headerSize = sizeof(size_t) / sizeof(T);
			if (sizeof(size_t) % sizeof(T) > 0)
				headerSize += 1;
			allocator.deallocate(array = headerSize);
		}

		inline void* alignForward(void* address, uint8_t alignment) {
			//return (void*)( ( reinterpret_cast<uint8_t*>(address) + static_cast<uint8_t>(alignment - 1) ) & static_cast<uint8_t>(~(alignment - 1)) );
		}

		inline uint8_t alignForwardAdjutment(const void* address, uint8_t alignment) {
			//uint8_t adjustment = alignment - (reinterpret_cast<uint8_t*>(address) & static_cast<uint8_t*>(alignment - 1));
			//if (adjustment == alignment) return 0;
			//return adjustment;
		}

	};
}


