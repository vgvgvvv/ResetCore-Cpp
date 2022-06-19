

#include <iostream>

#include "TestLuau.h"

int main()
{
	TestLuau TestLuau;
	auto result = TestLuau.DoTask();

	std::cout << "result : " << result << std::endl;
	return 0;
}
