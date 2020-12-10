#pragma once
#include "math.h"
#include "Vector2.h"


namespace Engine
{
	class point3d
	{
	public:
		float x = 0.f, y = 0.f, z = 0.f;
		// point3d(float, float);
		point3d();
		point3d(const point2d&, const float);
		point3d(const point3d&);
		point3d(const float, const float, const float);

		// only overloading the functions that modify member variables
		point3d& operator = (const point3d&);
		point3d& operator = (const float);

		// negate
		point3d operator - (void);

		// operators that change the member variables
		point3d& operator += (const float);
		point3d& operator += (const point3d&);
		point3d& operator -= (const float);
		point3d& operator -= (const point3d&);
		point3d& operator *= (const float);
		point3d& operator /= (const float);

		// return 0 if i_Vector is invalid otherwise returns magnetude of the vector
		float Magnetude();

		/*	returns Zero Vector (0,0,0) if the inputted vector's magnetude is 0.
		Otherwise returns the unit vector of the inputted vector	*/
		point3d Normalize();
	};


	// overloading operators that do not modify the member variables
	point3d operator + (const point3d&, const point3d&);
	point3d operator - (const point3d&, const point3d&);
	point3d operator * (const point3d&, const float);
	point3d operator * (const float, const point3d&);
	point3d operator * (const point3d&, const point3d&);
	point3d operator / (const point3d&, const float);
	point3d operator / (const point3d&, const point3d&);

	bool operator == (const point3d&, const point3d&);
	bool operator != (const point3d&, const point3d&);
	bool operator ! (const point3d&);
	float dot(const point3d&, const point3d&);
	point3d cross(const point3d&, const point3d&);

}
