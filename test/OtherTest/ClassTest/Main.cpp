#include "CommonHeader.h"


class TestClass
{
	DEFINE_CLASS(TestClass)
};

DEFINE_CLASS_IMP(TestClass)

int main()
{
	TestClass Test;
	auto Storage = Test.GetClass()->GetClassStorage();
	return 0;
}