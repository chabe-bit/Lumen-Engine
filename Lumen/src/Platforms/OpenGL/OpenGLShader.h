#pragma once

#include "Lumen/Renderer/Shader.h"
#include <glm/glm.hpp>

// Todo: Remove
typedef unsigned int GLenum;

namespace Lumen {
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void unBind() const override;

		void UploadUniformInt(const std::string& name, int value);
		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& value);

		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

	private:
		std::string ReadFile(const std::string& filename);
		std::unordered_map<GLenum, std::string>PreProcess(const std::string& source); // Map our shader types
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSource);
	private:
		uint32_t m_RendererID; // ID for every object

	};
}