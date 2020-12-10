#include "Vector3.h"
#include "Utils/Utils.h"

#include "assert.h"

namespace Engine
{
	// constructors
	point3d::point3d() :
		x(0.f),
		y(0.f),
		z(0.f)
	{
	}

	point3d::point3d(const point2d& i_vec, const float i_z) :
		x(i_vec.x),
		y(i_vec.y),
		z(i_z)
	{
		assert(!IsNAN(i_z));
	}

	point3d::point3d(const point3d& i_v1) :	// copy constructor
		x(i_v1.x),
		y(i_v1.y),
		z(i_v1.z)
	{
	}

	point3d::point3d(const float i_x, const float i_y, const float i_z) :
		x(i_x),
		y(i_y),
		z(i_z)
	{
		assert(!IsNAN(i_x));
		assert(!IsNAN(i_y));
		assert(!IsNAN(i_z));
	}


	//operator overloading in class functions
	point3d& point3d::operator = (const point3d& i_v2)
	{
		x = i_v2.x;
		y = i_v2.y;
		z = i_v2.z;
		return *this;
	}

	point3d& point3d::operator = (const float X)
	{
		assert(!IsNAN(X));
		x = X;
		y = X;
		z = X;
		return *this;
	}

	point3d point3d::operator - (void) //negate the member functions and return a new point3d variable
	{
		return point3d(-x, -y, -z);
	}

	point3d& point3d::operator += (const float i_f)
	{
		assert(!IsNAN(i_f));
		x += i_f;
		y += i_f;
		z += i_f;
		return *this;
	}

	point3d& point3d::operator += (const point3d& i_v)
	{
		x += i_v.x;
		y += i_v.y;
		z += i_v.z;
		return *this;
	}

	point3d& point3d::operator -= (const float i_f)
	{
		assert(!IsNAN(i_f));
		x -= i_f;
		y -= i_f;
		z -= i_f;
		return *this;
	}

	point3d& point3d::operator -= (const point3d& i_v)
	{
		x -= i_v.x;
		y -= i_v.y;
		z -= i_v.z;
		return *this;
	}

	point3d& point3d::operator *= (const float i_f)
	{
		assert(!IsNAN(i_f));
		x *= i_f;
		y *= i_f;
		z *= i_f;
		return *this;
	}

	point3d& point3d::operator /= (const float i_f)
	{
		assert(!IsNAN(i_f));
		assert(!IsZero(i_f));
		x /= i_f;
		y /= i_f;
		z /= i_f;
		return *this;
	}

	// operator overloading the operators that do not change member variables
	point3d operator + (const point3d& lhs, const point3d& rhs)
	{
		return point3d((lhs.x + rhs.x), (lhs.y + rhs.y), (lhs.z + rhs.z));
	}

	point3d operator - (const point3d& lhs, const point3d& rhs)
	{
		return point3d((lhs.x - rhs.x), (lhs.y - rhs.y), (lhs.z - rhs.z));
	}

	point3d operator * (const point3d& lhs, const float rhs)
	{
		assert(!IsNAN(rhs));
		return point3d((lhs.x * rhs), (lhs.y * rhs), (lhs.z * rhs));
	}

	point3d operator * (const float lhs, const point3d& rhs)
	{
		assert(!IsNAN(lhs));
		return point3d((lhs * rhs.x), (lhs * rhs.y), (lhs * rhs.z));
	}

	point3d operator * (const point3d& lhs, point3d& rhs)
	{
		return point3d((lhs.x * rhs.x), (lhs.y * rhs.y), (lhs.z * rhs.z));
	}

	point3d operator / (const point3d& lhs, const float rhs)
	{
		assert(!IsNAN(rhs));
		assert(!IsZero(rhs));
		return point3d((lhs.x / rhs), (lhs.y / rhs), (lhs.z / rhs));
	}

	point3d operator / (const point3d& lhs, const point3d& rhs)
	{
		assert(!IsNAN(rhs.x));
		assert(!IsNAN(rhs.y));
		assert(!IsNAN(rhs.z));
		return point3d((lhs.x / rhs.x), (lhs.y / rhs.y), (lhs.z / rhs.z));
	}

	// comparitive operators
	bool operator == (const point3d& lhs, const point3d& rhs)
	{
		return (lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.z == rhs.z);
	}

	bool operator != (const point3d& lhs, const point3d& rhs)
	{
		return (lhs.x != rhs.x) || (lhs.y != rhs.y) || (lhs.z != rhs.z);
	}

	bool operator ! (const point3d& i_ToCheck)
	{
		if (!(IsNAN(i_ToCheck.x) && IsNAN(i_ToCheck.y) && IsNAN(i_ToCheck.z)))
			return false;

		return true;
	}

	// vector operations
	float dot(const point3d& lhs, const point3d& rhs)
	{
		return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z);
	}

	point3d cross(const point3d& i_lhs, const point3d& i_rhs)
	{
		return point3d(i_lhs.y * i_rhs.z - i_lhs.z * i_rhs.y,
			i_lhs.z * i_rhs.x - i_lhs.x * i_rhs.z,
			i_lhs.x * i_rhs.y - i_lhs.y * i_rhs.x);
	}

	float point3d::Magnetude()
	{
		float MagSqr = (x * x) + (y * y) + (z * z);
		return sqrt(MagSqr);
	}

	point3d point3d::Normalize()
	{
		const float Mag = Magnetude();

		assert(!IsNAN(Mag));
		assert(!IsZero(Mag));
		return point3d((x / Mag), (y / Mag), (z / Mag));
	}
}

