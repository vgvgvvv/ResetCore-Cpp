#include <windows.h>
#include "D3D12Application.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
	PSTR cmdLine, int showCmd)
{
	D3D12Application app(hInstance);
	app.Run();
	return 0;
}
