#include "Matrix4.h"
#include "MathUtils.h"

#include "assert.h"

namespace Engine
{
	Matrix4::Matrix4():
		m_11(1.f), m_12(0.f), m_13(0.f), m_14(0.f),
		m_21(0.f), m_22(1.f), m_23(0.f), m_24(0.f),
		m_31(0.f), m_32(0.f), m_33(1.f), m_34(0.f),
		m_41(0.f), m_42(0.f), m_43(0.f), m_44(1.f)
	{
	}

	Matrix4::Matrix4(float i_11, float i_12, float i_13, float i_14,
				 	 float i_21, float i_22, float i_23, float i_24, 
					 float i_31, float i_32, float i_33, float i_34, 
					 float i_41, float i_42, float i_43, float i_44):
		m_11(i_11), m_12(i_12), m_13(i_13), m_14(i_14),
		m_21(i_21), m_22(i_22), m_23(i_23), m_24(i_24),
		m_31(i_31), m_32(i_32), m_33(i_33), m_34(i_34),
		m_41(i_41), m_42(i_42), m_43(i_43), m_44(i_44)
	{

	}

	Matrix4::Matrix4(const Matrix4& i_other):
		m_11(i_other.m_11), m_12(i_other.m_12), m_13(i_other.m_13), m_14(i_other.m_14),
		m_21(i_other.m_21), m_22(i_other.m_22), m_23(i_other.m_23), m_24(i_other.m_44),
		m_31(i_other.m_31), m_32(i_other.m_32), m_33(i_other.m_33), m_34(i_other.m_44),
		m_41(i_other.m_41), m_42(i_other.m_42), m_43(i_other.m_43), m_44(i_other.m_44)
	{
	}

	Matrix4& Matrix4::operator = (const Matrix4& i_other)
	{
		m_11 = i_other.m_11; m_12 = i_other.m_12; m_13 = i_other.m_13; m_14 = i_other.m_14;
		m_21 = i_other.m_21; m_22 = i_other.m_22; m_23 = i_other.m_23; m_24 = i_other.m_24;
		m_31 = i_other.m_31; m_32 = i_other.m_32; m_33 = i_other.m_33; m_34 = i_other.m_34;
		m_41 = i_other.m_41; m_42 = i_other.m_42; m_43 = i_other.m_43; m_44 = i_other.m_44;

		return *this;
	}

	// only for Matrix4 Matrix4 multiplication
	Matrix4 Matrix4::operator * (const Matrix4& i_other) const
	{
		Matrix4 Output;
		assert(!IsNAN(m_11));
		assert(!IsNAN(i_other.m_11));

		//Output.m_11 = dot(point4d(m_11, m_12, m_13, m_14), point4d(i_other.m_11, i_other.m_21, i_other.m_31, i_other.m_41));

		Output.m_11 = m_11 * i_other.m_11 + m_12 * i_other.m_21 + m_13 * i_other.m_31 + m_14 * i_other.m_41;
		Output.m_12 = m_11 * i_other.m_12 + m_12 * i_other.m_22 + m_13 * i_other.m_32 + m_14 * i_other.m_42;
		Output.m_13 = m_11 * i_other.m_13 + m_12 * i_other.m_23 + m_13 * i_other.m_33 + m_14 * i_other.m_43;
		Output.m_14 = m_11 * i_other.m_14 + m_12 * i_other.m_24 + m_13 * i_other.m_34 + m_14 * i_other.m_44;

		Output.m_21 = m_21 * i_other.m_11 + m_22 * i_other.m_21 + m_23 * i_other.m_31 + m_24 * i_other.m_41;
		Output.m_22 = m_21 * i_other.m_12 + m_22 * i_other.m_22 + m_23 * i_other.m_32 + m_24 * i_other.m_42;
		Output.m_23 = m_21 * i_other.m_13 + m_22 * i_other.m_23 + m_23 * i_other.m_33 + m_24 * i_other.m_43;
		Output.m_24 = m_21 * i_other.m_14 + m_22 * i_other.m_24 + m_23 * i_other.m_34 + m_24 * i_other.m_44;

		Output.m_31 = m_31 * i_other.m_11 + m_32 * i_other.m_21 + m_33 * i_other.m_31 + m_34 * i_other.m_41;
		Output.m_32 = m_31 * i_other.m_12 + m_32 * i_other.m_22 + m_33 * i_other.m_32 + m_34 * i_other.m_42;
		Output.m_33 = m_31 * i_other.m_13 + m_32 * i_other.m_23 + m_33 * i_other.m_33 + m_34 * i_other.m_43;
		Output.m_34 = m_31 * i_other.m_14 + m_32 * i_other.m_24 + m_33 * i_other.m_34 + m_34 * i_other.m_44;

		Output.m_41 = m_41 * i_other.m_11 + m_42 * i_other.m_21 + m_43 * i_other.m_31 + m_44 * i_other.m_41;
		Output.m_42 = m_41 * i_other.m_12 + m_42 * i_other.m_22 + m_43 * i_other.m_32 + m_44 * i_other.m_42;
		Output.m_43 = m_41 * i_other.m_13 + m_42 * i_other.m_23 + m_43 * i_other.m_33 + m_44 * i_other.m_43;
		Output.m_44 = m_41 * i_other.m_14 + m_42 * i_other.m_24 + m_43 * i_other.m_34 + m_44 * i_other.m_44;

		return Output;
	}

