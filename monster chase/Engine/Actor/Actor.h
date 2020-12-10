#pragma once
#include "Game Object/\Entity.h"
#include "Physics/Physics.h"
#include "Collision/Collision.h"
#include "Renderer/Render.h"
#include "Containers/Poimters/SmartPointer.h"
#include "GLib.h"

namespace Engine
{
	
	class Actor 
	{
	public:
		
		SmartPointer<GameObject> GO;
		SmartPointer<PhysicsObject> PHO;
		SmartPointer<CollisionObject> CO;
		SmartPointer<RenderObject> RO;

		Actor() :
			GO(nullptr),
			PHO(nullptr),
			CO(nullptr),
			RO(nullptr)
		{

		}

		virtual ~Actor()
		{
			if (GO)
				GO = nullptr;
			if (PHO)
				PHO = nullptr;
			if (CO)
				CO = nullptr;
			if (RO)
				RO = nullptr;
		}

	};
}
