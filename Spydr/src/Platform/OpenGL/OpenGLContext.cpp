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

		SP_CORE_TRACE("==== OpenGL Info: ====");
		SP_CORE_TRACE("  -> Vendor: {0}", glGetString(GL_VENDOR));
		SP_CORE_TRACE("  -> Renderer: {0}", glGetString(GL_RENDERER));
		SP_CORE_TRACE("  -> Version: {0}", glGetString(GL_VERSION));

#ifdef SP_ENABLE_ASSERTS
		int versionMajor;
		int versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

		SP_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "SpydrEngine requires at least OpenGL version 4.5!");
#endif
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}