	// Scale
	Matrix4 Matrix4::CreateScale(const point3d& i_scale)
	{
		return Matrix4(	i_scale.x, 0.f, 0.f, 0.f,
						0.f, i_scale.y, 0.f, 0.f,
						0.f, 0.f, i_scale.z, 0.f,
						0.f, 0.f, 0.f, 1.f);
	}

	// Rotation
	Matrix4 Matrix4::RV_CreateXRotationMat(float i_RotationRadians)
	{
		float rad = DegreesToRadians(i_RotationRadians);
		float sinTheta = sinf(rad);
		float cosTheta = cosf(rad);
		return Matrix4(	1.f, 0.f, 0.f, 0.f,
						0.f, cosTheta, sinTheta, 0.f,
						0.f, -sinTheta, cosTheta, 0.f,
						0.f, 0.f, 0.f, 1.f);
	}

	Matrix4 Matrix4::RV_CreateYRotationMat(float i_RotationRadians)
	{
		float rad = DegreesToRadians(i_RotationRadians);
		float sinTheta = sinf(rad);
		float cosTheta = cosf(rad);
		return Matrix4(	cosTheta, 0.f, -sinTheta, 0.f,
						0.f, 1.f, 0.f, 0.f,
						sinTheta, 0.f, cosTheta, 0.f,
						0.f, 0.f, 0.f, 1.f);
	}

	Matrix4 Matrix4::RV_CreateZRotationMat(float i_RotationRadians)
	{
		float rad = DegreesToRadians(i_RotationRadians);
		float sinTheta = sinf(rad);
		float cosTheta = cosf(rad);
		return Matrix4(	cosTheta, sinTheta, 0.f, 0.f,
						-sinTheta, cosTheta, 0.f, 0.f,
						0.f, 0.f, 1.f, 0.f,
						0.f, 0.f, 0.f, 1.f);
	}

	Matrix4 Matrix4::CV_CreateXRotationMat(float i_RotationRadians)
	{
		float rad = DegreesToRadians(i_RotationRadians);
		float sinTheta = sinf(rad);
		float cosTheta = cosf(rad);
		return Matrix4(	1.f, 0.f, 0.f, 0.f,
						0.f, cosTheta, -sinTheta, 0.f,
						0.f, sinTheta, cosTheta, 0.f,
						0.f, 0.f, 0.f, 1.f);
	}

	Matrix4 Matrix4::CV_CreateYRotationMat(float i_RotationRadians)
	{
		float rad = DegreesToRadians(i_RotationRadians);
		float sinTheta = sinf(rad);
		float cosTheta = cosf(rad);
		return Matrix4(	cosTheta, 0.f, sinTheta, 0.f,
						0.f, 1.f, 0.f, 0.f,
						-sinTheta, 0.f, cosTheta, 0.f,
						0.f, 0.f, 0.f, 1.f);
	}

