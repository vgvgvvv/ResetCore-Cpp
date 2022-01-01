#pragma once
#include "Class.h"


ResetCore_CommonLib_API extern Type const* GetTypeImpl(TypeTag<void>) noexcept;
ResetCore_CommonLib_API extern Type const* GetTypeImpl(TypeTag<bool>) noexcept;
ResetCore_CommonLib_API extern Type const* GetTypeImpl(TypeTag<char>) noexcept;
ResetCore_CommonLib_API extern Type const* GetTypeImpl(TypeTag<short>) noexcept;
ResetCore_CommonLib_API extern Type const* GetTypeImpl(TypeTag<int>) noexcept;
ResetCore_CommonLib_API extern Type const* GetTypeImpl(TypeTag<long>) noexcept;
ResetCore_CommonLib_API extern Type const* GetTypeImpl(TypeTag<long long>) noexcept;
ResetCore_CommonLib_API extern Type const* GetTypeImpl(TypeTag<float>) noexcept;
ResetCore_CommonLib_API extern Type const* GetTypeImpl(TypeTag<double>) noexcept;
ResetCore_CommonLib_API extern Type const* GetTypeImpl(TypeTag<long double>) noexcept;
ResetCore_CommonLib_API extern Type const* GetTypeImpl(TypeTag<unsigned char>) noexcept;
ResetCore_CommonLib_API extern Type const* GetTypeImpl(TypeTag<unsigned short>) noexcept;
ResetCore_CommonLib_API extern Type const* GetTypeImpl(TypeTag<unsigned int>) noexcept;
ResetCore_CommonLib_API extern Type const* GetTypeImpl(TypeTag<unsigned long>) noexcept;
ResetCore_CommonLib_API extern Type const* GetTypeImpl(TypeTag<unsigned long long>) noexcept;


template<typename T>
Type const* GetType()
{
	return GetTypeImpl(TypeTag<T>());
}

template<typename T>
Class const * GetClass()
{
	return T::StaticClass();
}