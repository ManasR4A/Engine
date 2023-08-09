#include "HeapManager.h"
#include "new.h"
#include "iostream"

// Initializes the vars of the instance of the HeapManagerSample
HeapManager * HeapManager::create(void * i_pHeapMemory, size_t i_HeapMemorySize, unsigned int i_numDescriptors)
{
	// initializing the namespace variables to the ones given as parameters.
	PointerToHeap = reinterpret_cast<HeapManager *>(i_pHeapMemory);
	MaxHeapSize = i_HeapMemorySize;
	FreeMemory = MaxHeapSize;
	TempMemoryPointer = reinterpret_cast<uint8_t *>(PointerToHeap);
	FreeMemoryPtr = TempMemoryPointer + i_HeapMemorySize - 1; // Points to the last byte in the given memory
	std::cout << "\n" << FreeMemoryPtr;
	return reinterpret_cast<HeapManager *>(PointerToHeap);
}

// alloc() override without custom alignment.
void * HeapManager::_alloc(size_t i_RequiredMemory)
{
	size_t								alignment = 8;
	size_t								UserMemoryAlignment = 0;

	// fill the original free memory.
	if (FreeMemory > 100 && i_RequiredMemory < FreeMemory - 100)// (i_RequiredMemory + sizeof(BlockDescriptor) + alignment))
	{
		TempMemoryPointer = reinterpret_cast<uint8_t *>(PointerToHeap);
		// traversing to the end of heap
		TempMemoryPointer = TempMemoryPointer + FreeMemory;

		// going back the required amount of memory
		TempMemoryPointer -= i_RequiredMemory;

		// aligning user memory to 4 bytes
		while (reinterpret_cast<uint8_t *>(reinterpret_cast<uintptr_t>(TempMemoryPointer) % alignment != 0))
		{
			TempMemoryPointer--;
			UserMemoryAlignment++;
		}

		// going back block descriptor size 
		TempMemoryPointer = reinterpret_cast<uint8_t *>(TempMemoryPointer) - sizeof(BlockDescriptor);
		
		if (TempMemoryPointer <= reinterpret_cast<uint8_t *>(PointerToHeap))
		{
			std::cout << "\n\nTempMemoryPointer out of Heap ";// << reinterpret_cast<uint8_t *>(TempMemoryPointer) << " pointing out of heap " << reinterpret_cast<uint8_t *>(PointerToHeap) << "\n";
			std::cout << "\nFreeMemory " << FreeMemory;
			std::wcout << "\nOutstandingMemory " << OutstandingMemory;
			return nullptr;
		}
		else
		{
			// allocating the blocvk descriptor, Allocation list, returning the user memory
			BlockDescriptor * AllocationDescriptor = new (TempMemoryPointer) BlockDescriptor;
			AllocationDescriptor->UserMemorySize = i_RequiredMemory;
			AllocationDescriptor->UserMemoryPointer = static_cast<void *>(TempMemoryPointer + sizeof(BlockDescriptor));
			AllocationDescriptor->SizeOfAllocation = AllocationDescriptor->UserMemorySize + sizeof(BlockDescriptor) + UserMemoryAlignment;
		
			// check if its the first allocation or not and set the NextBlock accordingly
			if (AllocationList == nullptr)
				AllocationDescriptor->NextBlockDescriptor = nullptr;
			else
			{
				AllocationDescriptor->NextBlockDescriptor = AllocationList;
				AllocationList->PrevDescriptor = AllocationDescriptor;
			}
			
			// Set PrecDescriptor to nullptr to make it the head of the Allocation List
			AllocationDescriptor->PrevDescriptor = nullptr;
			AllocationList = AllocationDescriptor;

			// updating the FreeMemory and OutstandingMemory
			FreeMemory -= AllocationDescriptor->SizeOfAllocation;
			OutstandingMemory += AllocationDescriptor->SizeOfAllocation;

			// pointing the FreeMemPtr befor the last allocation as the allocations here are happening inline.
			FreeMemoryPtr = reinterpret_cast<uint8_t *>(AllocationDescriptor) - 1; 

			std::cout << "\nAllocated out of ORIGINAL memory " << static_cast<void *>(AllocationDescriptor);
			std::cout << ". New FreeMemory " << FreeMemory << "\nNew outstanding memory " << OutstandingMemory;
			std::cout << "\nNew FreeMemPtr " << FreeMemoryPtr << "\n";
			return (AllocationDescriptor->UserMemoryPointer);
		}
	}

	// Out of original FreeMemory.
	else 
	{
		std::cout << "\nAttempting allocating out of FREED blocks";
		// No free memory and no free blocks
		if (FreeList == nullptr)
		{
			std::cout << "\nAllocation Failed";
			return nullptr;
		}
			
		// there is a free list
		else 
		{
			TempListTraverse = FreeList;
			do // Searching in the free BlockDescriptor list
			{
				// if existing free block has user memory less than 2 times the block descriptor, give the block in its entirety
				if (TempListTraverse->UserMemorySize >= (i_RequiredMemory + sizeof(BlockDescriptor)) && TempListTraverse->UserMemorySize < (i_RequiredMemory + (2 * sizeof(BlockDescriptor))))
				{
					// Update the free list
					TempListTraverse->PrevDescriptor->NextBlockDescriptor = TempListTraverse->NextBlockDescriptor;
					TempListTraverse->NextBlockDescriptor->PrevDescriptor = TempListTraverse->PrevDescriptor;

					// Add the block to the top of allocation list
					TempListTraverse->PrevDescriptor = nullptr;
					TempListTraverse->NextBlockDescriptor = AllocationList;
					AllocationList->PrevDescriptor = TempListTraverse;
					AllocationList = TempListTraverse;

					// Returning user memory ptr
					std::cout << "\nAllocated from previous block " << static_cast<void *>(TempListTraverse);
					return(TempListTraverse->UserMemoryPointer);
				}

				// If the free blocks user memory is > 2 times of the BlockDescriptor Size
				else if (TempListTraverse->UserMemorySize >= (i_RequiredMemory + (2 * sizeof(BlockDescriptor)))) 
				{
					// break block into two and update the free list
					uint8_t *				BrokenMemory;
					BrokenMemory = reinterpret_cast<uint8_t *>(TempListTraverse) + sizeof(BlockDescriptor) + TempListTraverse->SizeOfAllocation;
					BrokenMemory -= i_RequiredMemory;

					// Aligning user memory of the new block
					while (reinterpret_cast<uint8_t *>(reinterpret_cast<uintptr_t>(BrokenMemory) % alignment != 0))
					{
						BrokenMemory--;
						UserMemoryAlignment++;
					}

					// Going back sizeof BlockDescriptor
					BrokenMemory -= sizeof(BlockDescriptor);

					// creating the new block descriptor and assigning the required memory to this
					BlockDescriptor * AllocationDescriptor = new(BrokenMemory) BlockDescriptor; // NEW BLOCK
					AllocationDescriptor->UserMemorySize = i_RequiredMemory;
					AllocationDescriptor->SizeOfAllocation = AllocationDescriptor->UserMemorySize + sizeof(BlockDescriptor) + UserMemoryAlignment;
					AllocationDescriptor->UserMemoryPointer = reinterpret_cast<void *>(reinterpret_cast<int8_t *>(AllocationDescriptor) + sizeof(BlockDescriptor));

					// connect the new block to the top of the allocation list
					AllocationDescriptor->PrevDescriptor = nullptr;
					AllocationDescriptor->NextBlockDescriptor = AllocationList;
					if (AllocationList != nullptr) // If there is no allocation list
						AllocationList->PrevDescriptor = AllocationDescriptor;

					AllocationList = AllocationDescriptor;

					// redefining the original descriptor
					TempListTraverse->UserMemorySize -= AllocationDescriptor->SizeOfAllocation;
					TempListTraverse->SizeOfAllocation -= AllocationDescriptor->SizeOfAllocation;

					std::cout << "\nSplitted and allocated from previous block " << static_cast<void *>(TempListTraverse);
					return (AllocationDescriptor->UserMemoryPointer);
				}

				// If the Block doesn't have enough memory go to next block in FreeList
				TempListTraverse = TempListTraverse->NextBlockDescriptor;
			} while (TempListTraverse != nullptr);// Run through the free list

			// No block in FreeList is big enough for allocation and Free Memory is over
			if (TempListTraverse == nullptr)
				return nullptr;
		}
	}
}

