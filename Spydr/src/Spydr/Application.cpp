#include "sppch.h"
#include "Application.h"

#include "Spydr/Events/ApplicationEvent.h"
#include "Spydr/Log.h"

#include <GLFW/glfw3.h>

namespace Spydr
{

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (m_Running) {
			glClearColor(0, 0.3, 0.7, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}
}