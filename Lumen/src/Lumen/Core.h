#pragma once

#include <memory>

#ifdef LM_PLATFORM_WINDOWS
#if LM_DYNAMIC_LINK
	#ifdef LM_BUILD_DLL // Bulid this DLL
		#define LUMEN_API __declspec(dllexport)
	#else
		#define LUMEN_API __declspec(dllimport)
	#endif
#else
	#define LUMEN_API
#endif
#else
	#error Lumen only supports Windows!
#endif

#ifdef LM_DEBUG
	#define LM_ENABLE_ASSSERTS
#endif

#ifdef LM_ENABLE_ASSSERTS
	#define LM_CLIENT_ASSERT(x, ...) { if (!(x)) { LM_CLIENT_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();} }
	#define LM_CORE_ASSERT(x, ...) { if (!(x)) { LM_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();} }
#else
	#define LM_CLIENT_ASSERT(x, ...)
	#define LM_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1 << x)

#define LM_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Lumen {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
	
	


}