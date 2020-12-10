#pragma once
#include "Core/Core.h"
#include "Containers/Poimters/SmartPointer.h"


//class Boundery : public Actor
//{
//public:
//	Boundery();
//	Boundery(Actor i_actor);
//
//	void InitializeBounderyFromJSON(const std::string& i_JSONFile);
//
//	void CollisionResponce();
//
//	bool RemoveBoundery();
//
//};

namespace Game
{
	class player : public Engine::Actor
	{


	public:
		// constructor
		player();
		player(Actor i_actor);

		void InitializePlayerFromJSON(const std::string& i_JSONFile);

		void CollisionResponse();

		// Move function override
		bool move(const point2d& i_MoveDir);

		// to perform some functions on the player before we delete.
		bool RemovePlayer();

		bool QuitRequested = false;
		int bops = 0;

	};

	class enemy : public Engine::Actor
	{
	public:
		// constructor
		enemy();
		enemy(Actor i_actor);

		void InitializeEnemyFromJSON(const std::string& i_JSONFile);

		void CollisionResponse();

		void AI();

		// to perform some functions on the player before we delete.
		bool RemoveEnemy();

	};
}

