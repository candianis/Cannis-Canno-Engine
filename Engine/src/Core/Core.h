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