// Alloc override to take in custom alignment.
void * HeapManager::_alloc(size_t i_RequiredMemory, unsigned int i_alignment)
{
	size_t								alignment = i_alignment;
	size_t								UserMemoryAlignment = 0;

	// fill the original free memory.
	if (FreeMemory > 100)// (i_RequiredMemory + sizeof(BlockDescriptor) + alignment))
	{
		TempMemoryPointer = reinterpret_cast<uint8_t *>(PointerToHeap);
		// traversing to the end of heap
		TempMemoryPointer = TempMemoryPointer + FreeMemory;

		// going back the required amount of memory
		TempMemoryPointer -= i_RequiredMemory;

		// aligning user memory to 4 bytes
		while (reinterpret_cast<uint8_t *>(reinterpret_cast<uintptr_t>(TempMemoryPointer) % alignment != 0))
		{
			TempMemoryPointer--;
			UserMemoryAlignment++;
		}

		// going back block descriptor size 
		TempMemoryPointer = reinterpret_cast<uint8_t *>(TempMemoryPointer) - sizeof(BlockDescriptor);

		if (TempMemoryPointer <= reinterpret_cast<uint8_t *>(PointerToHeap))
		{
			std::cout << "\n\nTempMemoryPointer out of Heap ";// << reinterpret_cast<uint8_t *>(TempMemoryPointer) << " pointing out of heap " << reinterpret_cast<uint8_t *>(PointerToHeap) << "\n";
			std::cout << "\nFreeMemory " << FreeMemory;
			std::wcout << "\nOutstandingMemory " << OutstandingMemory;
			return nullptr;
		}
		else
		{
			// allocating the blocvk descriptor, Allocation list, returning the user memory
			BlockDescriptor * AllocationDescriptor = new (TempMemoryPointer) BlockDescriptor;
			AllocationDescriptor->UserMemorySize = i_RequiredMemory;
			AllocationDescriptor->UserMemoryPointer = static_cast<void *>(TempMemoryPointer + sizeof(BlockDescriptor));
			AllocationDescriptor->SizeOfAllocation = AllocationDescriptor->UserMemorySize + sizeof(BlockDescriptor) + UserMemoryAlignment;

			// check if its the first allocation or not and set the NextBlock accordingly
			if (AllocationList == nullptr)
				AllocationDescriptor->NextBlockDescriptor = nullptr;
			else
			{
				AllocationDescriptor->NextBlockDescriptor = AllocationList;
				AllocationList->PrevDescriptor = AllocationDescriptor;
			}

			// Set PrecDescriptor to nullptr to make it the head of the Allocation List
			AllocationDescriptor->PrevDescriptor = nullptr;
			AllocationList = AllocationDescriptor;

			// updating the FreeMemory and OutstandingMemory
			FreeMemory -= AllocationDescriptor->SizeOfAllocation;
			OutstandingMemory += AllocationDescriptor->SizeOfAllocation;

			// pointing the FreeMemPtr befor the last allocation as the allocations here are happening inline.
			FreeMemoryPtr = reinterpret_cast<uint8_t *>(AllocationDescriptor) - 1;

			std::cout << "\nAllocated out of ORIGINAL memory " << static_cast<void *>(AllocationDescriptor);
			std::cout << ". New FreeMemory " << FreeMemory << "\nNew outstanding memory " << OutstandingMemory;
			std::cout << "\nNew FreeMemPtr " << FreeMemoryPtr << "\n";
			return (AllocationDescriptor->UserMemoryPointer);
		}
	}

	// Out of original FreeMemory.
	else
	{
		std::cout << "\nAttempting allocating out of FREED blocks";
		// No free memory and no free blocks
		if (FreeList == nullptr)
		{
			std::cout << "\nAllocation Failed";
			return nullptr;
		}

		// there is a free list
		else
		{
			TempListTraverse = FreeList;
			do // Searching in the free BlockDescriptor list
			{
				// if existing free block has user memory less than 2 times the block descriptor, give the block in its entirety
				if (TempListTraverse->UserMemorySize >= (i_RequiredMemory + sizeof(BlockDescriptor)) && TempListTraverse->UserMemorySize < (i_RequiredMemory + (2 * sizeof(BlockDescriptor))))
				{
					// Update the free list
					TempListTraverse->PrevDescriptor->NextBlockDescriptor = TempListTraverse->NextBlockDescriptor;
					TempListTraverse->NextBlockDescriptor->PrevDescriptor = TempListTraverse->PrevDescriptor;

					// Add the block to the top of allocation list
					TempListTraverse->PrevDescriptor = nullptr;
					TempListTraverse->NextBlockDescriptor = AllocationList;
					AllocationList->PrevDescriptor = TempListTraverse;
					AllocationList = TempListTraverse;

					// Returning user memory ptr
					std::cout << "\nAllocated from previous block " << static_cast<void *>(TempListTraverse);
					return(TempListTraverse->UserMemoryPointer);
				}

				// If the free blocks user memory is > 2 times of the BlockDescriptor Size
				else if (TempListTraverse->UserMemorySize >= (i_RequiredMemory + (2 * sizeof(BlockDescriptor))))
				{
					// break block into two and update the free list
					uint8_t *				BrokenMemory;
					BrokenMemory = reinterpret_cast<uint8_t *>(TempListTraverse) + sizeof(BlockDescriptor) + TempListTraverse->SizeOfAllocation;
					BrokenMemory -= i_RequiredMemory;

					// Aligning user memory of the new block
					while (reinterpret_cast<uint8_t *>(reinterpret_cast<uintptr_t>(BrokenMemory) % alignment != 0))
					{
						BrokenMemory--;
						UserMemoryAlignment++;
					}

					// Going back sizeof BlockDescriptor
					BrokenMemory -= sizeof(BlockDescriptor);

					// creating the new block descriptor and assigning the required memory to this
					BlockDescriptor * AllocationDescriptor = new(BrokenMemory) BlockDescriptor; // NEW BLOCK
					AllocationDescriptor->UserMemorySize = i_RequiredMemory;
					AllocationDescriptor->SizeOfAllocation = AllocationDescriptor->UserMemorySize + sizeof(BlockDescriptor) + UserMemoryAlignment;
					AllocationDescriptor->UserMemoryPointer = reinterpret_cast<void *>(reinterpret_cast<int8_t *>(AllocationDescriptor) + sizeof(BlockDescriptor));

					// connect the new block to the top of the allocation list
					AllocationDescriptor->PrevDescriptor = nullptr;
					AllocationDescriptor->NextBlockDescriptor = AllocationList;
					if (AllocationList != nullptr) // If there is no allocation list
						AllocationList->PrevDescriptor = AllocationDescriptor;

					AllocationList = AllocationDescriptor;

					// redefining the original descriptor
					TempListTraverse->UserMemorySize -= AllocationDescriptor->SizeOfAllocation;
					TempListTraverse->SizeOfAllocation -= AllocationDescriptor->SizeOfAllocation;

					std::cout << "\nSplitted and allocated from previous block " << static_cast<void *>(TempListTraverse);
					return (AllocationDescriptor->UserMemoryPointer);
				}

				// If the Block doesn't have enough memory go to next block in FreeList
				TempListTraverse = TempListTraverse->NextBlockDescriptor;
			} while (TempListTraverse != nullptr);// Run through the free list

			// No block in FreeList is big enough for allocation and Free Memory is over
			if (TempListTraverse == nullptr)
				return nullptr;
		}
	}
}

