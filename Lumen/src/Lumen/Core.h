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