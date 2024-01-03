#pragma once

#include <string>

namespace Lumen {
	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void unBind() const;

	private:
		uint32_t m_RendererID; // ID for every object

	};
}