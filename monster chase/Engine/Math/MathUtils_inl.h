#pragma once

#include "MathUtils.h"

namespace Engine
{
	bool IsNAN(float i_value)
	{
		// Make a copy and check against itself to see if the value was NAN or not
		volatile float value = i_value;
		return value != value;
	}

	bool AreEqualInRange(float i_lhs, float i_rhs, float i_threshold)
	{
		return fabs(static_cast<double>(i_lhs) - static_cast<double>(i_rhs)) < i_threshold;
	}

	bool IsZero(float i_value)
	{
		return AreEqualInRange(i_value, 0.0f, 0.001f);
	}

	float DegreesToRadians(float i_Degrees)
	{
		static const float DegToRad = float(PI) / 180.0f;

		return i_Degrees * DegToRad;
	}
}

