#include "Charecters.h"

#include "conio.h"
#include "functional"
#include "iostream"

namespace Game
{
	#pragma region Player

	// player constructor
	player::player()
	{
		GO = new GameObject;
		PHO = new PhysicsObject;
		CO = new CollisionObject;
		RO = new RenderObject;
	}

	player::player(Actor i_actor)
	{
		GO = i_actor.GO;
		PHO = i_actor.PHO;
		CO = i_actor.CO;
		RO = i_actor.RO;

		// Add the reference of the PHO in the Physics System
		Engine::PhysicsSystem::AddPhysicsObject(PHO);
		if (CollisionSystem::AddCollisionObject(CO))
		{
			//DebugPrint120("\nCollision Object for player Added to update list.");
		}
	}

	void player::InitializePlayerFromJSON(const std::string& i_JSONFile)
	{
		Engine::InitializeActorFromJSON(i_JSONFile, *this);

		if(PHO)
			Engine::PhysicsSystem::AddPhysicsObject(PHO);
	
		if(CO)
			Engine::CollisionSystem::AddCollisionObject(CO);

		if (RO)
			Engine::RenderSystem::AddRenderObject(RO);
	}

	bool player::move(const point2d& i_MoveDir)
	{

		point2d ForceDir = i_MoveDir ; // ForceMultiplier

		// apply this Vector as the final force on the physics object of the entity
		this->PHO->SetOtherForces(ForceDir);


	#ifdef _DEBUG
		const size_t	lenBuffer = 65;
		char			Buffer[lenBuffer];

		sprintf_s(Buffer, lenBuffer, "Player Moved with force %f %f\n",ForceDir.x, ForceDir.y);
		OutputDebugStringA(Buffer);
	#endif // __DEBUG

		return true;

	}

	void player::CollisionResponse()
	{
		bops++;
		if (bops >= 50)
			QuitRequested = true;
	}

	bool player::RemovePlayer()
	{
		bool PHORemoved = false;
		bool CORemoved = false;
		bool RORemoved = false;

		if (GO)
		{
			GO = nullptr;
		}

		if (PHO)
		{
			PHORemoved = Engine::PhysicsSystem::RemovePhysicsObject(PHO);
			PHO = nullptr;
		}

		if (CO)
		{
			CORemoved = CollisionSystem::RemoveCollisionObject(CO);
			CO = nullptr;
		}

		if (RO)
		{
			RORemoved = RenderSystem::RemoveRenderObject(RO);
			RO = nullptr;
		}
		

		return PHORemoved && CORemoved && RORemoved;
	}



	#pragma endregion

	#pragma region Enemy

	// enemy constructor
	enemy::enemy()
	{
		GO = new GameObject;
		PHO = new PhysicsObject;
		CO = new CollisionObject;
		RO = new RenderObject;
	}

	enemy::enemy(Actor i_actor)
	{
		GO = i_actor.GO;
		PHO = i_actor.PHO;
		CO = i_actor.CO;
		RO = i_actor.RO;

		// Add the reference of the PHO in the Physics System
		Engine::PhysicsSystem::AddPhysicsObject(PHO);
		if (CollisionSystem::AddCollisionObject(CO))
			DebugPrint120("\nCollision Object for Enemy Added to update list.");

	}

	void enemy::InitializeEnemyFromJSON(const std::string& i_JSONFile)
	{
		Engine::InitializeActorFromJSON(i_JSONFile, *this);

		if(PHO)
			Engine::PhysicsSystem::AddPhysicsObject(PHO);

		if(CO)
			Engine::CollisionSystem::AddCollisionObject(CO);
	
		if (RO)
			Engine::RenderSystem::AddRenderObject(RO);
	}

	void enemy::CollisionResponse()
	{
		DebugPrint120("\nEnemy Collided.");
		AI();
	}


	void enemy::AI()
	{
		float rx = rand() % 2;
		float ry = rand() % 2;
		float x, y;
		rx = 0 ? x = rand() % 600 : x = -(rand() % 600);
		ry = 0 ? y = rand() % 300 : y = -(rand() % 300);
		point2d newLocation(x, y);
		GO->SetLocation(newLocation);
		PHO->SetLastPosition(newLocation);
	}

	bool enemy::RemoveEnemy()
	{
		bool PHORemoved = false;
		bool CORemoved = false;
		bool RORemoved = false;

		if (GO)
		{
			GO = nullptr;
		}

		if (PHO)
		{
			PHORemoved = Engine::PhysicsSystem::RemovePhysicsObject(PHO);
			PHO = nullptr;
		}

		if (CO)
		{
			CORemoved = CollisionSystem::RemoveCollisionObject(CO);
			CO = nullptr;
		}

		if (RO)
		{
			RORemoved = RenderSystem::RemoveRenderObject(RO);
			RO = nullptr;
		}

		return PHORemoved && CORemoved;
	}


	#pragma endregion
}




#pragma region Boundery
//
//Boundery::Boundery()
//{
//	m_sprite = nullptr;
//	GO = new GameObject;
//	PHO = new PhysicsObject;
//	CO = new CollisionObject;
//}
//
//Boundery::Boundery(Actor i_actor)
//{
//	GO = i_actor.GO;
//	PHO = i_actor.PHO;
//	CO = i_actor.CO;
//	m_sprite = i_actor.m_sprite;
//
//	// Add the reference of the PHO in the Physics System
//	Engine::PhysicsSystem::AddPhysicsObject(PHO);
//	if (CollisionSystem::AddCollisionObject(CO))
//	{
//		DebugPrint120("\nCollision Object for Boundery Added to update list.");
//	}
//
//}
//
//void Boundery::InitializeBounderyFromJSON(const std::string& i_JSONFile)
//{
//	Engine::InitializeActorFromJSON(i_JSONFile, *this);
//
//	if(PHO)
//		Engine::PhysicsSystem::AddPhysicsObject(PHO);
//	
//	if(CO)
//		Engine::CollisionSystem::AddCollisionObject(CO);
//}
//
//void Boundery::CollisionResponce()
//{
//	RemoveBoundery();
//}
//
//bool Boundery::RemoveBoundery()
//{
//	bool PHORemoved = false, CORemoved = false;
//
//	if (GO)
//		GO = nullptr;
//
//	if (PHO)
//	{
//		PHORemoved = Engine::PhysicsSystem::RemovePhysicsObject(PHO);
//		PHO = nullptr;
//	}
//
//	if (CO)
//	{
//		CORemoved = CollisionSystem::RemoveCollisionObject(CO);
//		CO = nullptr;
//	}
//
//	if (m_sprite)
//	{
//		GLib::Release(m_sprite);
//		m_sprite = nullptr;
//	}
//
//
//	return PHORemoved && CORemoved;
//}
//

#pragma endregion