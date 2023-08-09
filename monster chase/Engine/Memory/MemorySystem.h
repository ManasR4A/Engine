#pragma once

#include "HeapManager.h"
#include "FixSizeAllocater.h"

namespace Engine
{
	namespace MemoryManager
	{

		bool Initialize();

		bool Shutdown();

		bool ExpandMemory();

		bool CoalasePages();

		// size of each page of memory taken from the OS for custom heap allocator to work on.
		const size_t _PAGE_SIZE = 1024 * 1024;

		/* Has all the memory pages assigned to the memory manager.
			Directly affects the memory footprint of the Engine.
		*/ 
		void* pPages[10] = { nullptr };
	}

	//void* operator new (size_t i_mem);

	//void operator delete(void*);


	class HeapSystem
	{

	public:
		// Defining the Full Heap and the FSAs based on the numbers given in the assignment
		HeapManager* FullHeap;

		// Argument list = size of block, numbre of blocks, ptr to the full heap
		FixSizeAllocater* FSA16, * FSA32, * FSA96;

		// InitializeMemorySystem - initialize your memory system including your HeapManager and some FixedSizeAllocators
		bool InitializeHeapSystem(void* i_pHeapMemory, size_t i_sizeHeapMemory);

		// Collect - coalesce free blocks in attempt to create larger blocks
		void Collect();

		// DestroyMemorySystem - destroy your memory systems
		void DestroyMemorySystem();

		void* _malloc(size_t i_size);

		void _free(void* i_ptr);

		//void* operator new(size_t i_size, MemorySystem * i_MS);

		//void operator delete(void* i_ptr, MemorySystem * MS);

		//void* operator new[](size_t i_size, MemorySystem* MS);

		//void operator delete[](void* i_ptr, MemorySystem* MS);

	};
}
