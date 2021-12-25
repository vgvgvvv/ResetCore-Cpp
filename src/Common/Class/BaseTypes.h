#include "Class.h"


extern Type const* GetTypeImpl(TypeTag<void>) noexcept;
extern Type const* GetTypeImpl(TypeTag<bool>) noexcept;
extern Type const* GetTypeImpl(TypeTag<char>) noexcept;
extern Type const* GetTypeImpl(TypeTag<short>) noexcept;
extern Type const* GetTypeImpl(TypeTag<long>) noexcept;
extern Type const* GetTypeImpl(TypeTag<long long>) noexcept;
extern Type const* GetTypeImpl(TypeTag<float>) noexcept;
extern Type const* GetTypeImpl(TypeTag<double>) noexcept;
extern Type const* GetTypeImpl(TypeTag<long double>) noexcept;
extern Type const* GetTypeImpl(TypeTag<unsigned char>) noexcept;
extern Type const* GetTypeImpl(TypeTag<unsigned short>) noexcept;
extern Type const* GetTypeImpl(TypeTag<unsigned int>) noexcept;
extern Type const* GetTypeImpl(TypeTag<unsigned long>) noexcept;
extern Type const* GetTypeImpl(TypeTag<unsigned long long>) noexcept;


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