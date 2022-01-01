#pragma once
#include "CommonHeader.h"
#include "TestClass.reflect.h"

RE_CLASS()
class TestClass
{
	DEFINE_CLASS(TestClass)

	RE_FIELD()
	int IntValue;

	RE_FUNCTION()
	void TestFunction();
};

