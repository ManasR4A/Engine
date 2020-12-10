#pragma once
#include "Math.h"
#include "Vector3.h"

namespace Engine
{
	class Matrix3
	{
	public:
		float	m11, m12, m13,
			m21, m22, m23,
			m31, m32, m33;

		Matrix3() :
			m11(NAN), m12(NAN), m13(NAN),
			m21(NAN), m22(NAN), m23(NAN),
			m31(NAN), m32(NAN), m33(NAN)
		{
		}
		Matrix3(float i11, float i12, float i13,
			float i21, float i22, float i23,
			float i31, float i32, float i33)
			:
			m11(i11), m12(i12), m13(i13),
			m21(i21), m22(i22), m23(i23),
			m31(i31), m32(i32), m33(i33)
		{

		}

		point3d Row(size_t i_RowNum) const;
		point3d Col(size_t i_ColNum) const;

		// Creating a Rotation Matrix based on an inputted degree value
		static Matrix3 CV_CreateZRotationMat(const float i_z);

		float det()
		{
			float minor11 = (m22 * m33) - (m23 * m32);
			float minor12 = (m21 * m33) - (m23 * m31);
			float minor13 = (m21 * m32) - (m22 * m31);

			return (m11 * minor11) - (m12 * minor12) + (m13 * minor13);
		}

	};
}
