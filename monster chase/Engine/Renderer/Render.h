#pragma once
#include "Containers/Poimters/SmartPointer.h"
#include "Game Object/Entity.h"

#include "GLib.h"

#include "vector"

namespace Engine
{
	class RenderObject
	{
	public:
		WeakPointer<GameObject> GO;
		GLib::Sprite* Sprite = nullptr;

		bool Render();

		bool Release();
		~RenderObject();
	};

	namespace RenderSystem
	{
		static const float Background[4] = { 255.f, 255.f, 255.f, 255.f };
		static std::vector<WeakPointer<RenderObject>> AllRenderObjects;
		
		bool Initialize();

		bool AddRenderObject(SmartPointer<RenderObject>& i_RO);

		bool RemoveRenderObject(SmartPointer<RenderObject>& i_RO);

		void Tick(float i_deltaT);

		bool Shutdown();

	}
}

