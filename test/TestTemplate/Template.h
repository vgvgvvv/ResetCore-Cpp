
#pragma once

template<typename T>
struct PrintWrapper
{
	static void Print()
	{
		static_assert(false, "Invalid Print");
	}
};

template<typename T>
void GlobalPrint()
{
	PrintWrapper<T>::Print();
}

template<typename T>
void GlobalPrint2();