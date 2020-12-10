#pragma once
#include "stdint.h"
#include "assert.h"
#include "RefCounter.h"

namespace Engine 
{
	template<class U>
	class WeakPointer;


	template<class T>
	class SmartPointer
	{
	public:
		template<class U>
		friend class SmartPointer;

		template<class U>
		friend class WeakPointer;


	private:
		T* m_ptr = nullptr;
		RefCounter* Refs = nullptr;

		void release()
		{
			if (Refs)
			{
				// decrease referrence count
				assert(Refs->GetSmartRefs() > 0);
				Refs->DecreaseSmartRef();

				// if decreased ref count is zero deal with the pointers.
				if (Refs->GetSmartRefs() == 0)
				{
					assert(m_ptr);
					delete m_ptr;
					m_ptr = nullptr;
					if (Refs->GetWeakRefs() == 0)
					{
						delete Refs;
						Refs = nullptr;
					}
				}
			}
		}

	public:

		// default Constructors
		SmartPointer() :
			Refs(nullptr),
			m_ptr(nullptr)
		{}

		SmartPointer(T* i_ptr) :
			Refs(i_ptr ? new RefCounter(1, 0) : nullptr),
			m_ptr(i_ptr)
		{}

		//----------Copy Constructor----------//

		// From other SmartPointer of the same type
		SmartPointer(const SmartPointer& OtherPtr) :
			Refs(OtherPtr.Refs),
			m_ptr(OtherPtr.m_ptr)
		{
			if (Refs)
			{
				assert(m_ptr != nullptr);
				Refs->IncreaseSmartRef();
			}
		}

		// From other type of SmartPointer
		template<class U>
		SmartPointer(const SmartPointer<U>& OtherPointer) :
			Refs(OtherPointer.pCounters),
			m_ptr(OtherPointer.pPtr)
		{
			if (Refs)
			{
				assert(m_ptr != nullptr);
				Refs->IncreaseSmartRef();
			}
		}

		// From a WeakPointer of the same type
		SmartPointer(const WeakPointer<T>& OtherPointer)
		{

			// Only copy the refrences and the OG pointer if there is atleast 1 SmartPointer pointing to the object.
			if (OtherPointer.Refs && OtherPointer.Refs->GetSmartRefs() > 0)
			{
				Refs = OtherPointer.Refs;
				m_ptr = OtherPointer.m_ptr;
			}
				
			else
			{
				Refs = nullptr;
				m_ptr = nullptr;
			}
				
			// If the Refs exist, increase the SmartPointer Ref Count
			if (Refs)
			{
				assert(Refs->GetSmartRefs() > 0);
				assert(m_ptr != nullptr);

				Refs->IncreaseSmartRef();
			}
		}

		// From a WeakPointer of different type
		template<class U>
		SmartPointer(const WeakPointer<U>& OtherPointer)
		{

			// Only copy the refrences and the OG pointer if there is atleast 1 SmartPointer pointing to the object.
			if (OtherPointer.Refs && OtherPointer.Refs->GetSmartRefs() > 0)
			{
				Refs = OtherPointer.Refs;
				m_ptr = OtherPointer.m_ptr;
			}

			else
			{
				Refs = nullptr;
				m_ptr = nullptr;
			}

			// If the Refs exist, increase the SmartPointer Ref Count
			if (Refs)
			{
				assert(Refs->GetSmartRefs() > 0);
				assert(m_ptr != nullptr);

				Refs->IncreaseSmartRef();
			}
		}




		//----------Move Semantic Constructors----------//

		// From other SmartPointer of same type
		SmartPointer(SmartPointer&& OtherPointer) noexcept :
			Refs(OtherPointer.Refs),
			m_ptr(OtherPointer.m_ptr)
		{
			OtherPointer.Refs = nullptr;
			OtherPointer.m_ptr = nullptr;
		}

		// From a SmartPointer of a different Type
		template<class U>
		SmartPointer(SmartPointer<U>&& OtherPointer) :
			Refs(OtherPointer.Refs),
			m_ptr(OtherPointer.m_ptr)
		{
			OtherPointer.Refs = nullptr;
			OtherPointer.m_ptr = nullptr;
		}

		// From a Weak Pointer of the same type
		SmartPointer(WeakPointer<T>&& OtherPointer) :
			Refs(OtherPointer.Refs),
			m_ptr(OtherPointer.m_ptr)
		{
			OtherPointer.Refs = nullptr;
			OtherPointer.m_ptr = nullptr;
		}

		// From a WeakPointer of a different type
		template<class U>
		SmartPointer(WeakPointer<U>&& OtherPointer) :
			Refs(OtherPointer.Refs),
			m_ptr(OtherPointer.m_ptr)
		{
			OtherPointer.Refs = nullptr;
			OtherPointer.m_ptr = nullptr;
		}


		//-------- OPERATOR OVERLOADS ----------//

		// Assidgnment Operator
		SmartPointer& operator = (const SmartPointer& OtherPointer)
		{
			if (m_ptr != OtherPointer.m_ptr)
			{
				// release the previous holding pointer
				release();

				// update the wrapped pointer and Refs
				Refs = OtherPointer.Refs;
				m_ptr = OtherPointer.m_ptr;

				assert(Refs->GetSmartRefs() > 0); // To check if there is atlease one other pointer to the things.
				Refs->IncreaseSmartRef();
			}

			return *this;
		}

