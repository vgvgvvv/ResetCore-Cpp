#pragma

#include <vector>
#include <map>
#include <string>

class EnumField;

class Enum
{
public:
	const EnumField* FindField(const std::string& EnumName)
	{
		const EnumField* Field = Fields.find();
		return Field;
	}
private:
	std::map<std::string, EnumField> Fields;
};

class EnumField
{
	
};