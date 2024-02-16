#pragma once

#include "RefCounter.h"

namespace Engine
{

	template<class T>
	class WeakPointer
	{
	public:
		template<class U>
		friend class WeakPointer;

		template<class U>
		friend class SmartPointer;
		
	private:
		T* m_ptr;
		RefCounter* Refs;

		void release()
		{
			if (Refs)
			{
				// decrease referrence count
				assert(Refs->GetWeakRefs() > 0);
				Refs->DecreaseWeakRef();

				// if Smart ref count is zero deal with the pointers.
				if (Refs->GetWeakRefs() == 0)
				{
					if (Refs->GetSmartRefs() == 0)
					{
						delete Refs;
						Refs = nullptr;
						m_ptr = nullptr;
					}
				}
			}
			else
				assert(m_ptr == nullptr);
		}

	public:

		// default Constructors
		WeakPointer() :
			m_ptr(nullptr),
			Refs(nullptr)
		{}


		// Copy Constructor from a WeakPointer of same type
		WeakPointer(const WeakPointer& OtherPtr) :
			Refs(OtherPtr.Refs),
			m_ptr(OtherPtr.m_ptr)
		{
			if (Refs)
			{
				// Check if any Smart ptr or WeakPtr References still point
				assert(Refs->GetWeakRefs() || Refs->GetSmartRefs());
				Refs->IncreaseWeakRef();
			}
		}

		// copy from a WeakPointer of different type
		template<class U>
		WeakPointer(const WeakPointer<U>& OtherPtr) :
			Refs(OtherPtr.Refs),
			m_ptr(OtherPtr.m_ptr)
		{
			if (Refs)
			{
				// Check if any Smart ptr or WeakPtr References still point
				assert(Refs->GetWeaktRefs() || Refs->GetSmartRefs());
				Refs->IncreaseWeakRef();
			}
		}

		// Make a Weak Pointer From A Smart Pointer
		template<class U>
		WeakPointer(SmartPointer<U>& i_Smart) :
			Refs(i_Smart.Refs),
			m_ptr(i_Smart.m_ptr)
		{
			if (Refs)
			{
				// Check if any Smart ptr or WeakPtr References still point
				assert(Refs->GetWeakRefs() || Refs->GetSmartRefs());
				Refs->IncreaseWeakRef();
			}
		}


		//----------OPERATOR OVERLOADS----------//

		// Assidgnment Operator
		inline WeakPointer& operator = (const WeakPointer& OtherPointer)
		{
			if (m_ptr != OtherPointer.m_ptr)
			{
				// release the previous holding pointer
				release();

				// update the wrapped pointer and Refs
				Refs = OtherPointer.Refs;
				m_ptr = OtherPointer.m_ptr;

				assert(Refs->GetWeakRefs() > 0 || Refs->GetSmartRefs() > 0); // To check if there is atlease one other pointer to the things.
				Refs->IncreaseWeakRef();
			}

			return *this;
		}

		// Assignment Operator to make WeakPointer from another WeakPointer
		template<class U>
		inline WeakPointer& operator = (const WeakPointer<U>& OtherPointer)
		{
			if (m_ptr != OtherPointer.pPtr)
			{
				release();

				Refs = OtherPointer.pCounters;
				m_ptr = OtherPointer.pPtr;

				assert(Refs->GetWeakRefs() > 0 || Refs->GetSmartRefs() > 0); // To check if there is atlease one other pointer to the things.
				Refs->IncreaseWeakRef();
			}

			return *this;
		}

		// Assignment Operator to make WeakPointer from a SmartPointer
		template<class U>
		inline WeakPointer& operator = (const SmartPointer<U>& OtherPointer)
		{
			if (m_ptr != OtherPointer.m_ptr)
			{
				release();

				Refs = OtherPointer.Refs;
				m_ptr = OtherPointer.m_ptr;

				assert(Refs->GetWeakRefs() > 0 || Refs->GetSmartRefs() > 0); // To check if there is atlease one other pointer to the things.
				Refs->IncreaseWeakRef();
			}

			return *this;
		}

		// nullptr specific Assignment operator
		WeakPointer& operator = (std::nullptr_t i_nullptr)
		{
			release();
			Refs = nullptr;
			m_ptr = nullptr;
			return *this;
		}



		//-------- OPERATOR OVERLOADS ----------//

		// compare with other Weak ptr
		template<class U>
		inline bool operator == (WeakPointer<U>& OtherPtr)
		{
			return m_ptr == OtherPtr.m_ptr;
		}

		// compare with other Smart ptr
		template<class U>
		inline bool operator == (SmartPointer<U>& OtherPtr)
		{
			return m_ptr == OtherPtr.m_ptr;
		}

		// Compare with Wrapped Class pointer
		template<class U>
		inline bool operator == (U* i_ptr)
		{
			return m_ptr == i_ptr;
		}

		// Not equals with other Weak ptr
		template<class U>
		inline bool operator!=(const WeakPointer<U>& OtherPtr)
		{
			return m_ptr != OtherPtr.m_ptr;
		}

		// Not equals with samw Smart ptr
		inline bool operator!=(const SmartPointer<T>& OtherPtr)
		{
			return m_ptr != OtherPtr.m_ptr;
		}

		// Not equals with other Smart ptr
		template<class U>
		inline bool operator!=(const SmartPointer<U>& OtherPtr)
		{
			return m_ptr != OtherPtr.m_ptr;
		}

		// Added bool condition for if(ptr) direct check
		inline operator bool() const
		{
			return (m_ptr != nullptr);
		}

		// Get a SmartPointer from a WeakPointer
		// Used to operate on the resource from a weak pointer
		SmartPointer<T> GetSmartPointer()
		{
			return SmartPointer<T>(*this);
		}

		// destructor
		~WeakPointer()
		{
			release();
		}


	}; // End of class WeakPointer

}// End of Engine
