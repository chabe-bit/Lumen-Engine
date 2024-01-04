#include "lmpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <gl/GL.h>

namespace Lumen {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_windowHandle(windowHandle)
	{
		LM_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_windowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		LM_CORE_ASSERT(status, "Failed to initialize Glad!");

		//LM_CORE_INFO("OpenGL Info: ");

		//LM_CORE_INFO("OpenGL Info: ");
		//LM_CORE_INFO("OpenGL Info: ");
		//LM_CORE_INFO("OpenGL Info: ");

	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_windowHandle);
	}
}