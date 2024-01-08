#include "lmpch.h"
#include "Renderer.h"
#include "Platforms/OpenGL/OpenGLRendererAPI.h"

namespace Lumen {

    Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

    RendererAPI* Renderer::s_RendererAPI = nullptr;

    void Renderer::Init() {
        s_RendererAPI = new OpenGLRendererAPI; // Or appropriate initialization
    }

    void Renderer::Shutdown() {
        delete s_RendererAPI;
        s_RendererAPI = nullptr;
    }

    void Renderer::SetClearColor(const glm::vec4& color) {
        s_RendererAPI->SetClearColor(color);
    }

    void Renderer::Clear() {
        s_RendererAPI->Clear();
    }

    void Renderer::BeginScene(OrthographicCamera& camera) {
        m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::EndScene() {
        // Scene finalization code
    }

    void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray) {
       
        shader->Bind();
        shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
        
        vertexArray->Bind();
        s_RendererAPI->DrawIndexed(vertexArray);
    }

}