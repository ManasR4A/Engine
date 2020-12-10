#pragma once

#include "stdint.h"

namespace Engine 
{
	// The structure to Wrap the Ref counters
	struct RefCounter
	{
		uint64_t SmartRefs;
		uint64_t WeakRefs;

		// DEFAULT CONSTRUCTOR
		//RefCounter() :
		//	SmartRefs(0)
		//{
		//}

		RefCounter(uint64_t i_InitialSmart, uint64_t i_InitialWeak) :
			SmartRefs(i_InitialSmart),
			WeakRefs(i_InitialWeak)
		{
		}

		//----------FOR SMART POINTER REFRENCES----------//

		inline uint64_t GetSmartRefs() const
		{
			return this->SmartRefs;
		}

		inline uint64_t IncreaseSmartRef()
		{
			SmartRefs++;
			return this->SmartRefs;
		}

		inline uint64_t DecreaseSmartRef()
		{
			SmartRefs--;
			return SmartRefs;
		}


		//----------FOR WEAK POINTER REFRENCES----------//

		inline uint64_t GetWeakRefs() const
		{
			return WeakRefs;
		}

		inline uint64_t IncreaseWeakRef()
		{
			WeakRefs++;
			return WeakRefs;
		}

		inline uint64_t DecreaseWeakRef()
		{
			WeakRefs--;
			return WeakRefs;
		}

	};
}