// Coalesce() to coalesce two free adjescent blocks called in free only if the adjescent blocks are free.
BlockDescriptor * HeapManager::coalesce(BlockDescriptor * i_LeftBlock, BlockDescriptor * i_RightBlock)
{
	// Adding the entire memory from the right block to the user memory of the left block
	i_LeftBlock->SizeOfAllocation += i_RightBlock->SizeOfAllocation;
	i_LeftBlock->UserMemorySize += i_RightBlock->SizeOfAllocation;

	// the nextDescriptor of left is the next of the right
	i_LeftBlock->NextBlockDescriptor = i_RightBlock->NextBlockDescriptor;

	// check if the right is the last element
	if (i_RightBlock->NextBlockDescriptor != nullptr)
		i_RightBlock->NextBlockDescriptor->PrevDescriptor = i_LeftBlock;

	std::cout << "\nCoalasced " << i_LeftBlock << "\n";
	return i_LeftBlock;
}

// free() override.
bool HeapManager::_free(void * i_ptr)
{
	if (AllocationList == nullptr) // No outstanding allocation found
		return false;

	BlockDescriptor *					BlockToFree = nullptr;

	// CHECKING IF THE GIVEN POINTER EXISTS IN THE ALLOCATION LIST
	TempListTraverse = AllocationList;
	while (TempListTraverse != nullptr)
	{
		if (TempListTraverse->UserMemoryPointer == i_ptr) // pointer found in the allocated list
		{
			// POINT TO THE BLOCKTOFREE & REARRANGE THE ALLOCATIONLIST
			BlockToFree = TempListTraverse; 
			std::cout << "\nFound " << static_cast<void *>(BlockToFree);
			// If the BlockToFree is first in Allocation List
			if (BlockToFree == AllocationList)
			{
				AllocationList = BlockToFree->NextBlockDescriptor;
				if (AllocationList != nullptr) // If allocation List was more than one blocks
					AllocationList->PrevDescriptor = nullptr;
				std::cout << "\nFreed at the head of Allioction " << static_cast<void *>(BlockToFree);
				break;
			}

			// If the BlockToFree is at the end of the Allocation List
			else if (BlockToFree->NextBlockDescriptor == nullptr && BlockToFree != AllocationList)
			{
				BlockToFree->PrevDescriptor->NextBlockDescriptor = nullptr;
				std::cout << "\nFreed at the tail of Allocation " << static_cast<void *>(BlockToFree);
				break;
			}

			// If the BlockToFree is in the mid of Allocation List
			else
			{
				BlockToFree->PrevDescriptor->NextBlockDescriptor = BlockToFree->NextBlockDescriptor;
				BlockToFree->NextBlockDescriptor->PrevDescriptor = BlockToFree->PrevDescriptor;
				std::cout << "\nFreed from the mid of Allocation " << static_cast<void *>(BlockToFree);
				break;
			}
		}
		TempListTraverse = TempListTraverse->NextBlockDescriptor; // goto next block in AllocationList
	}

	if (TempListTraverse == nullptr) // Pointer not found in our allocated list
	{
		std::wcout << "\nPointer not allocated\n";
		return false;
	}

	// MOVING THE BLOCKTOFREE IN THE APPROPRIATE PLACE IN THE FREE LIST : INCREASING ORDER OF USER MEM ADDRESS
	if (TempListTraverse != nullptr) // Only if pointer found
	{
		// If the FreeList is empty
		if (FreeList == nullptr)
		{
			if (BlockToFree == nullptr)
				std::cout << "\nEngine/Memory System: Unintialized BlockToFree in _free()";
			FreeList = BlockToFree;
			BlockToFree->PrevDescriptor = nullptr;
			BlockToFree->NextBlockDescriptor = nullptr;
			std::cout << "\nInitialized FreeList with " << BlockToFree << "\n";
		}

		// If FreeList isn't empty
		else
		{
			TempListTraverse = FreeList;
			while (TempListTraverse != nullptr) // traversing FreeList to find the position
			{
				if (BlockToFree->UserMemoryPointer < TempListTraverse->UserMemoryPointer) // only execute if the blocktofree gets the appropriate position
				{
					// redo connections such that the BlockToFree is in Free list
					BlockToFree->NextBlockDescriptor = TempListTraverse;

					if (TempListTraverse->PrevDescriptor == nullptr) // If the BlockToFree goes on the font of the FreeList
					{
						BlockToFree->PrevDescriptor = nullptr;
						FreeList = BlockToFree;
						TempListTraverse->PrevDescriptor = BlockToFree;
						std::wcout << "\nadded block " << BlockToFree << " at the front of FreeList\n";
						std::wcout << "\nadded block " << BlockToFree << " at the front of FreeList\n";
						break;
					}

					else // If the BlockToFree goes anywhere else in the FreeList
					{
						BlockToFree->PrevDescriptor = TempListTraverse->PrevDescriptor;
						BlockToFree->PrevDescriptor->NextBlockDescriptor = BlockToFree;
						TempListTraverse->PrevDescriptor = BlockToFree;
						std::wcout << "\nadded block " << BlockToFree << " in the mid of FreeList\n";
						break;
					}
				}
				TempListTraverse = TempListTraverse->NextBlockDescriptor; // update statement if this is not the position
			}
			// To handel if the Block to free goes at the end of FreeList
			if (TempListTraverse == nullptr)
			{
				TempListTraverse = FreeList;
				while (TempListTraverse->NextBlockDescriptor != nullptr) // get to the last element of the FreeList
					TempListTraverse = TempListTraverse->NextBlockDescriptor;

				// add the BlockToFree at the end of the FreeList
				BlockToFree->PrevDescriptor = TempListTraverse;
				TempListTraverse->NextBlockDescriptor = BlockToFree;
				BlockToFree->NextBlockDescriptor = nullptr;
				std::wcout << "\nadded block " << BlockToFree << " at the end of FreeList\n";
			}
		}
	}
			

	// CHECKING CONDITION FOR COALESCE RIGHT & LEFT OF CURRENT NODE IN FREE LIST AND CALLING COALESCE() ACCORDINGLY
	if (BlockToFree->NextBlockDescriptor != nullptr && (reinterpret_cast<int8_t *>(BlockToFree) + BlockToFree->SizeOfAllocation) == reinterpret_cast<int8_t *>(BlockToFree->NextBlockDescriptor))
		BlockToFree = coalesce(BlockToFree, BlockToFree->NextBlockDescriptor);
	if (BlockToFree->PrevDescriptor != nullptr && reinterpret_cast<int8_t *>(BlockToFree->PrevDescriptor) + BlockToFree->PrevDescriptor->SizeOfAllocation == reinterpret_cast<int8_t *>(BlockToFree))
		BlockToFree = coalesce(BlockToFree->PrevDescriptor, BlockToFree);

	return true;
}

