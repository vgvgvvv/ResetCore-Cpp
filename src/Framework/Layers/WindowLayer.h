#pragma once

#if PLATFORM_WINDOWS
#include <Windows.h>
#endif

#include "Application/Layer.h"
#include "Class/ClassInfo.h"
#include "ResetCore_Framework_API.h"

#if PLATFORM_WINDOWS

class ResetCore_Framework_API WindowLayer : public Layer
{
public:
	WindowLayer(int width, int height, HINSTANCE appInstance, WNDPROC wndproc = nullptr)
		: width(width), height(height), appInstance(appInstance), wndproc(wndproc)
	{
		
	}
	void OnInit() override;
	void OnUpdate(float deltaTime) override;
	void OnShutDown() override;
	bool ShouldQuit() override;

	DEFINE_GETTER(HINSTANCE, appInstance);
	DEFINE_GETTER(HWND, mhMainWnd);
	DEFINE_GETTER(int, width);
	DEFINE_GETTER(int, height);
	
private:
	bool InitWindow();

	HINSTANCE appInstance;
	HWND      mhMainWnd = nullptr;
	WNDPROC wndproc = nullptr;
	int width;
	int height;
	
	MSG msg = { 0 };
};

#endif