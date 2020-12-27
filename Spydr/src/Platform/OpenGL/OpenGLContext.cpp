#include "sppch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Spydr
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle)
	{
		SP_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		//OpenGL (Glad) initialization
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		SP_CORE_ASSERT(status, "Could not initialize Glad!");

		SP_CORE_WARN("OpenGL Info:");
		SP_CORE_TRACE("  -> Vendor: {0}", glGetString(GL_VENDOR));
		SP_CORE_TRACE("  -> Renderer: {0}", glGetString(GL_RENDERER));
		SP_CORE_TRACE("  -> Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}