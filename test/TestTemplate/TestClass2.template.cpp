#include "Template.h"
#include "TestClass2.h"
#include <iostream>

template<>
void GlobalPrint2<TestClass2>()
{
	std::cout << "Hello TestClass2" << std::endl;
}
