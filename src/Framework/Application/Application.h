#pragma once
#include "Layer.h"
#include "ResetCore_Framework_API.h"

class ResetCore_Framework_API Application
{
public:
	virtual ~Application() = default;
	Application();

	int Run();

	LayerManager& GetLayerManager() { return LayerManager; }
	
	static Application& Get();

private:
	static Application* Instance;
	
protected:
	virtual void Init();
	virtual void Uninit();
	virtual bool ShouldQuit();

protected:
	LayerManager LayerManager;
};


