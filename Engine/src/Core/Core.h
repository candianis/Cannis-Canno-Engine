#pragma once

#ifdef CC_PLATFORM_WINDOWS
	#ifdef CC_BUILD_DLL
		#define CANNIS_API __declspec(dllexport)
	#else
		#define CANNIS_API __declspec(dllimport)
	#endif // DEBUG

#else
#error Cannis Canno only supports Windows

#endif

#ifdef CC_ENABLE_ASSERTS
	#define CC_ASSERT(x, ...) { if(!(x)) { CC_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define CC_CORE_ASSERT(x, ...) { if(!(x)) { CC_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }

#else
	#define CC_ASSERT(x, ...)
	#define CC_CORE_ASSERT(x, ...)

#endif

#define BIT(x) (1 << x)