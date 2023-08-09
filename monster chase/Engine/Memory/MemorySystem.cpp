#include "MemorySystem.h"
#include "new.h"
#include "assert.h"
#include "iostream"


bool MemorySystem::InitializeMemorySystem(void* i_pHeapMemory, size_t i_sizeHeapMemory, unsigned int i_OptionalNumDescriptors)
{
	// create your HeapManager
	FullHeap = new(i_pHeapMemory) HeapManager;
	FullHeap = FullHeap->create(i_pHeapMemory, i_sizeHeapMemory, i_OptionalNumDescriptors);
	assert(FullHeap);

#ifdef _DEBUG
	std::cout << "\n\nInitialized FullHeap";
#endif // _DEBUG

	FSA16 = reinterpret_cast<FixSizeAllocater *>(FullHeap->_alloc((16 * 100) + sizeof(FixSizeAllocater)));
	FSA32 = reinterpret_cast<FixSizeAllocater *>(FullHeap->_alloc((32 * 200) + sizeof(FixSizeAllocater)));
	FSA96 = reinterpret_cast<FixSizeAllocater *>(FullHeap->_alloc((96 * 400) + sizeof(FixSizeAllocater)));

#ifdef _DEBUG
	std::cout << "\n\nAllocated FSAs";
#endif // _DEBUG


	void* StartOfFSA16Blocks = reinterpret_cast<uint8_t*>(FSA16) + sizeof(FixSizeAllocater);
	void* StartOfFSA32Blocks = reinterpret_cast<uint8_t*>(FSA32) + sizeof(FixSizeAllocater);
	void* StartOfFSA96Blocks = reinterpret_cast<uint8_t*>(FSA96) + sizeof(FixSizeAllocater);

	FSA16 = new(FSA16) FixSizeAllocater;
	FSA32 = new(FSA32) FixSizeAllocater;
	FSA96 = new(FSA96) FixSizeAllocater;

	// creating the FSAs
	FSA16->create(16, 100, FullHeap, StartOfFSA16Blocks);
	FSA32->create(32, 200, FullHeap, StartOfFSA32Blocks);
	FSA96->create(96, 400, FullHeap, StartOfFSA96Blocks);

#ifdef _DEBUG
	std::cout << "\n\nFSAs initialized";
#endif // _DEBUG

	return true;
}

void MemorySystem::Collect()
{
	// coalesce free blocks
	// you may or may not need to do this depending on how you've implemented your HeapManager
	FullHeap->collect();
}

void MemorySystem::DestroyMemorySystem()
{
	// Destroy your HeapManager and FixedSizeAllocators
	//FSA16->destroyFSA();
	//FSA32->destroyFSA();
	//FSA96->destroyFSA();

	delete(FSA16);
	delete(FSA32);
	delete(FSA96);

	FullHeap->_free(FSA16);
	FullHeap->_free(FSA32);
	FullHeap->_free(FSA96);
	FullHeap->collect();
}



