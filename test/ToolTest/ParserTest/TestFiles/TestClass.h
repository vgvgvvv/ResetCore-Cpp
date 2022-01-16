#pragma once

#include "CommonHeader.h"

namespace TestNamespace
{

	RE_ENUM()
	enum class TestEnum
	{
		ValueFirst = 0,
		ValueSecond = 1
	};

	RE_CLASS()
	struct TestStruct
	{
		DEFINE_CLASS(TestStruct)

	};

	RE_CLASS()
	class TestClass
	{
		DEFINE_CLASS(TestClass)

	public:

		RE_FUNCTION()
		static AString GetCurrentFileName()
		{
			return __FILE__;
		}

		RE_FUNCTION()
		const AString& GetTestStr() const
		{
			return TestStr;
		}


		RE_FIELD()
		int TestInt = 0;

		RE_FIELD()
		AString TestStr;

	};
}

