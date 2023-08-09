#pragma once

#include "HeapManager.h"
#include "FixSizeAllocater.h"

class MemorySystem
{

public:
	// Defining the Full Heap and the FSAs based on the numbers given in the assignment
	HeapManager* FullHeap;

	// Argument list = size of block, numbre of blocks, ptr to the full heap
	FixSizeAllocater *FSA16, *FSA32, *FSA96;

	// InitializeMemorySystem - initialize your memory system including your HeapManager and some FixedSizeAllocators
	bool InitializeMemorySystem(void* i_pHeapMemory, size_t i_sizeHeapMemory, unsigned int i_OptionalNumDescriptors);

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
