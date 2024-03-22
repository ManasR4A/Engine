#pragma once
#include <inttypes.h>
#include "MemorySystem.h"
#include "HeapManager.h"
#include <stdio.h>
#include "assert.h"

namespace Engine
{
	void* HeapSystem::_malloc(size_t i_size)
	{
		// replace with calls to your HeapManager or FixedSizeAllocators

		// check for the size and based on that go to the different allocaters
		if (i_size > 0 && i_size <= 16)
		{
			return FSA16->alloc();
			std::cout << "\n\n Allocated out of FSA16.";
		}

		else if (i_size > 16 && i_size <= 32)
		{
			return FSA32->alloc();
			std::cout << "\n\n Allocated out of FSA32.";
		}

		else if (i_size > 32 && i_size <= 96)
		{
			return FSA96->alloc();
			std::cout << "\n\n Allocated out of FSA96.";
		}
		else
			return FullHeap->_alloc(i_size);
	}

	void HeapSystem::_free(void* i_ptr)
	{
		// replace with calls to your HeapManager or FixedSizeAllocators

		// checking which FSA is handling the ptr or if the HeapManager is handling the ptr
		if (FSA16->contains(i_ptr))
		{
			FSA16->free(i_ptr);
		}

		else if (FSA32->contains(i_ptr))
		{
			FSA32->free(i_ptr);
		}

		else if (FSA96->contains(i_ptr))
		{
			FSA96->free(i_ptr);
		}

		else if (FullHeap->Contains(i_ptr))
		{
			if (FullHeap->IsAllocated(i_ptr))
				FullHeap->_free(i_ptr);
		}

		else
		{
			// print that the ptr is not found
			assert(false);
		}

		printf("\n MemorySystem free 0x%" PRIXPTR "\n", reinterpret_cast<uintptr_t>(i_ptr));
	}


	//void* MemorySystem::operator new(size_t i_size, MemorySystem * i_MS)
	//{
	//	// replace with calls to your HeapManager or FixedSizeAllocators
	//	if (i_size > 0 && i_size <= 16)
	//		return i_MS->FSA16->alloc();
	//
	//	else if (i_size > 16 && i_size <= 32)
	//		return i_MS->FSA32->alloc();
	//
	//	else if (i_size > 32 && i_size <= 96)
	//		return i_MS->FSA96->alloc();
	//
	//	else
	//		return i_MS->FullHeap->_alloc(i_size);
	//	printf("new %zu\n", i_size);
	//}
	//
	//void MemorySystem::operator delete(void* i_ptr, MemorySystem* MS)
	//{
	//	// replace with calls to your HeapManager or FixedSizeAllocators
	//	assert(i_ptr);
	//
	//	// checking which FSA is handling the ptr or if the HeapManager is handling the ptr
	//	if (MS->FSA16->contains(i_ptr))
	//	{
	//		MS->FSA16->free(i_ptr);
	//	}
	//
	//	else if (MS->FSA32->contains(i_ptr))
	//	{
	//		MS->FSA32->free(i_ptr);
	//	}
	//
	//	else if (MS->FSA96->contains(i_ptr))
	//	{
	//		MS->FSA96->free(i_ptr);
	//	}
	//
	//	else if (MS->FullHeap->Contains(i_ptr))
	//	{
	//		if (MS->FullHeap->IsAllocated(i_ptr))
	//			MS->FullHeap->_free(i_ptr);
	//	}
	//
	//	else
	//	{
	//		// print that the ptr is not found
	//	}
	//
	//	printf("delete 0x%" PRIXPTR "\n", reinterpret_cast<uintptr_t>(i_ptr));
	//}
	//
	//void* MemorySystem::operator new[](size_t i_size, MemorySystem* MS)
	//{
	//	if (i_size > 0 && i_size <= 16)
	//		return MS->FSA16->alloc();
	//
	//	else if (i_size > 16 && i_size <= 32)
	//		return MS->FSA32->alloc();
	//
	//	else if (i_size > 32 && i_size <= 96)
	//		return MS->FSA96->alloc();
	//
	//	else
	//		return MS->FullHeap->_alloc(i_size);
	//}
	//
	//void MemorySystem::operator delete[](void* i_ptr, MemorySystem * MS)
	//{
	//	assert(i_ptr);
	//
	//	// checking which FSA is handling the ptr or if the HeapManager is handling the ptr
	//	if (MS->FSA16->contains(i_ptr))
	//	{
	//		MS->FSA16->free(i_ptr);
	//	}
	//
	//	else if (MS->FSA32->contains(i_ptr))
	//	{
	//		MS->FSA32->free(i_ptr);
	//	}
	//
	//	else if (MS->FSA96->contains(i_ptr))
	//	{
	//		MS->FSA96->free(i_ptr);
	//	}
	//
	//	else if (MS->FullHeap->Contains(i_ptr))
	//	{
	//		if (MS->FullHeap->IsAllocated(i_ptr))
	//			MS->FullHeap->_free(i_ptr);
	//	}
	//
	//	else
	//	{
	//		// print that the ptr is not found
	//	}
	//}
}



