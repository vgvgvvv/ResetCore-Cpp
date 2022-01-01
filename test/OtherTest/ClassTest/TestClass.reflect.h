#pragma once

#include "Class/BaseTypes.h"
#include "Class/ClassStorage.h"

class TestClass;

namespace __ClassDetail
{
    template<>
    struct GetClassStorageWrapper<TestClass>
    {
        static const ClassStorage* GetClassStorage()
        {
            std::vector<FieldInfo> FieldInfos;
            FieldInfos.emplace_back(FieldInfo("IntValue"
                , MemberAccessType::Public
                , MemberFlag::None
                , MemberOwnerType::ClassMember
                , GetType<int>()));

            std::vector<MethodInfo> MethodInfos;

            static ClassStorage StorageCache(
                FieldInfos,
                MethodInfos
            );
            return &StorageCache;
        }
    };
}
