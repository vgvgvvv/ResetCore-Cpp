#include "D3D12RHILayer.h"
#include "D3D12RHI.h"

void D3D12RHILayer::OnInit()
{
	D3D12WindowInfo info;
	info.windowInstance = windowLayer->get_appInstance();
	info.window = windowLayer->get_mhMainWnd();
#if PLATFORM_WINDOWS
	info.width = windowLayer->get_width();
	info.height = windowLayer->get_height();
#endif
	D3D12RHI::Get().Init(info);
}

void D3D12RHILayer::OnShutDown()
{
	D3D12RHI::Get().Uninit();
}