		// Assidgnment Operator from other type of SmartPointer
		template<class U>
		SmartPointer& operator = (const SmartPointer<U>& OtherPointer)
		{
			if (m_ptr != OtherPointer.m_ptr)
			{
				// release the previous holding pointer
				release();

				// update the wrapped pointer and Refs
				Refs = OtherPointer.Refs;
				m_ptr = OtherPointer.m_ptr;

				assert(Refs->GetSmartRefs() > 0); // To check if there is atlease one other pointer to the things.
				Refs->IncreaseSmartRef();
			}

			return *this;
		}

		// Assignment Operator  From the same type of WeakPointer
		SmartPointer& operator = (const WeakPointer<T> & OtherPointer)
		{
			if (m_ptr != OtherPointer.m_ptr)
			{
				release();

				// Only copy the refrences and the OG pointer if there is atleast 1 SmartPointer pointing to the object.
				if (OtherPointer.Refs && OtherPointer.Refs->GetSmartRefs() > 0)
				{
					Refs = OtherPointer.Refs;
					m_ptr = OtherPointer.m_ptr;
				}

				else
				{
					Refs = nullptr;
					m_ptr = nullptr;
				}
				
				assert(Refs->GetSmartRefs() > 0);
				Refs->IncreaseSmartRef();
			}

			return *this;
		}

		// Assignment Operator  From different type of WeakPointer
		template <class U>
		SmartPointer& operator = (const WeakPointer<U>& OtherPointer)
		{
			if (m_ptr != OtherPointer.pPtr)
			{
				release();

				// Only copy the refrences and the OG pointer if there is atleast 1 SmartPointer pointing to the object.
				if (OtherPointer.Refs && OtherPointer.Refs->GetSmartRefs() > 0)
				{
					Refs = OtherPointer.Refs;
					m_ptr = OtherPointer.m_ptr;
				}

				else
				{
					Refs = nullptr;
					m_ptr = nullptr;
				}

				assert(Refs->GetSmartRefs() > 0);
				Refs->IncreaseSmartRef();
			}

			return *this;
		}

		// Move Semantic Assignment operator from a SmartPointer
		template<class U>
		SmartPointer& operator = (SmartPointer<U>&& OtherPointer) noexcept
		{
			if (m_ptr != OtherPointer.m_ptr)
			{
				release();
				Refs = OtherPointer.Refs;
				m_ptr = OtherPointer.m_ptr;
				OtherPointer.Refs = nullptr;
				OtherPointer.m_ptr = nullptr;
			}

			return *this;
		}

		// Move Semantic Assignment operator from a WeakPointer
		template<class U>
		SmartPointer& operator = (WeakPointer<U>&& OtherPointer)
		{
			if (m_ptr != OtherPointer.m_ptr)
			{
				release();
				Refs = OtherPointer.Refs;
				m_ptr = OtherPointer.m_ptr;
				OtherPointer.Refs = nullptr;
				OtherPointer.m_ptr = nullptr;
			}

			return *this;
		}

		// nullptr specific Assignment operator
		SmartPointer& operator = (std::nullptr_t i_nullptr)
		{
			release();
			Refs = nullptr;
			m_ptr = nullptr;
			return *this;
		}

		// holding class pointer Assignment operator
		SmartPointer& operator = (T* i_ptr)
		{
			if (m_ptr != i_ptr)
			{
				release();
				if (i_ptr)
					Refs = new RefCounter(1, 0);
				else
					Refs = nullptr;

				m_ptr = i_ptr; // handles nullptr consition as well
			}

			return *this;
		}

		// compare with other smart ptr
		template<class U>
		inline bool operator == (SmartPointer<U>& OtherPtr)
		{
			return m_ptr == OtherPtr.m_ptr;
		}

		// compare with other weak ptr
		template<class U>
		inline bool operator == (WeakPointer<U>& OtherPtr)
		{
			return m_ptr == OtherPtr.m_ptr;
		}

		// compare with the native class pointer
		template<class U>
		inline bool operator == (U* i_ptr) const
		{
			return m_ptr == i_ptr;
		}

		// compare with nullptr
		inline bool operator == (std::nullptr_t nullp) const
		{
			return m_ptr == nullptr;
		}

		// Not equals with other smart ptr
		template<class U>
		inline bool operator != (const SmartPointer<U>& OtherPtr)
		{
			return m_ptr != OtherPtr.m_ptr;
		}

		// Not equals with other weak ptr
		template<class U>
		inline bool operator != (const WeakPointer<U>& OtherPtr)
		{
			return m_ptr != OtherPtr.m_ptr;
		}

		// Added bool condition for if(ptr) direct check
		inline operator bool() const
		{
			return (m_ptr != nullptr);
		}

		// Overload of -> operator
		T* operator->()
		{
			return m_ptr;
		}

		// Overload dereference operatoor
		T& operator*()
		{
			assert(m_ptr);
			return (*m_ptr);
		}

		// destructor

		~SmartPointer()
		{
			release();
		}


	}; // End of class SmartPointer

}// End of Engine


#include "WeakPointer.h"