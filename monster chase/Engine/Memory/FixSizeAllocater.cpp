#include"FixSizeAllocater.h"
#include "iostream"

namespace Engine
{
	// Constructors
	FixSizeAllocater::FixSizeAllocater()
	{
		BlockSize = 0;
		NumOfBlocks = 0;
		StartOfBlocks = nullptr;
		TempBlockPtr = nullptr;
		ParentHeap = nullptr;
		AllocatedBlocks = 0;
	}

	//FixSizeAllocater::FixSizeAllocater(size_t i_BlockSize, size_t i_NumofBlocks, HeapManager * i_FullHeap)
	//{
	//	BlockSize = i_BlockSize;
	//	NumOfBlocks = i_NumofBlocks;
	//	TrackerArray.CreateBitArray(NumOfBlocks * BlockSize);
	//	StartOfBlocks = reinterpret_cast<FixSizeAllocater *>( i_FullHeap->_alloc( (BlockSize * NumOfBlocks) ) );
	//	TempBlockPtr = reinterpret_cast<uint8_t*>(StartOfBlocks);
	//	ParentHeap = i_FullHeap;
	//}

	// custom function to initialize member variables after the instance is constructed
	void FixSizeAllocater::create(size_t i_BlockSize, size_t i_NumofBlocks, HeapManager* i_FullHeap, void* i_StartOfBlocks)
	{
		BlockSize = i_BlockSize;
		NumOfBlocks = i_NumofBlocks;
		TrackerArray.CreateBitArray(NumOfBlocks * BlockSize);
		StartOfBlocks = i_StartOfBlocks;
		TempBlockPtr = reinterpret_cast<uint8_t*>(StartOfBlocks);
		ParentHeap = i_FullHeap;
#ifdef _DEBUG
		std::cout << "\n\nInitialized FSA" << BlockSize;
#endif // _DEBUG
		AllocatedBlocks = 0;


	}

	// FSA specific allocater
	void* FixSizeAllocater::alloc()
	{

		// finding the first freee block
		size_t FreeBit = TrackerArray.GetFirstSetBit();

		if (FreeBit == 0) // No Free BlockFound
			return nullptr;

		// Setting that bit to 0 to represent that the block is now allocated
		TrackerArray.ClearBit(FreeBit);

		// getting the ptr represented by that bit
		TempBlockPtr = reinterpret_cast<uint8_t*>(StartOfBlocks);
		size_t LocalLoop = 1;
		while (LocalLoop != FreeBit)
		{
			TempBlockPtr += BlockSize;
			LocalLoop++;
		}

#ifdef _DEBUG
		std::cout << "\n\n Allocated Out of FSA" << BlockSize;
#endif // _DEBUG

		AllocatedBlocks++; // To debug how many allocations does the FSA have.

		// returning the ptr
		return reinterpret_cast<void*>(TempBlockPtr); // forcing to pass a void ptr


	}

	/* Since this free() is only called by me in the Allocators.h,
	I will only call this after I check if the void ptr is handled by this FSA.
	 Thus no assert on that is needed */
	void FixSizeAllocater::free(void* i_BlockToFree)
	{
		// check if the block to free is allocated
		size_t BitNum = (reinterpret_cast<uintptr_t>(i_BlockToFree) - reinterpret_cast<uintptr_t>(StartOfBlocks)) / BlockSize;

		// only Set the corosponding bit if it isn't already set
		if (!TrackerArray.IsBitSet(BitNum))
		{
			// Find at what number that block is
			size_t LocalLoop = 1;
			size_t BitToSet = 1; // We set the bit to indicate that the block is free
			TempBlockPtr = reinterpret_cast<uint8_t*>(StartOfBlocks);

			// going through the blocks to see where the ptr is
			while (LocalLoop <= NumOfBlocks)
			{
				if (TempBlockPtr == i_BlockToFree)
				{
#ifdef _DEBUG
					std::cout << "\n\n" << i_BlockToFree << " freed from FSA" << BlockSize;
#endif // _DEBUG

					TrackerArray.SetBit(BitToSet); // call the SetBit() on the bit corosponding to the block
					AllocatedBlocks--;
					break;
				}
				else
				{
					BitToSet++;
					TempBlockPtr += BlockSize; // Go to next block in the FSA.
				}

				LocalLoop++;
			}
		}
	}

	// return true if the given ptr is handled by that instance of the FSA
	bool FixSizeAllocater::contains(void* i_BlockToFind)
	{
		TempBlockPtr = reinterpret_cast<uint8_t*>(StartOfBlocks);
		size_t LocalLoop = 1;
		while (LocalLoop <= NumOfBlocks)
		{
			if (i_BlockToFind == TempBlockPtr)
			{
#ifdef _DEBUG
				std::cout << "\n\n" << i_BlockToFind << " found in FSA" << BlockSize;
#endif // _DEBUG
				return true;
			}
			else
			{
				TempBlockPtr += BlockSize;
				LocalLoop++;
			}
		}
		return false;

	}

	bool FixSizeAllocater::destroyFSA()
	{
#ifdef _DEBUG
		if (!TrackerArray.IsSetAll())
			std::cout << "\n\nNot All Allocations Freed in FSA" << BlockSize;
#endif // DEBUG

		//desrtoy the tracker array
		TrackerArray.~BitArray();

		StartOfBlocks = nullptr;
		TempBlockPtr = nullptr;
		ParentHeap = nullptr;
		return true;
	}

	FixSizeAllocater::~FixSizeAllocater()
	{
#ifdef _DEBUG
		if (!TrackerArray.IsSetAll())
			std::cout << "\n\nNot All Allocations Freed in FSA" << BlockSize;
#endif // DEBUG

		//desrtoy the tracker array
		TrackerArray.~BitArray();

		StartOfBlocks = nullptr;
		TempBlockPtr = nullptr;
		ParentHeap = nullptr;
	}
}
