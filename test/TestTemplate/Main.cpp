
#include "TestClass.h"
#include "TestClass2.h"


int main()
{
	GlobalPrint<TestClass>();
	GlobalPrint2<TestClass>();
	GlobalPrint2<TestClass2>();
	return 0;
}
