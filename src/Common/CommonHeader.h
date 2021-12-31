#pragma once

#include <string>
#include "Logging/Log.h"
#include "CommonAssert.h"
#include "Platform/Platform.h"
#include "Misc/StringEx.h"
#include "Misc/Path.h"
#include "Misc/Memory.h"

#include "FileSystem/File.h"
#include "FileSystem/Directory.h"

#include "Class/ClassInfo.h"
#include "Class/ClassMisc.h"

#include "Platform/Platform.h"

#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <iostream>
#include <memory>
#include <functional>

namespace fs = std::filesystem;

using AString = std::string;
using WString = std::wstring;

template<typename T>
using SharedPtr = std::shared_ptr<T>;

template<typename T>
using Vector = std::vector<T>;

template<typename K, typename V>
using Map = std::map<K, V>;

template<typename T>
using Set = std::set<T>;

template<typename T>
using Queue = std::queue<T>;

template<typename T>
using Stack = std::stack<T>;

template<typename T>
using Function = std::function<T>;

using DirectoryEntry = fs::directory_entry;
