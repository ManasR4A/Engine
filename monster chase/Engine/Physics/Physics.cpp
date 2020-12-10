#include "Physics.h"
#include "stdio.h"

namespace Engine
{
	bool PhysicsObject::initializePhysicsObject(const float i_Mass, const point2d& i_LastPosition, const float i_DragConstant, const point2d& i_GravityForce, const point2d& i_OtherForces, Engine::SmartPointer<GameObject>& i_GO)
	{
		// setting values
		this->Mass = i_Mass;
		this->LastPosition = i_LastPosition;
		this->DragConstant = i_DragConstant;
		this->GravityForce = i_GravityForce;
		this->OtherForces = i_OtherForces;
		this->GO = i_GO;
		this->IsLegel = true;

		// Adding the instance to the PHO_List in Physics System
		//Engine::PhysicsSystem::AddPhysicsObject(Engine::SmartPointer<PhysicsObject>(this));

		return true;
	}

	bool PhysicsObject::UpdateObject(float i_deltaT)
	{
		// Get FrameTime or deltaT
		float deltaT = i_deltaT;
		auto SmartGO = GO.GetSmartPointer();
		// Do numerical integration to calculate the new position of the owning object using current members
		// USING VERLET METHOD
		point2d					NewPosition;
		point2d					CurrentVelocity;
		point2d					CumulativeForce;
		point2d					DragForce;

		CurrentVelocity = SmartGO->Location - this->LastPosition;

		//if (AreEqualInRange(CurrentVelocity.x, 0.f, 0.01f))
		//	CurrentVelocity.x = 0;
		//if (AreEqualInRange(CurrentVelocity.y, 0.f, 0.01f))
		//	CurrentVelocity.y = 0;

		// check condition for terminal velocity
		if (CurrentVelocity.Magnetude() >= const_cast<point2d&>(PhysicsObject::TERMINAL_VELOCITY).Magnetude())
			CurrentVelocity = PhysicsObject::TERMINAL_VELOCITY;

		SmartGO->SetVelocity(CurrentVelocity);

		DragForce = CurrentVelocity * this->DragConstant;

		CumulativeForce = this->GravityForce + this->OtherForces - DragForce;

		NewPosition = SmartGO->Location + (CurrentVelocity + ((CumulativeForce / this->Mass) * deltaT * .5f));

		// update the LastPosition member
		this->LastPosition = SmartGO->Location;

		// transmit the new position info
		SmartGO->Location = NewPosition;

		SmartGO = nullptr;

		return true;
	}

	bool PhysicsObject::Release()
	{
		assert(GO);
		GO = nullptr;
		return true;
	}


	void PhysicsSystem::InitializePhysicsSystem()
	{
		PHO_Objects.clear();
		PHO_Objects.shrink_to_fit();
	}

	void PhysicsSystem::AddPhysicsObject(SmartPointer<PhysicsObject>& i_PHO)
	{
		assert(i_PHO);
		PHO_Objects.push_back(i_PHO);
	}

	bool PhysicsSystem::RemovePhysicsObject(SmartPointer<PhysicsObject>& i_PHO)
	{
		assert(i_PHO);
		size_t count = PHO_Objects.size();

		assert(count > 0);
		for (auto i = 0; i < count; i++)
		{
			if (PHO_Objects[i] == i_PHO)
			{
				auto SmartPHO = PHO_Objects[i].GetSmartPointer();
				PHO_Objects[i] = std::move(PHO_Objects.back());
				SmartPHO->Release();
				SmartPHO = nullptr;
				PHO_Objects.pop_back();
				return true;
			}
		}
		return false;
	}

	void PhysicsSystem::PhysicsTick(float deltaT)
	{
		size_t count = PHO_Objects.size();
		assert(count > 0);

		for (auto i = 0; i < count; i++)
		{
			SmartPointer<PhysicsObject> SmartPHO = PHO_Objects[i].GetSmartPointer();
			assert(SmartPHO);

			SmartPHO->UpdateObject(deltaT);
			SmartPHO = nullptr;
		}

	}

	bool PhysicsSystem::ShutDownPhysicsSystem()
	{
		bool ShutdownSuccessful = true;

		size_t count = PHO_Objects.size();

		if (count > 0)
		{
			ShutdownSuccessful = false;
			for (auto i = 0; i < count; i++)
				PHO_Objects.pop_back();
		}
		PHO_Objects.clear();
		PHO_Objects.shrink_to_fit();
		return ShutdownSuccessful;
	}
}




 