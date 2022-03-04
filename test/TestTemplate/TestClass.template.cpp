#include "Template.h"
#include "TestClass.h"
#include <iostream>

void PrintWrapper<TestClass>::Print()
{
	std::cout << "Hello TestClass" << std::endl;
}

template<>
void GlobalPrint2<TestClass>()
{
	std::cout << "Hello TestClass" << std::endl;
}
