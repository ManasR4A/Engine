#pragma once
#include "Math/vector2.h"

namespace Engine
{
	class GameObject
	{
	public:

		// constructors
		GameObject() :
			Location(point2d()),
			Velocity(point2d()),
			Heading(0)
		{
		}

		GameObject(const point2d i_Location, const point2d i_Velocity, const float i_Heading) :
			Location(i_Location),
			Velocity(i_Velocity),
			Heading(i_Heading)
		{
		}


		// Getters and Setters
		inline point2d GetLocation() const
		{
			return this->Location;
		}

		inline float GetLocation_X() const
		{
			return Location.x;
		}

		inline float GetLocation_Y() const
		{
			return Location.y;
		}

		inline point2d GetVelocity() const
		{
			return Velocity;
		}

		inline void SetVelocity(const point2d i_Velocity)
		{
			Velocity = i_Velocity;
		}

		inline float GetHeading() const
		{
			return Heading;
		}

		inline void SetLocation(const point2d i_Location)
		{
			this->Location.x = i_Location.x;
			this->Location.y = i_Location.y;
		}

		inline void SetHeading(const float i_Heading)
		{
			Heading = i_Heading;
		}

		//virtual ~GameObject()
		//{
		//	// If the inheritor wants, they can override the destructor
		//}


		point2d					Location;
		point2d					Velocity;
		float					Heading;
	};

	// Interface class to controll the movement of the GameObject
	class MovementController
	{
	public:
		virtual bool move() = delete;
		virtual bool move(const point2d& i_MoveDir) = 0;
		virtual ~MovementController()
		{
			// Not going to be overridden, but can be by the inheritor
		}
	};
}


