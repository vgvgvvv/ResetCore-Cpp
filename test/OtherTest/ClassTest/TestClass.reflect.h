#pragma once

class TestClass;

namespace __ClassDetail
{
    template<>
    struct GetClassStorageWrapper<TestClass>
    {
        static const ClassStorage* GetClassStorage()
        {
            std::vector<FieldInfo> FieldInfos;
            FieldInfos.emplace_back(
                FieldInfo(GetType<int>(),
                    "IntValue",
                    FieldInfo::FieldOwnerType::ClassMember));

            std::vector<MethodInfo> MethodInfos;

            static ClassStorage StorageCache(
                FieldInfos,
                MethodInfos
            );
            return &StorageCache;
        }
    };
}
