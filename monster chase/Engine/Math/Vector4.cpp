#include "Vector4.h"
#include "MathUtils.h"

#include "assert.h"

namespace Engine
{
	// constructors
	point4d::point4d() :
		x(0.f),
		y(0.f),
		z(0.f),
		w(0.f)
	{
	}

	point4d::point4d(const point4d& i_v1) :	// copy constructor
		x(i_v1.x),
		y(i_v1.y),
		z(i_v1.z),
		w(i_v1.w)
	{
	}

	point4d::point4d(const point3d& i_vec,const float i_w):
		x(i_vec.x),
		y(i_vec.y),
		z(i_vec.z),
		w(i_w)
	{
		assert(!IsNAN(i_w));
	}

	point4d::point4d(const float i_x, const float i_y, const float i_z, const float i_w) :
		x(i_x),
		y(i_y),
		z(i_z),
		w(i_w)
	{
		assert(!IsNAN(i_x));
		assert(!IsNAN(i_y));
		assert(!IsNAN(i_z));
		assert(!IsNAN(i_w));
	}


	//operator overloading in class functions
	point4d& point4d::operator = (const point4d& i_v2)
	{
		x = i_v2.x;
		y = i_v2.y;
		z = i_v2.z;
		w = i_v2.w;
		return *this;
	}

	point4d& point4d::operator = (const float X)
	{
		assert(!IsNAN(X));
		x = X;
		y = X;
		z = X;
		w = X;
		return *this;
	}

	point4d point4d::operator - (void) //negate the member functions and return a new point4d variable
	{
		return point4d(-x, -y, -z, -w);
	}

	point4d& point4d::operator += (const float i_f)
	{
		assert(!IsNAN(i_f));
		x += i_f;
		y += i_f;
		z += i_f;
		w += i_f;
		return *this;
	}

	point4d& point4d::operator += (const point4d& i_v)
	{
		x += i_v.x;
		y += i_v.y;
		z += i_v.z;
		w += i_v.w;
		return *this;
	}

	point4d& point4d::operator -= (const float i_f)
	{
		assert(!IsNAN(i_f));
		x -= i_f;
		y -= i_f;
		z -= i_f;
		w -= i_f;
		return *this;
	}

	point4d& point4d::operator -= (const point4d& i_v)
	{
		x -= i_v.x;
		y -= i_v.y;
		z -= i_v.z;
		w -= i_v.w;
		return *this;
	}

	point4d& point4d::operator *= (const float i_f)
	{
		assert(!IsNAN(i_f));
		x *= i_f;
		y *= i_f;
		z *= i_f;
		w *= i_f;
		return *this;
	}

	point4d& point4d::operator /= (const float i_f)
	{
		assert(!IsNAN(i_f));
		assert(!IsZero(i_f));
		x /= i_f;
		y /= i_f;
		z /= i_f;
		w /= i_f;
		return *this;
	}

	// operator overloading the operators that do not change member variables
	point4d operator + (const point4d& lhs, const point4d& rhs)
	{
		return point4d((lhs.x + rhs.x), (lhs.y + rhs.y), (lhs.z + rhs.z), (lhs.w + rhs.w));
	}

	point4d operator - (const point4d& lhs, const point4d& rhs)
	{
		return point4d((lhs.x - rhs.x), (lhs.y - rhs.y), (lhs.z - rhs.z), (lhs.w - rhs.w));
	}

	point4d operator * (const point4d& lhs, const float rhs)
	{
		assert(!IsNAN(rhs));
		return point4d((lhs.x * rhs), (lhs.y * rhs), (lhs.z * rhs), (lhs.w * rhs));
	}

	point4d operator * (const float lhs, const point4d& rhs)
	{
		assert(!IsNAN(lhs));
		return point4d((lhs * rhs.x), (lhs * rhs.y), (lhs * rhs.z), (lhs * rhs.w));
	}

	point4d operator * (const point4d& lhs, point4d& rhs)
	{
		return point4d((lhs.x * rhs.x), (lhs.y * rhs.y), (lhs.z * rhs.z), (lhs.w * rhs.w));
	}

	point4d operator / (const point4d& lhs, const float rhs)
	{
		assert(!IsNAN(rhs));
		assert(!IsZero(rhs));
		return point4d((lhs.x / rhs), (lhs.y / rhs), (lhs.z / rhs), (lhs.w / rhs));
	}

	point4d operator / (const point4d& lhs, const point4d& rhs)
	{
		assert(!IsZero(rhs.x));
		assert(!IsZero(rhs.y));
		assert(!IsZero(rhs.z));
		assert(!IsZero(rhs.w));
		return point4d((lhs.x / rhs.x), (lhs.y / rhs.y), (lhs.z / rhs.z), (lhs.w / rhs.w));
	}

	// comparitive operators
	bool operator == (const point4d& lhs, const point4d& rhs)
	{
		return AreEqualInRange(lhs.x, rhs.x, 0.001f) && AreEqualInRange(lhs.y, rhs.y, 0.001f) && AreEqualInRange(lhs.z, rhs.z, 0.001f) && AreEqualInRange(lhs.w, rhs.w, 0.001f);
	}

	bool operator != (const point4d& lhs, const point4d& rhs)
	{
		return (lhs.x != rhs.x) || (lhs.y != rhs.y) || (lhs.z != rhs.z) || (lhs.w != rhs.w);
	}

	bool operator ! (const point4d& i_ToCheck)
	{
		if (!(IsNAN(i_ToCheck.x) && IsNAN(i_ToCheck.y) && IsNAN(i_ToCheck.z) && IsNAN(i_ToCheck.w)))
			return false;

		return true;
	}

	// vector operations
	float dot(const point4d& lhs, const point4d& rhs)
	{
		return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z) + (lhs.w * rhs.w);
	}

	float point4d::Magnetude()
	{
		float MagSqr = (x * x) + (y * y) + (z * z) + (w * w);
		return sqrt(MagSqr);
	}

	point4d point4d::Normalize()
	{
		const float Mag = Magnetude();

		assert(!IsNAN(Mag));
		assert(!IsZero(Mag));
		return point4d((x / Mag), (y / Mag), (z / Mag), (w / Mag));
	}

}
