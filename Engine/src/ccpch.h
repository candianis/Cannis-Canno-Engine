#pragma once

//Cannis Canno Precompiled header

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <sstream>
#include <thread>
#include <typeindex>

// Data structures
#include <string>
using std::string;
#include <vector>
#include <unordered_map>
#include <map>
#include <list>

//
#include "Logger/Log.h"

#ifdef CC_PLATFORM_WINDOWS
	#include <Windows.h>
#endif