#pragma once

#include "CommonHeader.h"

namespace TestNamespace
{

	RE_ENUM(EnumAttr())
	enum class TestEnum
	{
		ValueFirst = 0,
		ValueSecond = 1
	};

	RE_CLASS(StructAttr())
	struct TestStruct
	{
		DEFINE_CLASS(TestStruct)

	};

	RE_CLASS(ClassAttr())
	class TestClass
	{
		DEFINE_CLASS(TestClass)

	public:

		RE_FUNCTION(FunctionAttr())
		static AString GetCurrentFileName()
		{
			return __FILE__;
		}

		RE_FUNCTION()
		const AString& GetTestStr() const
		{
			return TestStr;
		}


		RE_FIELD(FieldAttr("haha"), FileAttr("xixi"))
		int TestInt = 0;

		RE_FIELD()
		AString TestStr;

	};
}