	Matrix4 Matrix4::CV_CreateZRotationMat(float i_RotationRadians)
	{
		float rad = DegreesToRadians(i_RotationRadians);
		float sinTheta = sinf(rad);
		float cosTheta = cosf(rad);
		return Matrix4(	cosTheta, -sinTheta, 0.f, 0.f,
						sinTheta, cosTheta, 0.f, 0.f,
						0.f, 0.f, 1.f, 0.f,
						0.f, 0.f, 0.f, 1.f);
	}

	// Translation
	Matrix4 Matrix4::RV_CreateTranslationMat(const point3d& i_trans)
	{
		return Matrix4(	1.f, 0.f, 0.f, 0.f,
						0.f, 1.f, 0.f, 0.f,
						0.f, 0.f, 1.f, 0.f,
						i_trans.x, i_trans.y, i_trans.z, 1.f);
	}

	Matrix4 Matrix4::CV_CreateTranslationMat(const point3d& i_trans)
	{
		return Matrix4(	1.f, 0.f, 0.f, i_trans.x,
						0.f, 1.f, 0.f, i_trans.y,
						0.f, 0.f, 1.f, i_trans.z,
						0.f, 0.f, 0.f, 1.f);
	}

	Matrix4 Matrix4::Transpose() const
	{
		return Matrix4( m_11, m_21, m_31, m_41,
						m_12, m_22, m_32, m_42,
						m_13, m_23, m_33, m_43,
						m_14, m_24, m_34, m_44);
	}

	Matrix4 Matrix4::Inverse() const
	{
		float det;
		Matrix4 Inverse;

		Matrix3 min11(m_22, m_23, m_24, m_32, m_33, m_34, m_42, m_43, m_44);
		Matrix3 min12(m_21, m_23, m_24, m_31, m_33, m_34, m_41, m_43, m_44);
		Matrix3 min13(m_21, m_22, m_24, m_31, m_32, m_34, m_41, m_42, m_44);
		Matrix3 min14(m_21, m_22, m_23, m_31, m_32, m_33, m_41, m_42, m_43);
		
		Matrix3 min21(m_12, m_13, m_14, m_32, m_33, m_34, m_42, m_43, m_44);
		Matrix3 min22(m_11, m_13, m_14, m_31, m_33, m_34, m_41, m_43, m_44);
		Matrix3 min23(m_11, m_12, m_14, m_31, m_32, m_34, m_41, m_42, m_44);
		Matrix3 min24(m_11, m_12, m_13, m_31, m_32, m_33, m_41, m_42, m_43);

		Matrix3 min31(m_12, m_13, m_14, m_22, m_23, m_24, m_42, m_43, m_44);
		Matrix3 min32(m_11, m_13, m_14, m_21, m_23, m_24, m_41, m_43, m_44);
		Matrix3 min33(m_11, m_12, m_14, m_21, m_22, m_24, m_41, m_42, m_44);
		Matrix3 min34(m_11, m_12, m_13, m_21, m_22, m_23, m_41, m_42, m_43);
		
		Matrix3 min41(m_12, m_13, m_14, m_22, m_23, m_24, m_32, m_33, m_34);
		Matrix3 min42(m_11, m_13, m_14, m_21, m_23, m_24, m_31, m_33, m_34);
		Matrix3 min43(m_11, m_12, m_14, m_21, m_22, m_24, m_31, m_32, m_34);
		Matrix3 min44(m_11, m_12, m_13, m_21, m_22, m_23, m_31, m_32, m_33);

		Matrix4 Cij(min11.det(), -min12.det(), min13.det(), -(min14.det()),
					-(min21.det()), min22.det(), -(min23.det()), min24.det(),
					min31.det(), -(min32.det()), min33.det(), -(min34.det()),
					-(min41.det()), min42.det(), -(min43.det()), min44.det());

		Matrix4 CijT = Cij.Transpose();
		det = (m_11 * min11.det()) - (m_12 * min12.det()) + (m_13 * min13.det()) - (m_14 * min14.det());
		
		Inverse = CijT * (1.f / det);

		return Inverse;
	}

