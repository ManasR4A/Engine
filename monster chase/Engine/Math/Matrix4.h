#pragma once
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix3.h"

namespace Engine
{
	// For cooridinates in 3d
	class Matrix4
	{
	public:

		//	col1, col2, col3, col4
		float	m_11, m_12, m_13, m_14, // row 1
				m_21, m_22, m_23, m_24, // row 2
				m_31, m_32, m_33, m_34, // row 3
				m_41, m_42, m_43, m_44; // row 4

		// constructors
		Matrix4(); // creates an Identity Matrix

		Matrix4(float i_11, float i_12, float i_13, float i_14,
				float i_21, float i_22, float i_23, float i_24,
				float i_31, float i_32, float i_33, float i_34,
				float i_41, float i_42, float i_43, float i_44);

		// Copy constructor & assignment operator
		Matrix4(const Matrix4& i_other);
		Matrix4& operator = (const Matrix4& i_other);

		// For Matrix4 Matrix4 Multiplication only
		Matrix4 operator * (const Matrix4& i_other) const;

#pragma region Transform component Matrices

		// Creating the Scale multiplying matrix from a point3d
		static Matrix4 CreateScale(const point3d&);

		// Creates the Rotation multiplying matrix based on axes and Vector oritation
			// Layout for row vector multiplies ( V = V * M )
		static Matrix4 RV_CreateXRotationMat(float i_RotationRadians);
		static Matrix4 RV_CreateYRotationMat(float i_RotationRadians);
		static Matrix4 RV_CreateZRotationMat(float i_RotationRadians);
			// Layout for column vector multiplies ( V = M * V )
		static Matrix4 CV_CreateXRotationMat(float i_RotationRadians);
		static Matrix4 CV_CreateYRotationMat(float i_RotationRadians);
		static Matrix4 CV_CreateZRotationMat(float i_RotationRadians);

		// Creating the translation multiplying matrix bsaed on Vector Axes
		static Matrix4 RV_CreateTranslationMat(const point3d& i_trans);
		static Matrix4 CV_CreateTranslationMat(const point3d& i_trans);

		// Return a matrix that is the inverse ASSUMING this matrix has axis rotation and translation only.
		Matrix4 GetInverseRotTransCV() const;
		Matrix4 GetInverseRotTransRV() const;

#pragma endregion

#pragma region Matrix data functions

		// Returns the point4d vector for a particular row of the matrix
		point4d GetRow(size_t i_row) const;

		// Returns the point4d vector for a particular column of the matrix
		point4d GetColumn(size_t i_col) const;

		// Returns Transpose matrix of this instance
		Matrix4 Transpose() const;

		// Returns the inverse matrix of this instance
		Matrix4 Inverse() const;

		// Returns the inverse of the matrix and takes in the output matrix.
		void Inverse(Matrix4&) const;

#pragma endregion

		// Functions for updating transform of a point
		point3d TransformPointRV(const point3d& i_Point) const;
		point3d TransformPointCV(const point3d& i_Point) const;

		point3d TransformNormalRV(const point3d& i_Normal) const;
		point3d TransformNormalCV(const point3d& i_Normal) const;

	};

	Matrix4 operator * (const Matrix4&, const float);
	Matrix4 operator / (const Matrix4&, const float);

	void Multiply(const Matrix4& lhs, const Matrix4& rhs, Matrix4& Output);

	// Allows us to use V = M * V; (i.e. column vector)
	/* For multiplying M x V
		|m, m, m, m|	|v|
		|m, m, m, m| \/ |v|
		|m, m, m, m| /\ |v|
		|m, m, m, m|	|v|
	*/
	point4d operator * (const Matrix4&, const point4d&);

	// Allows us to use V = V * M; (i.e. row vector)
	/* For multiplying M x V
						|m, m, m, m|
					 \/	|m, m, m, m|
					 /\	|m, m, m, m|
		|v, v, v, v|	|m, m, m, m|
	*/
	point4d operator * (const point4d&, const Matrix4&);

	bool operator == (const Matrix4& lhs, const Matrix4& rhs);

	// Indentity matrix
	static const Matrix4 Identity4(	1.f, 0.f, 0.f, 0.f,
									0.f, 1.f, 0.f, 0.f,
									0.f, 0.f, 1.f, 0.f,
									0.f, 0.f, 0.f, 1.f);
									
}