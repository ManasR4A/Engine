#pragma once
#include "stdint.h"

// this is HeapManager class interface.

namespace Engine
{
	struct BlockDescriptor
	{
		size_t								SizeOfAllocation;
		size_t								UserMemorySize;
		void* UserMemoryPointer;
		BlockDescriptor* NextBlockDescriptor;
		BlockDescriptor* PrevDescriptor;
	};

	class HeapManager
	{
	public:
		// allocates memory. named with a underscore to resolve name clash 
		HeapManager* create(void* i_pHeapMemory, size_t i_HeapMemorySize);

		// allocation with alignment. returns a block of memory with a given alignment
		void* _alloc(size_t i_RequiredMemeory);

		// frees an allocation
		void* _alloc(size_t i_RequiredMemeory, unsigned int i_alignment);

		BlockDescriptor* coalesce(BlockDescriptor* i_LeftBlock, BlockDescriptor* i_RightBlock);

		// attempt to merge abutting blocks.
		bool _free(void* i_ptr);

		// tells us the size of the largest free block
		void collect();

		// tells us how much total memory is available
		size_t getLargestFreeBlock() const;

		// tells us if a pointer is within this HeapManagers managed memory
		size_t getTotalFreeMemory() const;

		// tells us if this pointer is an outstanding allocation from this block
		bool Contains(void* i_ptr) const;

		// a debugging helper function to show us all the free blocks.
		bool IsAllocated(void* i_ptr) const;

		// a debugging helper function to show us all the outstanding blocks.
		void ShowFreeBlocks() const;

	private:
		// defining some namespace global variables
		HeapManager* PointerToHeap = nullptr;
		size_t									MaxHeapSize = 0;
		size_t									OutstandingMemory = 0;
		size_t									FreeMemory = 0;
		uint8_t* TempMemoryPointer = nullptr;
		uint8_t* FreeMemoryPtr = nullptr;

		// defining the HEADS of Allocated list, Free list and defining a temporary list node pointer
		BlockDescriptor* AllocationList = nullptr;
		BlockDescriptor* FreeList = nullptr;
		BlockDescriptor* TempListTraverse = nullptr;


	};
}