	void Matrix4::Inverse(Matrix4& o_Mat) const
	{
		float det;

		Matrix3 min11(m_22, m_23, m_24, m_32, m_33, m_34, m_42, m_43, m_44);
		Matrix3 min12(m_21, m_23, m_24, m_31, m_33, m_34, m_41, m_43, m_44);
		Matrix3 min13(m_21, m_22, m_24, m_31, m_32, m_34, m_41, m_42, m_44);
		Matrix3 min14(m_21, m_22, m_23, m_31, m_32, m_33, m_41, m_42, m_43);

		Matrix3 min21(m_12, m_13, m_14, m_32, m_33, m_34, m_42, m_43, m_44);
		Matrix3 min22(m_11, m_13, m_14, m_31, m_33, m_34, m_41, m_43, m_44);
		Matrix3 min23(m_11, m_12, m_14, m_31, m_32, m_34, m_41, m_42, m_44);
		Matrix3 min24(m_11, m_12, m_13, m_31, m_32, m_33, m_41, m_42, m_43);

		Matrix3 min31(m_12, m_13, m_14, m_22, m_23, m_24, m_42, m_43, m_44);
		Matrix3 min32(m_11, m_13, m_14, m_21, m_23, m_24, m_41, m_43, m_44);
		Matrix3 min33(m_11, m_12, m_14, m_21, m_22, m_24, m_41, m_42, m_44);
		Matrix3 min34(m_11, m_12, m_13, m_21, m_22, m_23, m_41, m_42, m_43);

		Matrix3 min41(m_12, m_13, m_14, m_22, m_23, m_24, m_32, m_33, m_34);
		Matrix3 min42(m_11, m_13, m_14, m_21, m_23, m_24, m_31, m_33, m_34);
		Matrix3 min43(m_11, m_12, m_14, m_21, m_22, m_24, m_31, m_32, m_34);
		Matrix3 min44(m_11, m_12, m_13, m_21, m_22, m_23, m_31, m_32, m_33);

		Matrix4 Cij(min11.det(), -min12.det(), min13.det(), -(min14.det()),
			-(min21.det()), min22.det(), -(min23.det()), min24.det(),
			min31.det(), -(min32.det()), min33.det(), -(min34.det()),
			-(min41.det()), min42.det(), -(min43.det()), min44.det());

		Matrix4 CijT = Cij.Transpose();
		det = (m_11 * min11.det()) - (m_12 * min12.det()) + (m_13 * min13.det()) - (m_14 * min14.det());

		o_Mat = CijT * (1.f / det);
	}

	point3d Matrix4::TransformPointCV(const point3d& i_Point) const
	{
		point4d TransformedPoint = (*this) * point4d(i_Point, 1.0f);
		assert(!IsZero(TransformedPoint.w));

		float inv_w = 1.0f / TransformedPoint.w;
		return point3d(TransformedPoint.x * inv_w, TransformedPoint.y * inv_w, TransformedPoint.z * inv_w);
	}



	
	
	
	
	
	
	
	
	
	Matrix4 operator * (const Matrix4& i_mat, const float i_f)
	{
		assert(!IsNAN(i_f));
		return Matrix4((i_mat.m_11 / i_f), (i_mat.m_12 / i_f), (i_mat.m_13 / i_f), (i_mat.m_14 / i_f),
			(i_mat.m_21 / i_f), (i_mat.m_22 / i_f), (i_mat.m_23 / i_f), (i_mat.m_24 / i_f),
			(i_mat.m_31 / i_f), (i_mat.m_32 / i_f), (i_mat.m_33 / i_f), (i_mat.m_34 / i_f),
			(i_mat.m_41 / i_f), (i_mat.m_42 / i_f), (i_mat.m_43 / i_f), (i_mat.m_44 / i_f)
		);
	}

