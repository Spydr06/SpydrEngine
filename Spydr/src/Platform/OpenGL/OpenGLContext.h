#pragma once

#include "Spydr/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace SPYDR_API Spydr
{
#define vvoid virtual void
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		vvoid Init() override;
		vvoid SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
#undef vvoid
}