#pragma once
#include <wrl/client.h>
#include <d3d12.h>
#include "Class/ClassInfo.h"
#include "D3D12Structs.h"

// 使用模板别名(C++11)简化类型名
template <class T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

