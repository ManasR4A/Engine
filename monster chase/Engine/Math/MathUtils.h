#pragma once

#include "stdint.h"
#include "math.h"

namespace Engine
{
#define PI  3.14159265358979323846

	// returns true of the value fed is a NAN
	inline bool IsNAN(float i_value);

	// Make sure the threshold is always positive
	inline bool AreEqualInRange(float i_lhs, float i_rhs, float i_threshold);

	// returns true if the value fed was close to a zero.
	inline bool IsZero(float i_value);

	// converts degrees to radians.
	inline float DegreesToRadians(float i_Degrees);

}

#include "MathUtils_inl.h"