#include "D3D11RHILayer.h"
#include "D3D11RHI.h"

void D3D11RHILayer::OnInit()
{
	D3D11WindowInfo info;
	info.windowInstance = windowLayer->get_appInstance();
	info.window = windowLayer->get_mhMainWnd();
#if PLATFORM_WINDOWS
	info.width = windowLayer->get_width();
	info.height = windowLayer->get_height();
#endif
	D3D11RHI::Get().Init(info);
}

void D3D11RHILayer::OnShutDown()
{
	D3D11RHI::Get().Uninit();
}
