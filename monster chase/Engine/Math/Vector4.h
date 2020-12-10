#pragma once
#include "Vector3.h"

namespace Engine
{
	class point4d
	{
	public:
		float x = 0.f, y = 0.f, z = 0.f, w = 0.f;
		// point4d(float, float);
		point4d();
		point4d(const point4d&);
		point4d(const point3d&,const float);
		point4d(const float, const float, const float, const float);

		// only overloading the functions that modify member variables
		point4d& operator = (const point4d&);
		point4d& operator = (const float);

		// negate
		point4d operator - (void);

		// operators that change the member variables
		point4d& operator += (const float);
		point4d& operator += (const point4d&);
		point4d& operator -= (const float);
		point4d& operator -= (const point4d&);
		point4d& operator *= (const float);
		point4d& operator /= (const float);

		// return 0 if i_Vector is invalid otherwise returns magnetude of the vector
		float Magnetude();

		/*	returns Zero Vector (0,0,0,0) if the inputted vector's magnetude is 0.
		Otherwise returns the unit vector of the inputted vector	*/
		point4d Normalize();
	};


	// overloading operators that do not modify the member variables
	point4d operator + (const point4d&, const point4d&);
	point4d operator - (const point4d&, const point4d&);
	point4d operator * (const point4d&, const float);
	point4d operator * (const float, const point4d&);
	point4d operator * (const point4d&, const point4d&);
	point4d operator / (const point4d&, const float);
	point4d operator / (const point4d&, const point4d&);

	bool operator == (const point4d&, const point4d&);
	bool operator != (const point4d&, const point4d&);
	bool operator ! (const point4d&);
	float dot(const point4d&, const point4d&);

}
