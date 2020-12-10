#pragma once
#include "Math/Vector2.h"
#include "Game Object/Entity.h"
#include "Containers/Poimters/SmartPointer.h"
#include "Utils/Utils.h"

#include "vector"

namespace Engine
{
	class PhysicsObject
	{
	public:
		// constructors
		PhysicsObject() : Mass(0),
			LastPosition(point2d()), // Calling default constructor of point2d class
			DragConstant(0),
			GravityForce(point2d()),
			OtherForces(point2d()),
			GO(Engine::WeakPointer<GameObject>()),
			TERMINAL_VELOCITY(point2d(1024.0f, 1024.0f)),
			IsLegel(false)
		{
		}

		bool initializePhysicsObject(const float i_Mass, const point2d& i_LastPosition, const float i_DragConstant, const point2d& i_GravityForce, const point2d& i_OtherForces, Engine::SmartPointer<GameObject>& i_GO);

		// Getters and Setters
		inline float GetMass() const;
		inline void SetMass(const float i_Mass);

		inline point2d GetLastPosition() const;
		inline void SetLastPosition(const point2d& i_LastPosition);

		inline float GetDragConstant()const;
		inline void SetDragConstant(const float i_DragConstant);

		inline point2d GetGravityForce() const;
		inline void SetGravityForce(const point2d& i_GravityForce);

		inline point2d GetOtherForces() const;
		inline void SetOtherForces(const point2d& i_OtherForces);

		// Update function for the physics object
		bool UpdateObject(float deltaT);

		bool Release();

	private:
		WeakPointer<GameObject> GO;
		float Mass;
		point2d LastPosition;
		float DragConstant;
		point2d GravityForce;
		point2d OtherForces;
		const point2d TERMINAL_VELOCITY;
		bool IsLegel : 1;
	};

	namespace PhysicsSystem
	{
		static size_t PHO_Count;

		static std::vector<WeakPointer<PhysicsObject>> PHO_Objects;

		/*Initializes the Physics System.*/
		void InitializePhysicsSystem();

		/*Adds the reference to the Physics object at the end of the list of Objects that have physics.*/
		void AddPhysicsObject(SmartPointer<PhysicsObject>& i_PHO);

		/*Removes the Specified Physics object from the list of PHOs to be updated every frame.*/
		bool RemovePhysicsObject(SmartPointer<PhysicsObject>& i_PHO);

		/*Updates the list of PHOs every frame. Called by Engine::Tick()*/
		void PhysicsTick(float deltaT);

		/*Shuts down the Physics System. Returns true if everything was fine. Returns False if any PHOs were still being updated.*/
		bool ShutDownPhysicsSystem();
	}
}


#include "Physics_Inl.h"
