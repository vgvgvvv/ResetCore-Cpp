
#include <windows.h>
#include "VulkanApplication.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
    PSTR cmdLine, int showCmd)
{
	VulkanApplication app(hInstance);
	app.Run();
	return 0;
}
