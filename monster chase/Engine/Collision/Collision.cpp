#include "Collision.h"
#include "Containers/Poimters/SmartPointer.h"

namespace Engine
{
	bool CollisionSystem::Initialize()
	{
		AllCollisionObjects.clear();
		AllCollisionObjects.shrink_to_fit();
		return true;
	}

	bool CollisionSystem::AddCollisionObject(SmartPointer<CollisionObject>& i_CO)
	{
		assert(i_CO);
		AllCollisionObjects.push_back(i_CO);
		return true;
	}

	bool CollisionSystem::RemoveCollisionObject(SmartPointer<CollisionObject>& i_CO)
	{
		size_t count = AllCollisionObjects.size();
		assert(count > 0);
		
		for (size_t i = 0; i < count; i++)
		{
			if (AllCollisionObjects[i] == i_CO)
			{
				AllCollisionObjects[i] = std::move(AllCollisionObjects.back());
				AllCollisionObjects.pop_back();
				return true;
			}
		}

		return false;
	}

	bool CollisionSystem::CheckForCollisions(float i_deltaTime)
	{
		bool CollisionDetected = false;

		GenerateCollisionData();
		CollisionPair PairOfCollidingObjects;

		if (FindAnyCollision(i_deltaTime, PairOfCollidingObjects))
		{
			assert(PairOfCollidingObjects.Collidables[0]);
			assert(PairOfCollidingObjects.Collidables[1]);

			SmartPointer<CollisionObject> SmartCO1 = PairOfCollidingObjects.Collidables[0].GetSmartPointer();
			SmartPointer<CollisionObject> SmartCO2 = PairOfCollidingObjects.Collidables[1].GetSmartPointer();
			
			if (SmartCO1->CollisionCallback)
			{
				auto SmartGO = SmartCO2->GO.GetSmartPointer();
				DebugPrint120("\nCollisionDetected");
				SmartCO1->CollisionCallback();
			}
			
			if (SmartCO2->CollisionCallback)
			{
				auto SmartGO = SmartCO1->GO.GetSmartPointer();
				DebugPrint120("\nSameCollisionDetected");
				SmartCO2->CollisionCallback();
			}


			CollisionDetected = true;
		}

		for (auto& CO : AllCollisionObjects)
		{
			SmartPointer<CollisionObject> SmartCO = CO.GetSmartPointer();
			SmartCO->GeneratedCollisionData.SmartGO = nullptr;
		}

		return CollisionDetected;
	}

	void CollisionSystem::GenerateCollisionData()
	{
		size_t count = AllCollisionObjects.size();

		for (size_t i = 0; i < count; i++)
		{
			SmartPointer<CollisionObject> LocalSmartCO = AllCollisionObjects[i].GetSmartPointer();;

			LocalSmartCO->GeneratedCollisionData.SmartGO = LocalSmartCO->GO;

			if (LocalSmartCO->GeneratedCollisionData.SmartGO) // If we get a valid Smart POinter
			{
				LocalSmartCO->GeneratedCollisionData.mOrientationInWorld = Matrix3::CV_CreateZRotationMat(LocalSmartCO->GeneratedCollisionData.SmartGO->GetHeading());
				Multiply(Matrix4::CV_CreateTranslationMat(point3d(LocalSmartCO->GeneratedCollisionData.SmartGO->GetLocation(), 0.f)), Matrix4::CV_CreateZRotationMat(LocalSmartCO->GeneratedCollisionData.SmartGO->GetHeading()), LocalSmartCO->GeneratedCollisionData.mObjectToWorld);
				LocalSmartCO->GeneratedCollisionData.BBCenterInWorld = LocalSmartCO->GeneratedCollisionData.mObjectToWorld.TransformPointCV(LocalSmartCO->BoundingBox.Center);
			}
			else
			{
				if (i < (count - 1))
					AllCollisionObjects[i] = std::move(AllCollisionObjects.back());

				AllCollisionObjects.pop_back();
				count--;
				--i; // go back to the new ith index
			}
			LocalSmartCO = nullptr;
		}

		assert(count == AllCollisionObjects.size());
	}

