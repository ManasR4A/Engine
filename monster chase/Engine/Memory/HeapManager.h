#pragma once
#include "stdint.h"

// this is HeapManager class interface.


struct BlockDescriptor
{	
	size_t								SizeOfAllocation;
	size_t								UserMemorySize;
	void *								UserMemoryPointer;
	BlockDescriptor *					NextBlockDescriptor;
	BlockDescriptor *					PrevDescriptor;
};

class HeapManager
{
public:
	HeapManager* create(void* i_pHeapMemory, size_t i_HeapMemorySize, unsigned int i_numDescriptors);
	// allocates memory. named with a underscore to resolve name clash 

	void* _alloc(size_t i_RequiredMemeory);
	// allocation with alignment. returns a block of memory with a given alignment

	void* _alloc(size_t i_RequiredMemeory, unsigned int i_alignment);
	// frees an allocation

	BlockDescriptor * coalesce(BlockDescriptor * i_LeftBlock, BlockDescriptor * i_RightBlock);

	bool _free(void* i_ptr);
	// attempt to merge abutting blocks.

	void collect();
	// tells us the size of the largest free block

	size_t getLargestFreeBlock() const;
	// tells us how much total memory is available

	size_t getTotalFreeMemory() const;
	// tells us if a pointer is within this HeapManagers managed memory

	bool Contains(void * i_ptr) const;
	// tells us if this pointer is an outstanding allocation from this block

	bool IsAllocated(void* i_ptr) const;
	// a debugging helper function to show us all the free blocks.
		
	void ShowFreeBlocks() const;
	// a debugging helper function to show us all the outstanding blocks.

private:
	// defining some namespace global variables
	HeapManager *							PointerToHeap = nullptr;
	size_t									MaxHeapSize = 0;
	size_t									OutstandingMemory = 0;
	size_t									FreeMemory = 0;
	uint8_t *								TempMemoryPointer = nullptr;
	uint8_t *								FreeMemoryPtr = nullptr;

	// defining the HEADS of Allocated list, Free list and defining a temporary list node pointer
	BlockDescriptor *						AllocationList = nullptr;
	BlockDescriptor *						FreeList = nullptr;
	BlockDescriptor *						TempListTraverse = nullptr;
	

};
