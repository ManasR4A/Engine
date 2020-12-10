#include "Game Object/ObjectFactory.h"
#include "../Physics/Physics.h"
#include "LibOverloads/Overloads.h"


namespace Engine
{

	// From Sample to load json data
	std::vector<uint8_t> LoadJSONFile(const std::string& i_Name)
	{
		std::vector<uint8_t> Contents;

		if (!i_Name.empty())
		{
			FILE* pFile = nullptr;

			errno_t fopenError = fopen_s(&pFile, i_Name.c_str(), "rb");
			if (fopenError == 0)
			{
				assert(pFile != nullptr);

				int FileIOError = fseek(pFile, 0, SEEK_END);
				assert(FileIOError == 0);

				long FileSize = ftell(pFile);
				assert(FileSize >= 0);

				FileIOError = fseek(pFile, 0, SEEK_SET);
				assert(FileIOError == 0);

				Contents.reserve(FileSize);
				Contents.resize(FileSize);

				size_t FileRead = fread(&Contents[0], 1, FileSize, pFile);
				assert(FileRead == FileSize);

				fclose(pFile);
			}
		}

		return Contents;
	}

	void InitializeActorFromJSON(const std::string& i_JSONFile, Actor& o_ActorToCreate)
	{
		// load the file in
		std::vector<uint8_t> FileContent = LoadJSONFile(i_JSONFile);

		// Check to see if the file is not empty
		if (!FileContent.empty())
		{
			nlohmann::json Data = nlohmann::json::parse(FileContent);
			
			if (Data.contains("GameObject"))
			{
				// Fetch data
				point2d InitialLocation(Data["GameObject"]["Initial Location"][0], Data["GameObject"]["Initial Location"][1]);

				// Initialize the GameObject at the initial Location
				*o_ActorToCreate.GO = GameObject(InitialLocation, point2d(0.f, 0.f), 0.f);
			}
			else
				o_ActorToCreate.GO = nullptr;

			if (Data.contains("PhysicsObject"))
			{

				// fetch data
				float Mass = Data["PhysicsObject"]["Mass"];
				float DragConstant = Data["PhysicsObject"]["DragConstant"];
				point2d OtherForces(Data["PhysicsObject"]["OtherForces"][0], Data["PhysicsObject"]["OtherForces"][1]);
				point2d LastPosition = o_ActorToCreate.GO->GetLocation();
				point2d GravityInput(Data["PhysicsObject"]["Gravity"][0], Data["PhysicsObject"]["Gravity"][1]);
				point2d Gravity = GravityInput * Mass;

				// initialize the Physics Object
				o_ActorToCreate.PHO->initializePhysicsObject(Mass, LastPosition, DragConstant, Gravity, OtherForces, o_ActorToCreate.GO);
				DebugPrint120("PhysicsObject Created.\n");
			}
			else
				o_ActorToCreate.PHO = nullptr;

			if (Data.contains("CollisionObject"))
			{
				using namespace CollisionSystem;

				point3d Center(Data["CollisionObject"]["AABB"]["Center"][0], Data["CollisionObject"]["AABB"]["Center"][1], 0.f);
				point3d Extents(Data["CollisionObject"]["AABB"]["Extents"][0], Data["CollisionObject"]["AABB"]["Extents"][1], 0.f);

				o_ActorToCreate.CO->BoundingBox.Center = Center;
				o_ActorToCreate.CO->BoundingBox.Extents = Extents;

				o_ActorToCreate.CO->GO = o_ActorToCreate.GO;

				DebugPrint120("CollisionObject Created.\n");
			}
			else
				o_ActorToCreate.CO = nullptr;

			if (Data.contains("Renderable"))
			{
				// Fetching and converting data
				std::string Sprite = Data["Renderable"]["Sprite"];
				const char* SpriteChar = Sprite.c_str();

				// Creating sprite
				o_ActorToCreate.RO->Sprite = CreateSprite(SpriteChar);
				o_ActorToCreate.RO->GO = o_ActorToCreate.GO;
				DebugPrint120("SpriteObject Created.\n");
			}
			else
				o_ActorToCreate.RO = nullptr;
		}

#ifdef _DEBUG
		const size_t	lenBuffer = 65;
		char			Buffer[lenBuffer];

		sprintf_s(Buffer, lenBuffer, "Object Loaded from JSON\n");
		OutputDebugStringA(Buffer);
#endif // __DEBUG

		FileContent.clear();
	}



}