	bool CollisionSystem::FindAnyCollision(float i_deltaTime, CollisionPair& o_CollidingPair)
	{
		bool CollisionDetected = false;

		size_t count = AllCollisionObjects.size();

		if (count > 1)
		{
			for (size_t i = 0; i < (count - 1); i++)
			{
				for (size_t j = i + 1; j < count; j++)
				{
					float TimeOfCollision = 0.f;

					if (CheckIfColliding(AllCollisionObjects[i], AllCollisionObjects[j], i_deltaTime, TimeOfCollision))
					{
						// Checks if there was a collision and if it was intra-frame
						if (!CollisionDetected || (CollisionDetected && TimeOfCollision < o_CollidingPair.TimeOfCollision))
						{
							o_CollidingPair.Collidables[0] = AllCollisionObjects[i];
							o_CollidingPair.Collidables[1] = AllCollisionObjects[j];
							o_CollidingPair.TimeOfCollision = TimeOfCollision;
							CollisionDetected = true;
						}
					}
				}
			}
		}

		return CollisionDetected;
	}

	bool CollisionSystem::DetectOverlapTimeOnAxis(float i_Center, float i_Extent, float i_PointOnAxis, float i_DistanceOnAxis, float& o_OverlapStart, float& o_OverlapEnd)
	{
		assert(i_Extent > 0.f);

		// getting the 
		float BBOnAixStart = i_Center - i_Extent;
		float BBOnAixsEnd = i_Center + i_Extent;

		// Checking if the Distance is zero or not.
		if (IsZero(i_DistanceOnAxis))
		{
			if ((i_PointOnAxis < BBOnAixStart) || (i_PointOnAxis > BBOnAixsEnd)) // This checks if there is any preexisting plane or not
				return false;
			else
			{
				o_OverlapStart = 0.0f;
				o_OverlapEnd = 1.0f;
				return true;
			}
		}

		// Calculating the overlap times based on D(overlap). This is used to see if there was any intra-frame collision
		o_OverlapStart = (BBOnAixStart - i_PointOnAxis) / i_DistanceOnAxis;
		o_OverlapEnd = (BBOnAixsEnd - i_PointOnAxis) / i_DistanceOnAxis;

		// This will handle the oriantation dependency
		if (o_OverlapStart > o_OverlapEnd)
			Swap(o_OverlapStart, o_OverlapEnd);

		return !((o_OverlapStart >= 1.0f) || (o_OverlapEnd <= 0.0f));
	}

