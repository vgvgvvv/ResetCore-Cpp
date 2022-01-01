#include "CommonHeader.h"
#include "TestClass.h"

int main()
{
	TestClass Test;
	auto Storage = Test.GetClass()->GetClassStorage();
	if(Storage)
	{
		auto Field = Storage->GetField("IntValue");
		auto FieldTypeName = Field->GetFieldType()->Name();
		RE_LOG_INFO("Test", "Field Type Is {}", FieldTypeName)
	}
	return 0;
}
