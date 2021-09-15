#include "Application.h"

#include <chrono>

#include "CommonAssert.h"
#include "Logging/Log.h"

Application* Application::Instance = nullptr;
Application& Application::Get()
{
	return *Instance;
}

Application::Application()
{
	RE_ASSERT(Instance == nullptr)
	Instance = this;
}


bool Application::ShouldQuit()
{
	if(LayerManager.ShouldQuit())
	{
		return true;
	}
	return false;
}

void Application::Init()
{
	RE_LOG_INFO("Application", "Application::Init");
}

void Application::Uninit()
{
	RE_LOG_INFO("Application", "Application::Uninit");
}



int Application::Run()
{
	Init();

	auto lastTick = std::chrono::system_clock::now();
	std::chrono::duration<double> dt(0);
	while (!ShouldQuit())
	{
		dt = std::chrono::system_clock::now() - lastTick;
		lastTick = std::chrono::system_clock::now();

		const auto deltaTime = 
			std::chrono::duration_cast<std::chrono::milliseconds>(dt).count() * 1.0f / 1000.0f;
		
		LayerManager.PreUpdate(deltaTime);
		LayerManager.Update(deltaTime);
		LayerManager.LateUpdate(deltaTime);
		LayerManager.BeforeRender(deltaTime);
		LayerManager.OnGUI(deltaTime);
		LayerManager.Render(deltaTime);
		LayerManager.AfterRender(deltaTime);
	}

	Uninit();
	
	return 0;
}