	Matrix4 operator / (const Matrix4& i_mat, const float i_f)
	{
		assert(!IsNAN(i_f));
		assert(!IsZero(i_f));
		return Matrix4( i_mat.m_11 / i_f, i_mat.m_12 / i_f, i_mat.m_13 / i_f, i_mat.m_14 / i_f,
						i_mat.m_21 / i_f, i_mat.m_22 / i_f, i_mat.m_23 / i_f, i_mat.m_24 / i_f,
						i_mat.m_31 / i_f, i_mat.m_32 / i_f, i_mat.m_33 / i_f, i_mat.m_34 / i_f,
						i_mat.m_41 / i_f, i_mat.m_42 / i_f, i_mat.m_43 / i_f, i_mat.m_44 / i_f
			);
	}

	void Multiply(const Matrix4& lhs, const Matrix4& rhs, Matrix4& Output)
	{
		//Matrix4 Output;
		
		Output.m_11 = lhs.m_11 * rhs.m_11 + lhs.m_12 * rhs.m_21 + lhs.m_13 * rhs.m_31 + lhs.m_14 * rhs.m_41;
		Output.m_12 = lhs.m_11 * rhs.m_12 + lhs.m_12 * rhs.m_22 + lhs.m_13 * rhs.m_32 + lhs.m_14 * rhs.m_42;
		Output.m_13 = lhs.m_11 * rhs.m_13 + lhs.m_12 * rhs.m_23 + lhs.m_13 * rhs.m_33 + lhs.m_14 * rhs.m_43;
		Output.m_14 = lhs.m_11 * rhs.m_14 + lhs.m_12 * rhs.m_24 + lhs.m_13 * rhs.m_34 + lhs.m_14 * rhs.m_44;

		Output.m_21 = lhs.m_21 * rhs.m_11 + lhs.m_22 * rhs.m_21 + lhs.m_23 * rhs.m_31 + lhs.m_24 * rhs.m_41;
		Output.m_22 = lhs.m_21 * rhs.m_12 + lhs.m_22 * rhs.m_22 + lhs.m_23 * rhs.m_32 + lhs.m_24 * rhs.m_42;
		Output.m_23 = lhs.m_21 * rhs.m_13 + lhs.m_22 * rhs.m_23 + lhs.m_23 * rhs.m_33 + lhs.m_24 * rhs.m_43;
		Output.m_24 = lhs.m_21 * rhs.m_14 + lhs.m_22 * rhs.m_24 + lhs.m_23 * rhs.m_34 + lhs.m_24 * rhs.m_44;

		Output.m_31 = lhs.m_31 * rhs.m_11 + lhs.m_32 * rhs.m_21 + lhs.m_33 * rhs.m_31 + lhs.m_34 * rhs.m_41;
		Output.m_32 = lhs.m_31 * rhs.m_12 + lhs.m_32 * rhs.m_22 + lhs.m_33 * rhs.m_32 + lhs.m_34 * rhs.m_42;
		Output.m_33 = lhs.m_31 * rhs.m_13 + lhs.m_32 * rhs.m_23 + lhs.m_33 * rhs.m_33 + lhs.m_34 * rhs.m_43;
		Output.m_34 = lhs.m_31 * rhs.m_14 + lhs.m_32 * rhs.m_24 + lhs.m_33 * rhs.m_34 + lhs.m_34 * rhs.m_44;

		Output.m_41 = lhs.m_41 * rhs.m_11 + lhs.m_42 * rhs.m_21 + lhs.m_43 * rhs.m_31 + lhs.m_44 * rhs.m_41;
		Output.m_42 = lhs.m_41 * rhs.m_12 + lhs.m_42 * rhs.m_22 + lhs.m_43 * rhs.m_32 + lhs.m_44 * rhs.m_42;
		Output.m_43 = lhs.m_41 * rhs.m_13 + lhs.m_42 * rhs.m_23 + lhs.m_43 * rhs.m_33 + lhs.m_44 * rhs.m_43;
		Output.m_44 = lhs.m_41 * rhs.m_14 + lhs.m_42 * rhs.m_24 + lhs.m_43 * rhs.m_34 + lhs.m_44 * rhs.m_44;

		//return Output;
	}

