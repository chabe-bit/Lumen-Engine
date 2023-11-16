#pragma once

#ifdef LM_PLATFORM_WINDOWS
	#ifdef LM_BUILD_DLL // Bulid this DLL
		#define LUMEN_API __declspec(dllexport)
	#else
		#define LUMEN_API __declspec(dllimport)
	#endif
#else
	#error Lumen only supports Windows!
#endif

#ifdef LM_ENABLE_ASSSERTS
	#define LM_CLIENT_ASSERT(x, ...) { if (!(x)) { LM_CLIENT_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();} }
	#define LM_CORE_ASSERT(x, ...) { if (!(x)) { LM_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();} }
#else
	#define LM_CLIENT_ASSERT(x, ...)
	#define LM_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1 << x)