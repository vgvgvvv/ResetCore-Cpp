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
	class TestClass
	{
		DEFINE_CLASS(TestClass)

	public:

		RE_FUNCTION()
		static AString GetCurrentFileName()
		{
			return __FILE__;
		}

	};
}

