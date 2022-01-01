#include "CommonHeader.h"
#include "TestClass.h"

int main()
{
	TestClass Test;
	auto Storage = Test.GetClass()->GetClassStorage();
	return 0;
}
