#pragma once
#include "Singleton.h"
#include "Class/ClassInfo.h"
#include "VulkanRHI_API.h"
#include "VulkanInternal/VulkanInstance.h"
#include "VulkanInternal/VulkanDebugLayer.h"

class VulkanRHI_API VulkanRHI
{
	DEFINE_SINGLETON(VulkanRHI)
public:

	void Init();
	void Uninit();

private:
	VulkanInstance instance;
	VulkanDebugLayer debugLayer;
};
