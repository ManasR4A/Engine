#pragma once
#include "math.h"

namespace Engine
{
	class point2d
	{
	public:
		float x = 0, y = 0;
		// point2d(float, float);
		point2d();
		point2d(const point2d&);
		point2d(const float , const float);

		// only overloading the functions that modify member variables
		point2d& operator = (const point2d&);
		point2d& operator = (const float);

		// negate
		point2d operator - (void);

		// operators that change the member variables
		point2d& operator += (const float);
		point2d& operator += (const point2d&);
		point2d& operator -= (const float);
		point2d& operator -= (const point2d&);
		point2d& operator *= (const float);
		point2d& operator *= (const point2d&);
		point2d& operator /= (const float);
		point2d& operator /= (const point2d&);

		// return 0 if i_Vector is invalid otherwise returns magnetude of the vector
		float Magnetude();

		/*	returns Zero Vector (0,0) if the inputted vector's magnetude is 0.
		Otherwise returns the unit vector of the inputted vector	*/
		point2d Normalize();

	};


	// overloading operators that do not modify the member variables
	point2d operator + (const point2d&, const point2d&);
	point2d operator - (const point2d&, const point2d&);
	point2d operator * (const point2d&, const float);
	point2d operator * (const point2d&, const point2d&);
	point2d operator / (const point2d&, const float);
	point2d operator / (const point2d&, const point2d&);

	bool operator == (const point2d&, const point2d&);
	bool operator != (const point2d&, const point2d&);
	bool operator ! (const point2d&);
	float dot(const point2d&, const point2d&);

}