// collects all the free blocks that can be coalasced.
void HeapManager::collect()
{
	std::cout << "\n\n\n FreeList";
	TempListTraverse = FreeList;
	while (TempListTraverse != nullptr)
	{
		std::cout << "\n" << TempListTraverse;
		TempListTraverse = TempListTraverse->NextBlockDescriptor;
	}

	// to check for the last collect and the remaining original free memory
	if (reinterpret_cast<uint8_t *>(PointerToHeap) + FreeMemory == reinterpret_cast<uint8_t *>(FreeList) && FreeMemory + FreeList->SizeOfAllocation == MaxHeapSize)
	{
		BlockDescriptor *	FinalBlock = new (PointerToHeap) BlockDescriptor;
		FinalBlock->SizeOfAllocation = FreeMemory + FreeList->SizeOfAllocation;
		FinalBlock->UserMemorySize = FinalBlock->SizeOfAllocation - sizeof(BlockDescriptor); 
		FinalBlock->NextBlockDescriptor = nullptr;
		FinalBlock->PrevDescriptor = nullptr;
		FreeList = FinalBlock;
		std::cout << "\n\nCollected Final memory";
	}
}

// returns block with the largest UserMemorySize.
size_t HeapManager::getLargestFreeBlock() const
{
	// Temp Variables
	BlockDescriptor *				MaxFreeBlock;
	MaxFreeBlock = nullptr;

	BlockDescriptor *				LocalTempListTraverse;
	LocalTempListTraverse = FreeList;

	// If the Free list is nullptr, then the MaxFree size is nullptr
	(LocalTempListTraverse == nullptr ? MaxFreeBlock = nullptr : MaxFreeBlock = LocalTempListTraverse);

	// Traverse through Free list
	while (LocalTempListTraverse != nullptr)
	{
		if (LocalTempListTraverse->UserMemorySize > MaxFreeBlock->UserMemorySize)
			MaxFreeBlock = LocalTempListTraverse;

		LocalTempListTraverse = LocalTempListTraverse->NextBlockDescriptor;
	}

	// return accordingly
	if (MaxFreeBlock == nullptr)
		return 0;
	else
		return MaxFreeBlock->UserMemorySize;
}

