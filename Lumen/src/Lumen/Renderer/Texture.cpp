#include "lmpch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platforms/OpenGL/OpenGLTexture.h"

namespace Lumen {
	Ref<Texture2D> Lumen::Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	LM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:	return std::make_shared<OpenGLTexture2D>(path);

		}

		LM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
