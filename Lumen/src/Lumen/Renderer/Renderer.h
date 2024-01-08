#pragma once

#include <glm/glm.hpp>
#include "RendererAPI.h"
#include "VertexArray.h"

namespace Lumen {
    class Renderer {
    public:
        static void Init(); // Initialize the RendererAPI
        static void Shutdown(); // Clean up

        static void SetClearColor(const glm::vec4& color);
        static void Clear();

        static void CameraView();

        static void BeginScene();
        static void EndScene();

        static void Submit(const std::shared_ptr<VertexArray>& vertexArray);
        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

    private:
        static RendererAPI* s_RendererAPI; // RendererAPI instance
    };
}
