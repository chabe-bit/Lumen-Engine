#pragma once

#include <glm/glm.hpp>
#include "RendererAPI.h"
#include "Shader.h"
#include "Lumen/Renderer/OrthographicCamera.h"

namespace Lumen {
    class Renderer {
    public:
        static void OpenGLInit(); // Initialize the RendererAPI
        static void Shutdown(); // Clean up

        static void SetClearColor(const glm::vec4& color);
        static void Clear();

        static void BeginScene(OrthographicCamera& camera);
        static void EndScene();

        static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0));
        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); } 

    private:
        static RendererAPI* s_RendererAPI; // RendererAPI instance

        struct SceneData
        {
            glm::mat4 ViewProjectionMatrix;
        };

        static SceneData* m_SceneData;


    };
}
