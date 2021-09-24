#pragma once
#include <windows.h>
#include "Application/Application.h"

class VulkanApplication : public Application
{
public:
	VulkanApplication(HINSTANCE appInstance)
		: appInstance(appInstance)
	{

	}
protected:
	void Init() override;
	void Uninit() override;

private:
	HINSTANCE appInstance = nullptr;
};