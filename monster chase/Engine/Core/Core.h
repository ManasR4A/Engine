#pragma once
#include "PlayerController.h"
#include "Utils/Utils.h"
#include "Timer/Timer.h"

#include "Renderer/Render.h"

#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"
#include "Math/Matrix4.h"
#include "Math/MathUtils.h"

#include "Containers/List/List.h"
#include "LibOverloads/Overloads.h"
#include "Actor/Actor.h"
#include "Game Object/ObjectFactory.h"

#include "SFML/Graphics.hpp"


namespace Engine
{

#define _USE_CUSTOM_HEAP_MANAGER

	// timer for the engine
	static Timer * T;
	//static SmartPointer<Timer> T;

	// tick time
	static float deltaT = 0;

	// Initialize all the Systems.
	bool Initialize(bool i_bCustomHeapManager = false);

	// Execute the Tick functions of all the Systems.
	void Tick();

	// ShutDown all the Systems.
	bool ShutDown();
}

using namespace Engine;