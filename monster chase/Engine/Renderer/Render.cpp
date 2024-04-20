
#include "assert.h"

#include "Utils/Utils.h"
#include "Renderer/Render.h"

namespace Engine
{
	bool RenderSystem::Initialize()
	{
		AllRenderObjects.clear();
		AllRenderObjects.shrink_to_fit();
		return true;
	}

	bool RenderSystem::AddRenderObject(SmartPointer<RenderObject>& i_RO)
	{
		assert(i_RO);
		assert(i_RO->GO);
		// assert(i_RO->Sprite);
		AllRenderObjects.push_back(i_RO);
		return true;
	}

	bool RenderSystem::RemoveRenderObject(SmartPointer<RenderObject>& i_RO)
	{
		assert(i_RO);
		
		size_t count = AllRenderObjects.size();
		assert(count > 0);

		for (auto i = 0; i < count; i++)
		{
			if (AllRenderObjects[i] == i_RO)
			{
				auto SmartRO = AllRenderObjects[i].GetSmartPointer();
				AllRenderObjects[i] = std::move(AllRenderObjects.back());
				SmartRO->Release();
				SmartRO = nullptr;
				AllRenderObjects.pop_back();
				return true;
			}
		}
		return false;
	}

	void RenderSystem::Tick(float i_deltaT)
	{
		// IMPORTANT: Tell GLib that we want to start rendering
		// GLib::BeginRendering(Background);
		// Tell GLib that we want to render some sprites
		//GLib::Sprites::BeginRendering();

		size_t count = AllRenderObjects.size();
		if (count > 0)
		{
			for (auto i = 0; i < count; i++)
			{
				auto SmartRO = AllRenderObjects[i].GetSmartPointer();
				SmartRO->Render();
				SmartRO = nullptr;
			}
		}

		// Tell GLib we're done rendering sprites
		// GLib::Sprites::EndRendering();
		// IMPORTANT: Tell GLib we're done rendering
		// GLib::EndRendering();
	}

	bool RenderSystem::Shutdown()
	{
		bool SuccessfulShutdown = true;
		size_t count = AllRenderObjects.size();

		// check if there were any remaining RenderObjects in vector
		if (count > 0)
		{
			SuccessfulShutdown = false;
			for (auto i = 0; i < count; i++)
			{
				AllRenderObjects.pop_back();
			}
			AllRenderObjects.shrink_to_fit();
		}

		// IMPORTANT:  Tell GLib to shutdown, releasing resources.
		// GLib::Shutdown();

		return SuccessfulShutdown;
	}

	bool RenderObject::Render()
	{
		//if (GO && Sprite)
		//{
		//	auto SmartGO = GO.GetSmartPointer();

		//	// calcculating Offset
		//	static GLib::Point2D Offset;
		//	Offset.x = SmartGO->Location.x;
		//	Offset.y = SmartGO->Location.y;

		//	// Tell GLib to render this sprite at our calculated location
		//	GLib::Render(*Sprite, Offset, 0.0f);
		//	SmartGO = nullptr;
		//	return true;
		//}
		return false;
	}
	
	bool RenderObject::Release()
	{
		//assert(GO);
		//GO = nullptr;
		//if (Sprite)
		//{
		//	GLib::Release(this->Sprite);
		//	Sprite = nullptr;
		//	DebugPrint120("\nSprite Released.\n");
		//	return true;
		//}
		return false;
	}

	RenderObject::~RenderObject()
	{
	}
}

