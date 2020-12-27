#include "sppch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Spydr
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle)
	{
		SP_CORE_ASSERT(windowHandle, "Window hndle is null!");
	}

	void OpenGLContext::Init()
	{
		//OpenGL (Glad) initialization
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		SP_CORE_ASSERT(status, "Could not initialize Glad!");
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}