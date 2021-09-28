#pragma once
#include <wrl/client.h>
#include <d3d11_1.h>
#include "D3D11Internal/DXTrace.h"
#include "Class/ClassInfo.h"
#include "D3D11Initializers.h"
#include "D3D11Structs.h"

// ʹ��ģ�����(C++11)��������
template <class T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

//
// �����
//

// Ĭ�Ͽ���ͼ�ε�����������
// �������Ҫ����ܣ���ͨ��ȫ���ı��滻����ֵ����Ϊ0
#ifndef GRAPHICS_DEBUGGER_OBJECT_NAME
#define GRAPHICS_DEBUGGER_OBJECT_NAME (1)
#endif

// ��ȫCOM����ͷź�
#define SAFE_RELEASE(p) { if ((p)) { (p)->Release(); (p) = nullptr; } }

//
// ����������غ���
//

// ------------------------------
// D3D11SetDebugObjectName����
// ------------------------------
// ΪD3D�豸���������Ķ�����ͼ�ε����������ö�����
// [In]resource				D3D11�豸�������Ķ���
// [In]name					������
template<UINT TNameLength>
inline void D3D11SetDebugObjectName(_In_ ID3D11DeviceChild* resource, _In_ const char(&name)[TNameLength])
{
#if (defined(DEBUG) || defined(_DEBUG)) && (GRAPHICS_DEBUGGER_OBJECT_NAME)
	resource->SetPrivateData(WKPDID_D3DDebugObjectName, TNameLength - 1, name);
#else
	UNREFERENCED_PARAMETER(resource);
	UNREFERENCED_PARAMETER(name);
#endif
}

// ------------------------------
// D3D11SetDebugObjectName����
// ------------------------------
// ΪD3D�豸���������Ķ�����ͼ�ε����������ö�����
// [In]resource				D3D11�豸�������Ķ���
// [In]name					������
// [In]length				�ַ�������
inline void D3D11SetDebugObjectName(_In_ ID3D11DeviceChild* resource, _In_ LPCSTR name, _In_ UINT length)
{
#if (defined(DEBUG) || defined(_DEBUG)) && (GRAPHICS_DEBUGGER_OBJECT_NAME)
	resource->SetPrivateData(WKPDID_D3DDebugObjectName, length, name);
#else
	UNREFERENCED_PARAMETER(resource);
	UNREFERENCED_PARAMETER(name);
	UNREFERENCED_PARAMETER(length);
#endif
}

// ------------------------------
// D3D11SetDebugObjectName����
// ------------------------------
// ΪD3D�豸���������Ķ�����ͼ�ε����������ö�����
// [In]resource				D3D11�豸�������Ķ���
// [In]name					������
inline void D3D11SetDebugObjectName(_In_ ID3D11DeviceChild* resource, _In_ const std::string& name)
{
#if (defined(DEBUG) || defined(_DEBUG)) && (GRAPHICS_DEBUGGER_OBJECT_NAME)
	resource->SetPrivateData(WKPDID_D3DDebugObjectName, (UINT)name.length(), name.c_str());
#else
	UNREFERENCED_PARAMETER(resource);
	UNREFERENCED_PARAMETER(name);
#endif
}

// ------------------------------
// D3D11SetDebugObjectName����
// ------------------------------
// ΪD3D�豸���������Ķ�����ͼ�ε���������ն�����
// [In]resource				D3D11�豸�������Ķ���
inline void D3D11SetDebugObjectName(_In_ ID3D11DeviceChild* resource, _In_ std::nullptr_t)
{
#if (defined(DEBUG) || defined(_DEBUG)) && (GRAPHICS_DEBUGGER_OBJECT_NAME)
	resource->SetPrivateData(WKPDID_D3DDebugObjectName, 0, nullptr);
#else
	UNREFERENCED_PARAMETER(resource);
#endif
}

// ------------------------------
// DXGISetDebugObjectName����
// ------------------------------
// ΪDXGI������ͼ�ε����������ö�����
// [In]object				DXGI����
// [In]name					������
template<UINT TNameLength>
inline void DXGISetDebugObjectName(_In_ IDXGIObject* object, _In_ const char(&name)[TNameLength])
{
#if (defined(DEBUG) || defined(_DEBUG)) && (GRAPHICS_DEBUGGER_OBJECT_NAME)
	object->SetPrivateData(WKPDID_D3DDebugObjectName, TNameLength - 1, name);
#else
	UNREFERENCED_PARAMETER(object);
	UNREFERENCED_PARAMETER(name);
#endif
}

// ------------------------------
// DXGISetDebugObjectName����
// ------------------------------
// ΪDXGI������ͼ�ε����������ö�����
// [In]object				DXGI����
// [In]name					������
// [In]length				�ַ�������
inline void DXGISetDebugObjectName(_In_ IDXGIObject* object, _In_ LPCSTR name, _In_ UINT length)
{
#if (defined(DEBUG) || defined(_DEBUG)) && (GRAPHICS_DEBUGGER_OBJECT_NAME)
	object->SetPrivateData(WKPDID_D3DDebugObjectName, length, name);
#else
	UNREFERENCED_PARAMETER(object);
	UNREFERENCED_PARAMETER(name);
	UNREFERENCED_PARAMETER(length);
#endif
}

// ------------------------------
// DXGISetDebugObjectName����
// ------------------------------
// ΪDXGI������ͼ�ε����������ö�����
// [In]object				DXGI����
// [In]name					������
inline void DXGISetDebugObjectName(_In_ IDXGIObject* object, _In_ const std::string& name)
{
#if (defined(DEBUG) || defined(_DEBUG)) && (GRAPHICS_DEBUGGER_OBJECT_NAME)
	object->SetPrivateData(WKPDID_D3DDebugObjectName, (UINT)name.length(), name.c_str());
#else
	UNREFERENCED_PARAMETER(object);
	UNREFERENCED_PARAMETER(name);
#endif
}

// ------------------------------
// DXGISetDebugObjectName����
// ------------------------------
// ΪDXGI������ͼ�ε���������ն�����
// [In]object				DXGI����
inline void DXGISetDebugObjectName(_In_ IDXGIObject* object, _In_ std::nullptr_t)
{
#if (defined(DEBUG) || defined(_DEBUG)) && (GRAPHICS_DEBUGGER_OBJECT_NAME)
	object->SetPrivateData(WKPDID_D3DDebugObjectName, 0, nullptr);
#else
	UNREFERENCED_PARAMETER(object);
#endif
}