// returns total free memory including all the UserMemorySize in the FreeList blocks.
size_t HeapManager::getTotalFreeMemory() const
{
	BlockDescriptor *				LocalTempListTraverse = nullptr;
	size_t							TotalFreeMem = 0;

	TotalFreeMem += FreeMemory;

	if (FreeList != nullptr) // go through if there are some free-d blocks
	{
		LocalTempListTraverse = FreeList;
		while (LocalTempListTraverse != nullptr) // traverse through free blocks' list and add the allocated mem to TotalFreeMem
		{
			TotalFreeMem += LocalTempListTraverse->UserMemorySize; // Only show the user memory size
			LocalTempListTraverse = LocalTempListTraverse->NextBlockDescriptor;
		}
	}

	return TotalFreeMem;
}

// returns a bool whether the inputed ptr is managed by the HeapManagerSample instance or not.
bool HeapManager::Contains(void * i_ptr) const
{
	if (AllocationList != nullptr) // Only go in if there are outstanding allocations
	{
		BlockDescriptor *				LocalTempListTraverse;
		LocalTempListTraverse = AllocationList;

		while (LocalTempListTraverse != nullptr) // go through the allocation list
		{
			if (LocalTempListTraverse->UserMemoryPointer == i_ptr) // Pointer found in the allocation list
				return true;
			else
				LocalTempListTraverse = LocalTempListTraverse->NextBlockDescriptor;
		}

		return false; // The pointer not found in the allocation list
	}

	else // No outstanding allocations
		return false;
}

