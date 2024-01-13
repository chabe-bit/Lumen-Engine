#include "lmpch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Lumen {

    void OpenGLRendererAPI::SetClearColor(const glm::vec4& color) {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray) {
        // Assuming your VertexArray class has a method to get the count of indices
        uint32_t indexCount = vertexArray->GetIndexBuffer()->GetCount();
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
    }

    void OpenGLRendererAPI::Clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    }
}