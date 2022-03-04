#pragma once
#include "Template.h"

class TestClass;
template<>
struct PrintWrapper<TestClass>
{
	static void Print();
};

