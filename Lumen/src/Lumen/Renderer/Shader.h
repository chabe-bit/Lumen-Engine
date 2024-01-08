#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Lumen {
	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void unBind() const;

		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

	private:
		uint32_t m_RendererID; // ID for every object

	};
}