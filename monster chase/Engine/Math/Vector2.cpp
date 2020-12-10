
#include "Vector2.h"
#include "MathUtils.h"

#include "iostream"
#include "math.h"
#include "stdlib.h"
#include "assert.h"

namespace Engine
{
	// constructors
	point2d::point2d() :
		x(0.f),
		y(0.f)
	{
	}

	point2d::point2d(const point2d& i_v1) :	// copy constructor
		x(i_v1.x),
		y(i_v1.y)
	{
	}

	point2d::point2d(const float i_x, const float i_y) :
		x(i_x),
		y(i_y)
	{
		assert(!IsNAN(i_x));
		assert(!IsNAN(i_y));
	}


	//operator overloading in class functions
	point2d& point2d::operator = (const point2d& i_v2)
	{
		x = i_v2.x;
		y = i_v2.y;
		return *this;
	}

	point2d& point2d::operator = (const float X)
	{
		assert(!IsNAN(X));
		x = X;
		y = X;
		return *this;
	}

	point2d point2d::operator - (void) //negate the member functions and return a new point2d variable
	{
		return point2d(-x, -y);
	}

	point2d& point2d::operator += (const float i_f)
	{
		assert(!IsNAN(i_f));
		x += i_f;
		y += i_f;
		return *this;
	}

	point2d& point2d::operator += (const point2d& i_v)
	{
		x += i_v.x;
		y += i_v.y;
		return *this;
	}

	point2d& point2d::operator -= (const float i_f)
	{
		assert(!IsNAN(i_f));
		x -= i_f;
		y -= i_f;
		return *this;
	}

	point2d& point2d::operator -= (const point2d& i_v)
	{
		x -= i_v.x;
		y -= i_v.y;
		return *this;
	}

	point2d& point2d::operator *= (const float i_f)
	{
		assert(!IsNAN(i_f));
		x *= i_f;
		y *= i_f;
		return *this;
	}

	point2d& point2d::operator *= (const point2d& i_v)
	{
		x *= i_v.x;
		y *= i_v.y;
		return *this;
	}

	point2d& point2d::operator /= (const float i_f)
	{
		assert(!IsNAN(i_f));
		assert(!IsZero(i_f));
		x /= i_f;
		y /= i_f;
		return *this;
	}

	point2d& point2d::operator /= (const point2d& i_v)
	{
		x /= i_v.x;
		y /= i_v.y;
		return *this;
	}

	// operator overloading the operators that do not change member variables
	point2d operator + (const point2d& lhs, const point2d& rhs)
	{
		return point2d((lhs.x + rhs.x), (lhs.y + rhs.y));
	}

	point2d operator - (const point2d& lhs, const point2d& rhs)
	{
		return point2d((lhs.x - rhs.x), (lhs.y - rhs.y));
	}

	point2d operator * (const point2d& lhs, const float rhs)
	{
		assert(!IsNAN(rhs));
		return point2d((lhs.x * rhs), (lhs.y * rhs));
	}

	point2d operator * (const point2d& lhs, point2d& rhs)
	{
		return point2d((lhs.x * rhs.x), (lhs.y * rhs.y));
	}

	point2d operator / (const point2d& lhs, const float rhs)
	{
		assert(!IsNAN(rhs));
		assert(!IsZero(rhs));
		return point2d((lhs.x / rhs), (lhs.y / rhs));
	}

	point2d operator / (const point2d& lhs, const point2d& rhs)
	{
		return point2d((lhs.x / rhs.x), (lhs.y / rhs.x));
	}

	// comparitive operators
	bool operator == (const point2d& lhs, const point2d& rhs)
	{
		return (lhs.x == rhs.x) && (lhs.y == rhs.y);
	}

	bool operator != (const point2d& lhs, const point2d& rhs)
	{
		return (lhs.x != rhs.x) || (lhs.y != rhs.y);
	}

	bool operator ! (const point2d& i_ToCheck)
	{
		//assert(i_ToCheck.x != 0);
		//assert(i_ToCheck.y != 0);
		if (i_ToCheck.x == 0 && i_ToCheck.y == 0)
			return false;
		return true;
	}

	// vector operations
	float dot(const point2d& lhs, const point2d& rhs)
	{
		return((lhs.x * rhs.x) + (lhs.y * rhs.y));
	}

	float point2d::Magnetude()
	{
		const float MagSqr = (x * x) + (y * y);
		return sqrt(MagSqr);
	}

	point2d point2d::Normalize()
	{
		const float	Mag = Magnetude();
		assert(!IsNAN(Mag));
		assert(!IsZero(Mag));
		return point2d((x / Mag), (y / Mag));
	}
}

