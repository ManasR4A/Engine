#pragma once
#include "Game Object/Entity.h"
#include "Containers/Poimters/SmartPointer.h"
#include "Math/MathUtils.h"
#include "Math/Vector2.h"

#include "Actor/Actor.h"

#include "../nlohmann/json.hpp"


namespace Engine
{

	

	void InitializeActorFromJSON(const std::string& i_JSONFile, Actor&);
	
}