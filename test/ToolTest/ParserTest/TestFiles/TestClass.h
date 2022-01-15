#pragma once

#include "CommonHeader.h"

namespace TestNamespace
{
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

