#pragma once

#ifdef SP_PLATFORM_WINDOWS
	#ifdef SP_BUILD_DLL
		#define SPYDR_API __declspec(dllexport)
	#else 
		#define SPYDR_API __declspec(dllimport)
	#endif
#else
	#error SpydrEngine only supports Windows.
#endif

#define BIT(x) (1 << x)