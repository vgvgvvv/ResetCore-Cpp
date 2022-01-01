#pragma once

enum class MemberAccessType
{
	Public,
	Protected,
	Private
};

enum class MemberFlag
{
	None = 0,
	Static = 1,
	Abstruct = 1 << 1,
	Virtual = 1 << 2,
	Overrided = 1 << 3
};

class MemberInfo
{
public:

	MemberInfo(std::string&& InName, 
		MemberAccessType InAccessType,
		MemberFlag InFlag)
		: Name(std::move(Name))
		, AccessType(InAccessType)
		, Flag(InFlag)
	{
	}

	const std::string& GetName() const
	{
		return Name;
	}


	MemberAccessType GetAccessType() const
	{
		return AccessType;
	}

	MemberFlag GetMemberFlag() const
	{
		return Flag;
	}

private:
	const std::string Name;
	const MemberAccessType AccessType;
	const MemberFlag Flag;
};