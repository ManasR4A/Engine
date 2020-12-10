#include "Matrix3.h"
#include "assert.h"
#include "Utils/Utils.h"

namespace Engine
{
	point3d Matrix3::Row(size_t i_RowNum) const
	{
		assert(!IsNAN(m11));

		switch (i_RowNum)
		{
		case 0:
			return point3d(m11, m12, m13);
		case 1:
			return point3d(m21, m22, m23);
		case 2:
			return point3d(m31, m32, m33);
		default:
			assert(false);
			return point3d(NAN, NAN, NAN);
		}
	}
	point3d Matrix3::Col(size_t i_ColNum) const
	{
		assert(!IsNAN(m11));

		switch (i_ColNum)
		{
		case 0:
			return point3d(m11, m21, m31);
		case 1:
			return point3d(m12, m22, m32);
		case 2:
			return point3d(m13, m23, m33);
		default:
			assert(false);
			return point3d(NAN, NAN, NAN);
		}
	}


	Matrix3 Matrix3::CV_CreateZRotationMat(const float i_z)
	{
		float sin = sinf(i_z);
		float cos = cosf(i_z);

		return Matrix3(
			cos, -sin, 0.0f,
			sin, cos, 0.0f,
			0.0f, 0.0f, 1.0f);
	}
}

