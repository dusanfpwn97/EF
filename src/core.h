#pragma once

#ifdef EF_PLATFORM_WINDOWS
	#ifdef EF_BUILD_DLL
		#define EF_API __declspec(dllexport)
	#else
		#define EF_API __declspec(dllimport)
	#endif
#else
	#error EF only supports Windows!
#endif