	/* For multiplying M x V
		|m, m, m, m|	|v|	
		|m, m, m, m| \/ |v| 
		|m, m, m, m| /\ |v|
		|m, m, m, m|	|v|
	*/
	point4d operator*(const Matrix4& i_mat, const point4d& i_vec)
	{
		assert(!IsNAN(i_mat.m_11));
		float x = (i_mat.m_11 * i_vec.x) + (i_mat.m_12 * i_vec.y) + (i_mat.m_13 * i_vec.z) + (i_mat.m_14 * i_vec.w);
		float y = (i_mat.m_21 * i_vec.x) + (i_mat.m_22 * i_vec.y) + (i_mat.m_23 * i_vec.z) + (i_mat.m_24 * i_vec.w);
		float z = (i_mat.m_31 * i_vec.x) + (i_mat.m_32 * i_vec.y) + (i_mat.m_33 * i_vec.z) + (i_mat.m_34 * i_vec.w);
		float w = (i_mat.m_41 * i_vec.x) + (i_mat.m_42 * i_vec.y) + (i_mat.m_43 * i_vec.z) + (i_mat.m_44 * i_vec.w);
		return point4d(x, y, z, w);
	}

	/* For multiplying M x V
						|m, m, m, m|	
					 \/	|m, m, m, m| 
					 /\	|m, m, m, m|
		|v, v, v, v|	|m, m, m, m|	
	*/
	point4d operator*(const point4d& i_vec, const Matrix4& i_mat)
	{
		assert(!IsNAN(i_mat.m_11));

		return point4d(
			(i_vec.x * i_mat.m_11) + (i_vec.y * i_mat.m_21) + (i_vec.z * i_mat.m_31) + (i_vec.w * i_mat.m_41),
			(i_vec.x * i_mat.m_12) + (i_vec.y * i_mat.m_22) + (i_vec.z * i_mat.m_32) + (i_vec.w * i_mat.m_42),
			(i_vec.x * i_mat.m_13) + (i_vec.y * i_mat.m_23) + (i_vec.z * i_mat.m_33) + (i_vec.w * i_mat.m_43),
			(i_vec.x * i_mat.m_14) + (i_vec.y * i_mat.m_24) + (i_vec.z * i_mat.m_34) + (i_vec.w * i_mat.m_44)
			);
	}

	bool operator == (const Matrix4& lhs, const Matrix4& rhs)
	{
		bool Row1 = AreEqualInRange(lhs.m_11, rhs.m_11, 0.001f) && AreEqualInRange(lhs.m_12, rhs.m_12, 0.001f) && AreEqualInRange(lhs.m_13, rhs.m_13, 0.001f) && AreEqualInRange(lhs.m_14, rhs.m_14, 0.001f);
		bool Row2 = AreEqualInRange(lhs.m_21, rhs.m_21, 0.001f) && AreEqualInRange(lhs.m_22, rhs.m_22, 0.001f) && AreEqualInRange(lhs.m_23, rhs.m_23, 0.001f) && AreEqualInRange(lhs.m_24, rhs.m_24, 0.001f);
		bool Row3 = AreEqualInRange(lhs.m_31, rhs.m_31, 0.001f) && AreEqualInRange(lhs.m_32, rhs.m_32, 0.001f) && AreEqualInRange(lhs.m_33, rhs.m_33, 0.001f) && AreEqualInRange(lhs.m_34, rhs.m_34, 0.001f);
		bool Row4 = AreEqualInRange(lhs.m_41, rhs.m_41, 0.001f) && AreEqualInRange(lhs.m_42, rhs.m_42, 0.001f) && AreEqualInRange(lhs.m_43, rhs.m_43, 0.001f) && AreEqualInRange(lhs.m_44, rhs.m_44, 0.001f);

		return Row1 && Row2 && Row3 && Row4;

	}

}


