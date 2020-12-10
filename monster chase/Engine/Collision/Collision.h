#pragma once
#include"Math/Vector2.h"
#include"Math/Vector3.h"
#include "Math/Matrix3.h"
#include "Math/Matrix4.h"
#include "Utils/Utils.h"
#include "Containers/Poimters/SmartPointer.h"
#include "Game Object/Entity.h"


#include "vector"
#include <functional>

namespace Engine
{

	struct AABB
	{
		point3d Center;
		point3d Extents;
	};

	struct CollisionData
	{
		SmartPointer<GameObject> SmartGO;
		Matrix4 mObjectToWorld;
		Matrix3 mOrientationInWorld;
		point3d BBCenterInWorld;
	};

	struct CollisionObject
	{
	public:
		WeakPointer<GameObject> GO;
		AABB BoundingBox;
		CollisionData GeneratedCollisionData;
		std::function<void()> CollisionCallback;

		inline void SetCollisionCallback(std::function<void()>& i_funct)
		{
			CollisionCallback = i_funct;
		}

	};

	struct CollisionPair
	{
		WeakPointer<CollisionObject> Collidables[2];
		float TimeOfCollision = 1.f;
	};

	namespace CollisionSystem
	{

		static bool CollisionDetectedThisFrame = false;

		// The std::vector of all CO's that need to be updated and checked each frame.
		static std::vector<WeakPointer<CollisionObject>> AllCollisionObjects;

		// Initializes the Collision System
		bool Initialize();

		/** Adds the Collision Object to the update list
		* @param	Smart POinter Reference to the game object
		*/
		bool AddCollisionObject(SmartPointer<CollisionObject>& i_CO);

		/** Removes the Collision Object to the update list
		* @param	Smart POinter Reference to the game object
		*/
		bool RemoveCollisionObject(SmartPointer<CollisionObject>& i_CO);

		/** Checks for any possible collissions in the CO's in the list
		* @param	Frame Time
		* @returns	True if detected any collision.
		*/
		bool CheckForCollisions(float i_deltaTime);

		/** Generates the Collision Data for all the CO's in the update list.
		*	To be called by CheckForCollisions() as soon as it enters. 
		*/
		void GenerateCollisionData();

		/** Checks for all the possible combinations of CO's in the update list and returns if there is any collisions.
		* @param	FrameTime
		* @param	A reference to the CollisionPair struct to store the colliding CO's
		* @returns	True if any collision was detected.
		*/
		bool FindAnyCollision(float i_deltaTime, CollisionPair& o_CollidingPair);

		/** Checks if the given CO's are colliding.
		* @param	Reference to First CO
		* @param	Reference to Second CO
		* @param	Frame Time
		* @param	Reference to a float to store the time if intra-frame collision was detected
		* @returns	True if there was a collision detected between these two objects.
		*/
		bool CheckIfColliding(WeakPointer<CollisionObject>& i_Object1, WeakPointer<CollisionObject>& i_Object2, float i_deltaTime, float& o_TimeOfCollision);

		/** Detects if there was 
		*/
		bool DetectOverlapTimeOnAxis(float i_Center, float i_Extent, float i_PointOnAxis, float i_DistanceOnAxis, float& o_OverlapStartTime, float& o_OverlapEndTime);

		void Tick(float i_deltaTime);

		bool Shutdown();
	}


}