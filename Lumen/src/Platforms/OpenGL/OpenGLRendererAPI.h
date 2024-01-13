#pragma once
#include "Lumen/Renderer/RendererAPI.h"

namespace Lumen {

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
		virtual void Clear() override;
	};
}