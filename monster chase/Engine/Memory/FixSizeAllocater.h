#pragma once
#include "BitArray.h"
#include "HeapManager.h"

namespace Engine
{
	class FixSizeAllocater
	{
	public:
		// constructors
		FixSizeAllocater();
		// FixSizeAllocater(size_t i_BlockSize, size_t i_NumofBlocks, HeapManager* i_FullHeap);

		// Function to create the FSA
		void create(size_t i_BlockSize, size_t i_NumofBlocks, HeapManager* i_FullHeap, void* i_StartOfBlocks);

		// memory fumctions
		void* alloc();
		void free(void* i_BlockToFree);

		// To check if a given ptr is handled by the instance of this FSA or not.
		bool contains(void* i_BlockToFind);

		bool destroyFSA();

		~FixSizeAllocater();


		//private:
		BitArray TrackerArray;
		size_t BlockSize;
		size_t NumOfBlocks;
		size_t AllocatedBlocks;
		void* StartOfBlocks;
		uint8_t* TempBlockPtr;
		HeapManager* ParentHeap;
	};
}