	bool CollisionSystem::CheckIfColliding(WeakPointer<CollisionObject>& i_Object1, WeakPointer<CollisionObject>& i_Object2, float i_deltaTime, float& o_TimeOfCollision)
	{
		// making Local references
		SmartPointer<CollisionObject> SmartObject1 = i_Object1.GetSmartPointer();
		SmartPointer<CollisionObject> SmartObject2 = i_Object2.GetSmartPointer();
		SmartPointer<GameObject>& SmartGO1 = SmartObject1->GeneratedCollisionData.SmartGO;
		SmartPointer<GameObject>& SmartGO2 = SmartObject2->GeneratedCollisionData.SmartGO;
		const CollisionData& CollisionData1 = SmartObject1->GeneratedCollisionData;
		const CollisionData& CollisionData2 = SmartObject2->GeneratedCollisionData;

		float tEnter = 0.0f;
		float tExit = 1.0f;

		// For collision check of Object 2 in Object 1's reference
		point2d Object2_RelVel = SmartObject2->GeneratedCollisionData.SmartGO->GetVelocity() - SmartObject1->GeneratedCollisionData.SmartGO->GetVelocity();
		point3d Obj2Travel = point3d(Object2_RelVel * i_deltaTime, 0.f);

		// Compare with X Axis
		{
			point3d Object1_XAxisInWorld = CollisionData1.mOrientationInWorld.Col(0).Normalize();

			// getting the BB centers for both the GOs in Object1's coordinate System
			float Object1_BBCenterOnAxis = dot(CollisionData1.BBCenterInWorld, Object1_XAxisInWorld);
			float Object2_BBCenterOnAxis = dot(CollisionData2.BBCenterInWorld, Object1_XAxisInWorld);

			// Getting the projected extents of Object 2 on Object 1's X axis
			float Object2_ProjectedX_Extents =
				fabs(dot(Object1_XAxisInWorld, CollisionData2.mOrientationInWorld.Col(0).Normalize() * SmartObject2->BoundingBox.Extents.x)) +
				fabs(dot(Object1_XAxisInWorld, CollisionData2.mOrientationInWorld.Col(1).Normalize() * SmartObject2->BoundingBox.Extents.y)) +
				fabs(dot(Object1_XAxisInWorld, CollisionData2.mOrientationInWorld.Col(2).Normalize() * SmartObject2->BoundingBox.Extents.z));

			// This makes the Object 1 into a bigget collidable and Object 2 into a single point
			float Object1_ExpandedExtents = SmartObject1->BoundingBox.Extents.x + Object2_ProjectedX_Extents;

			float Object2_DistanceAlongAxis = dot(Obj2Travel, Object1_XAxisInWorld);

			float axisEnter = 0.0f;
			float axisExit = 1.0f;

			// If this condition is satisfied ie, the Objects collided in axis either before the frame or will collide after the frame.
			// Thus there is a seperation along this axis. 
			if (!DetectOverlapTimeOnAxis(Object1_BBCenterOnAxis, Object1_ExpandedExtents, Object2_BBCenterOnAxis, Object2_DistanceAlongAxis, axisEnter, axisExit))
				return false;

			// Resetting the First Collision Start time
			if (axisEnter > tEnter)
				tEnter = axisEnter;

			// Resetting the Last Collision End time
			if (axisExit < tExit)
				tExit = axisExit;
		}

		// Compare with Y Axis
		{
			point3d Object1_YAxisInWorld = CollisionData1.mOrientationInWorld.Col(1).Normalize();

			// getting the BB centers for both the GOs in Object1's coordinate System
			float Object1_BBCenterOnAxis = dot(CollisionData1.BBCenterInWorld, Object1_YAxisInWorld);
			float Object2_BBCenterOnAxis = dot(CollisionData2.BBCenterInWorld, Object1_YAxisInWorld);

			// Getting the projected extents of Object 2 on Object 1's Y axis
			float Object2_ProjectedY_Extents =
				fabs(dot(Object1_YAxisInWorld, CollisionData2.mOrientationInWorld.Col(0).Normalize() * SmartObject2->BoundingBox.Extents.x)) +
				fabs(dot(Object1_YAxisInWorld, CollisionData2.mOrientationInWorld.Col(1).Normalize() * SmartObject2->BoundingBox.Extents.y)) +
				fabs(dot(Object1_YAxisInWorld, CollisionData2.mOrientationInWorld.Col(2).Normalize() * SmartObject2->BoundingBox.Extents.z));

			// This makes the Object 1 into a bigget collidable and Object 2 into a single point
			float Object1_ExpandedExtents = SmartObject1->BoundingBox.Extents.y + Object2_ProjectedY_Extents;

			float Object2_DistanceAlongAxis = dot(Obj2Travel, Object1_YAxisInWorld);

			float axisEnter = 0.0f;
			float axisExit = 1.0f;

			// If this condition is satisfied ie, the Objects collided in axis either before the frame or will collide after the frame.
			// Thus there is a seperation along this axis. 
			if (!DetectOverlapTimeOnAxis(Object1_BBCenterOnAxis, Object1_ExpandedExtents, Object2_BBCenterOnAxis, Object2_DistanceAlongAxis, axisEnter, axisExit))
				return false;

			// Resetting the First Collision Start time
			if (axisEnter > tEnter)
				tEnter = axisEnter;

			// Resetting the Last Collision End time
			if (axisExit < tExit)
				tExit = axisExit;
		}



		// For collision check of Object 1 in Object 2's reference
		point2d Object1_RelVel = SmartObject1->GeneratedCollisionData.SmartGO->GetVelocity() - SmartObject2->GeneratedCollisionData.SmartGO->GetVelocity();
		point3d Obj1Travel = point3d(Object1_RelVel * i_deltaTime, 0.f);

		// Compare with X Axis
		{
			point3d Object2_XAxisInWorld = CollisionData2.mOrientationInWorld.Col(0).Normalize();

			// getting the BB centers for both the GOs in Object 2's coordinate System
			float Object1_BBCenterOnAxis = dot(CollisionData1.BBCenterInWorld, Object2_XAxisInWorld);
			float Object2_BBCenterOnAxis = dot(CollisionData2.BBCenterInWorld, Object2_XAxisInWorld);

			// Getting the projected extents of Object 1 on Object 2's X axis
			float Object1_ProjectedX_Extents =
				fabs(dot(Object2_XAxisInWorld, CollisionData1.mOrientationInWorld.Col(0).Normalize() * SmartObject1->BoundingBox.Extents.x)) +
				fabs(dot(Object2_XAxisInWorld, CollisionData1.mOrientationInWorld.Col(1).Normalize() * SmartObject1->BoundingBox.Extents.y)) +
				fabs(dot(Object2_XAxisInWorld, CollisionData1.mOrientationInWorld.Col(2).Normalize() * SmartObject1->BoundingBox.Extents.z));

			// This makes the Object 2 into a bigger stationary collidable and Object 1 into a single point
			float Object2_ExpandedExtents = SmartObject2->BoundingBox.Extents.x + Object1_ProjectedX_Extents;

			float Object1_DistanceAlongAxis = dot(Obj1Travel, Object2_XAxisInWorld);

			float axisEnter = 0.0f;
			float axisExit = 1.0f;

			// If this condition is satisfied ie, the Objects collided in axis either before the frame or will collide after the frame.
			// Thus there is a seperation along this axis. 
			if (!DetectOverlapTimeOnAxis(Object2_BBCenterOnAxis, Object2_ExpandedExtents, Object1_BBCenterOnAxis, Object1_DistanceAlongAxis, axisEnter, axisExit))
				return false;

			// Resetting the First Collision Start time
			if (axisEnter > tEnter)
				tEnter = axisEnter;

			// Resetting the Last Collision End time
			if (axisExit < tExit)
				tExit = axisExit;
		}

		// Compare with Y Axis
		{
			point3d Object2_YAxisInWorld = CollisionData2.mOrientationInWorld.Col(1).Normalize();

			// getting the BB centers for both the GOs in Object1's coordinate System
			float Object1_BBCenterOnAxis = dot(CollisionData1.BBCenterInWorld, Object2_YAxisInWorld);
			float Object2_BBCenterOnAxis = dot(CollisionData2.BBCenterInWorld, Object2_YAxisInWorld);

			// Getting the projected extents of Object 2 on Object 1's Y axis
			float Object1_ProjectedY_Extents =
				fabs(dot(Object2_YAxisInWorld, CollisionData1.mOrientationInWorld.Col(0).Normalize() * SmartObject1->BoundingBox.Extents.x)) +
				fabs(dot(Object2_YAxisInWorld, CollisionData1.mOrientationInWorld.Col(1).Normalize() * SmartObject1->BoundingBox.Extents.y)) +
				fabs(dot(Object2_YAxisInWorld, CollisionData1.mOrientationInWorld.Col(2).Normalize() * SmartObject1->BoundingBox.Extents.z));

			// This makes the Object 1 into a bigger stationary collidable and Object 2 into a single point
			float Object2_ExpandedExtents = SmartObject2->BoundingBox.Extents.y + Object1_ProjectedY_Extents;

			float Object1_DistanceAlongAxis = dot(Obj1Travel, Object2_YAxisInWorld);

			float axisEnter = 0.0f;
			float axisExit = 1.0f;

			// If this condition is satisfied ie, the Objects collided in axis either before the frame or will collide after the frame.
			// Thus there is a seperation along this axis. 
			if (!DetectOverlapTimeOnAxis(Object2_BBCenterOnAxis, Object2_ExpandedExtents, Object1_BBCenterOnAxis, Object1_DistanceAlongAxis, axisEnter, axisExit))
				return false;

			// Resetting the First Collision Start time
			if (axisEnter > tEnter)
				tEnter = axisEnter;

			// Resetting the Last Collision End time
			if (axisExit < tExit)
				tExit = axisExit;
		}

		// returns if tere was any collision detected or not. If there was an intra- frame collision, also sets the o_TimeofCollision to the timeset.
		o_TimeOfCollision = tEnter;
		return tEnter < tExit;
	}


	void CollisionSystem::Tick(float i_deltaTime)
	{
		CollisionDetectedThisFrame = CheckForCollisions(i_deltaTime);
	}

	bool CollisionSystem::Shutdown()
	{
		bool SuccessfulShutDown = true;

		size_t count = AllCollisionObjects.size();
		if (count > 0)
		{
			SuccessfulShutDown = false;
			for (size_t i = 0; i < count; i++)
			{
				AllCollisionObjects.pop_back();
			}
		}

		AllCollisionObjects.clear();
		AllCollisionObjects.shrink_to_fit();
		return SuccessfulShutDown;

	}


}


