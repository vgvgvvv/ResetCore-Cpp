#pragma once
#include <windows.h>
#include "Application/Application.h"

class D3D12Application : public Application
{
public:
	D3D12Application(HINSTANCE appInstance)
		: appInstance(appInstance)
	{

	}
protected:
	void Init() override;
	void Uninit() override;

private:
	HINSTANCE appInstance = nullptr;
};
