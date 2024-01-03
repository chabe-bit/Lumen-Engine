#pragma once
#pragma once

#include "Lumen/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Lumen {

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;


	private:
		GLFWwindow* m_windowHandle;
	};

}