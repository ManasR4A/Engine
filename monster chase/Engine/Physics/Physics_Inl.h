#pragma once

#include "assert.h"

namespace Engine
{
	inline float PhysicsObject::GetMass() const
	{
		return this->Mass;
	}

	inline void PhysicsObject::SetMass(const float i_Mass)
	{
		assert(i_Mass);
		PhysicsObject::Mass = i_Mass;
	}

	inline point2d PhysicsObject::GetLastPosition() const
	{
		return PhysicsObject::LastPosition;
	}

	inline void PhysicsObject::SetLastPosition(const point2d& i_LastPosition)
	{
		if (i_LastPosition != point2d())
			PhysicsObject::LastPosition = i_LastPosition;
	}

	inline float PhysicsObject::GetDragConstant() const
	{
		return PhysicsObject::DragConstant;
	}

	inline void PhysicsObject::SetDragConstant(const float i_DragConstant)
	{
		PhysicsObject::DragConstant = i_DragConstant;
	}

	inline point2d PhysicsObject::GetGravityForce() const
	{
		return PhysicsObject::GravityForce;
	}

	inline void PhysicsObject::SetGravityForce(const point2d& i_GravityForce)
	{
		if (i_GravityForce != point2d())
			PhysicsObject::GravityForce = i_GravityForce;
	}

	inline point2d PhysicsObject::GetOtherForces() const
	{
		return PhysicsObject::OtherForces;
	}

	inline void PhysicsObject::SetOtherForces(const point2d& i_OtherForces)
	{
		//if(i_OtherForces != point2d())
		this->OtherForces = i_OtherForces;
	}

}





