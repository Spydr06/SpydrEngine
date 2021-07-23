#pragma once

#if defined(SP_PLATFORM_WINDOWS)
	#ifdef SP_BUILD_DLL
		#define SPYDR_API __declspec(dllexport)
	//#else 
		//#define SPYDR_API __declspec(dllimport)
	#endif
	#define SPYDR_API
#elif defined(SP_PLATFORM_LINUX)

#else
	#error SpydrEngine only supports Windows.
#endif

#ifdef SP_ENABLE_ASSERTS
	#define SP_ASSERT(x, ...) { if(!(x)) { SP_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define SP_CORE_ASSERT(x, ...) { if(!(x)) { SP_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define SP_ASSERT(x, ...)
	#define SP_CORE_ASSERT(x, ...)
#endif

#define SPYDR_API

#define BIT(x) (1 << x)
#define SP_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
#define ARRAY_SIZE(x) std::size(x)