// returns a bool whether the inputted ptr is an allocated UserMemoryPointer or not.
bool HeapManager::IsAllocated(void * i_ptr) const
{
	if (AllocationList != nullptr) // Only execute if there are outstanding allocations
	{
		BlockDescriptor *				LocalTempListTraverse;
		LocalTempListTraverse = AllocationList;
		while (LocalTempListTraverse != nullptr) // go through the allocation list
		{
			if (LocalTempListTraverse->UserMemoryPointer == i_ptr) // Pointer found in the allocation list
				return true;
			else
				LocalTempListTraverse = LocalTempListTraverse->NextBlockDescriptor;
		}

		return false; // Not found in allocations
	}
	else // No outstanding allocations
		return false;
}

// prints the info of all the blocks in the free list.
void HeapManager::ShowFreeBlocks() const
{
	if (FreeList != nullptr) // go through only if there are free-d blocks
	{
		BlockDescriptor *				LocalTempListTraverse = FreeList;

		while (LocalTempListTraverse != nullptr) // go through the free list
		{
			std::cout << "\n/npointer = " << LocalTempListTraverse->UserMemoryPointer << " size = " << LocalTempListTraverse->UserMemorySize;
			LocalTempListTraverse = LocalTempListTraverse->NextBlockDescriptor;
		}
	}

	else // No free-d blocks found
	{
		std::cout << "\n No Free-d blocks found";
	}

	if (FreeMemory != 0) // If original free memory of the heap exists
		std::cout << "\nOriginal heap pointer = " << PointerToHeap << "\n Original free memory size = " << FreeMemory;
}

