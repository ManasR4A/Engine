#pragma once
#include "String"
#include "stdio.h"
#include "Windows.h"

#include "Math/MathUtils.h"

namespace Engine
{
	template<class T>
	inline void Swap(T& First, T& Second)
	{
		T temp = First;
		First = Second;
		Second = temp;
	}

	inline void DebugPrint120(std::string i_StringToPrint)
	{
#ifdef _DEBUG
		const size_t	lenBuffer = 128;
		char			Buffer[lenBuffer];

		sprintf_s(Buffer, lenBuffer, i_StringToPrint.c_str());
		OutputDebugStringA(Buffer);
#endif // __DEBUG

	}
}