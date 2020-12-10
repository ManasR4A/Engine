#include "Core.h"
#include "Timer/Timer.h"

bool Engine::Initialize()
{
	T = new Timer;
	T->Initialize();
	PhysicsSystem::InitializePhysicsSystem();
	CollisionSystem::Initialize();
	RenderSystem::Initialize();
	return false;
}

void Engine::Tick()
{
	deltaT = T->GetLatFrameTimeMS();

//#ifdef _DEBUG
//	const size_t	lenBuffer = 65;
//	char			Buffer[lenBuffer];
//
//	sprintf_s(Buffer, lenBuffer, "FrameTime = %f \n", deltaT);
//	OutputDebugStringA(Buffer);
//#endif // __DEBUG
	CollisionSystem::Tick(deltaT);
	PhysicsSystem::PhysicsTick(deltaT);
	RenderSystem::Tick(deltaT);
	
}

bool Engine::ShutDown()
{
	bool PHY = PhysicsSystem::ShutDownPhysicsSystem();
	bool CO = CollisionSystem::Shutdown();
	bool RE = RenderSystem::Shutdown();
	delete T;
	return PHY && CO && RE;
}
