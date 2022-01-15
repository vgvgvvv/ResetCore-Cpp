#pragma once
#include "CommonHeader.h"

RE_CLASS()
class TestClass
{
	DEFINE_CLASS(TestClass)

	RE_FIELD()
	int IntValue;

	RE_FUNCTION()
	void TestFunction();
};

