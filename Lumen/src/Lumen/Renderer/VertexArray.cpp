#include "lmpch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "VertexArray.h"

#include "Platforms/OpenGL/OpenGLVertexArray.h"

namespace Lumen {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		LM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:	return new OpenGLVertexArray();

		}

		LM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}